FROM ubuntu:18.04
ENV TZ=Europe/Minsk
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y git cmake build-essential
RUN cd $HOME && git clone https://github.com/RosettaCommons/binder.git
RUN mkdir $HOME/prefix && cd $HOME/prefix


RUN apt-get update && apt-get install -y \
xz-utils \
build-essential \
curl \
&& rm -rf /var/lib/apt/lists/* \
&& curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
| tar -xJC . && \
mv clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04 clang_10.0.0 && \
echo 'export PATH=/clang_10.0.0/bin:$PATH' >> ~/.bashrc && \
echo 'export LD_LIBRARY_PATH=/clang_10.0.0/lib:$LD_LIBRARY_PATH' >> ~/.bashrc

RUN cd  $HOME/binder && cmake .  -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_EH=1 -DLLVM_ENABLE_RTTI=ON && make -j && make install
RUN apt-get update && apt-get install -y libx11-dev libgl1-mesa-dev libegl1-mesa-dev libudev-dev libalut-dev
RUN apt-get update && apt-get install -y libfreetype6-dev libxrandr-dev libudev-dev libogg-dev libflac-dev libvorbis-dev libopenal-dev pkg-config
RUN apt-get -y install libtool pkg-config build-essential autoconf automake libsodium-dev

COPY run.sh /opt/run.sh
RUN chmod 777 /opt/run.sh
CMD /opt/run.sh
