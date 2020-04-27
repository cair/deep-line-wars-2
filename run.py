import Engine

if __name__ == "__main__":

    game = Engine.Game(11, 11)
    action_space = Engine.DiscreteActions(game)
    player1 = game.get_player(0)
    player2 = game.get_player(1)
    i = 0



    while True:

        game.reset()

        while not game.terminal:

            if i % 60 == 0:
                game.select_player(0)
                action_space.sample_action()
                game.select_player(1)
                action_space.sample_action()
            i += 1
            game.update()
            game.render()
