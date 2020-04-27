#include <seasocks/Server.h>
#include <seasocks/PrintfLogger.h>
#include <seasocks/PageHandler.h>
#include <seasocks/StringUtil.h>
#include <seasocks/util/RootPageHandler.h>
#include <seasocks/util/PathHandler.h>
#include "game.h"
#include <nlohmann/json.hpp>
#include <chrono>
#include <zmq.hpp>
#include <filesystem>
#include <string>
#include <algorithm>
class WebSocketServer : public seasocks::WebSocket::Handler {
    game &_game;
public:

    WebSocketServer(game &g): _game(g){

    }

    void onConnect(seasocks::WebSocket* /*connection*/) override {
    }

    void onData(seasocks::WebSocket* connection, const uint8_t* data, size_t length) override {
        connection->send(data, length); // binary
    }

    void onData(seasocks::WebSocket* connection, const char* data) override {
        connection->send(data); // text
    }

    void onDisconnect(seasocks::WebSocket* /*connection*/) override {
    }
};

class StatusHandler : public seasocks::CrackedUriPageHandler {
    game &_game;
public:

    explicit StatusHandler(game &g):
    _game(g)
    {
    }


    std::shared_ptr<seasocks::Response> handle(
            const seasocks::CrackedUri& /*uri*/,
            const seasocks::Request& request) override {
        if (request.verb() != seasocks::Request::Verb::Get) {
            return seasocks::Response::unhandled();
        }


        auto d = std::chrono::duration_cast<std::chrono::duration<double>>(
                std::chrono::high_resolution_clock::now() -
                _game.startTime
                );
        nlohmann::json obj = {
                "gameCount", _game.gameCount,
                "averageTick", _game.averageTick(),
                "averageMinutes", (_game.averageTick() / _game._c.ticksPerSecond) / 60,
                "averageTPS", _game.tickSum / d.count(),
                "currentTick", _game.tick,
                "gameSeconds", _game.tick / _game._c.ticksPerSecond,
                "gameMinutes", (_game.tick / _game._c.ticksPerSecond) / 60,
                "terminal", _game.terminal

        };

        return seasocks::Response::jsonResponse(obj.dump());

    }

};

class APIServer{

public:
    seasocks::Server _server;
    std::thread* _thread;
    const bool _http;
    const bool _ws;
    const int _port;
    game &_game;
    zmq::context_t ctx;
    zmq::socket_t *sock;
    APIServer(game &g, bool http, bool ws, int port):
    _game(g),
    _port(port),
    _server(std::make_shared<seasocks::PrintfLogger>(seasocks::Logger::Level::Info)),
    _http(http),
    _ws(ws),
    ctx(1)
    {

        /*if( _game._c.dashboardAddress.rfind("ipc", 0) == 0){
            // Configured to use unix sockets

            if(std::filesystem::exists(_game._c.dashboardAddress)){
                // Unix socket already exists
                sock = new zmq::socket_t(ctx, ZMQ_PUB);
                sock->connect(_game._c.dashboardAddress);
            } else {
                // Unix socket does not exists
                sock = new zmq::socket_t(ctx, ZMQ_SUB);
                sock->bind(_game._c.dashboardAddress);
            }


        }else if(_game._c.dashboardAddress.rfind("tcp", 0) == 0){
            // Configured to use tcp sockets

            try{
                sock = new zmq::socket_t(ctx, ZMQ_REP);
                sock->bind(_game._c.dashboardAddress);
            }catch(const std::exception& e){
                sock = new zmq::socket_t(ctx, ZMQ_);
                sock->connect(_game._c.dashboardAddress);
            }

        } else  {
            throw std::runtime_error("Incorrect protocol in dashboardAddress");
        }*/

        _server.addWebSocketHandler("/stream", std::make_shared<WebSocketServer>(_game), true);
        auto root = std::make_shared<seasocks::RootPageHandler>();
        auto page_status = std::make_shared<seasocks::PathHandler>("status", std::make_shared<StatusHandler>(_game));
        root->add(page_status);
        _server.addPageHandler(root);
        _thread = new std::thread([this]{
            this->_server.serve("web", _port);
        });

    }


    ~APIServer(){
        _server.terminate();
        _thread->join();
    }



};