sudo apt remove --purge 'qt5-*'
sudo apt autoremove
sudo apt update
cd ~/Desktop/
sudo apt update
sudo apt install -y build-essential libgl1-mesa-dev libxcb-xinerama0 libxkbcommon-x11-0
sudo apt install -y build-essential libgl1-mesa-dev libxcb-xinerama0 libxkbcommon-x11-0
sudo apt install -y llvm-14 llvm-14-dev clang-14 libclang-14-dev
sudo apt install -y libxcb1 libxcb1-dev libxcb-xinerama0 libxcb-xinerama0-dev \
	libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev \ 
	libxcb-render0 libxcb-render0-dev libxcb-shape0-dev libxcb-sync-dev \
	libxcb-icccm4 libxcb-icccm4-dev libxcb-xfixes0-dev libxcb-xkb-dev \
	libxcb-randr0 libxcb-randr0-dev libxkbcommon-x11-0

wget https://download.qt.io/archive/qt/6.6/6.6.0/single/qt-everywhere-src-6.6.0.tar.xz
tar -xf qt-everywhere-src-6.6.0.tar.xz
cd qt-everywhere-src-6.6.0
./configure
make
sudo make install
git clone https://github.com/KDAB/GammaRay.git
cd GammaRay
sudo apt purge gammaray
mkdir build && cd build/
cmake -G Ninja -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/Qt/6.6.0

cmake --build .
sudo cmake --build . --target install