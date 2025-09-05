set -x
git clone --recurse-submodules https://github.com/openocd-org/openocd.git
cd openocd
git submodule update --init --recursive
sudo apt-get install -y autoconf libtool libusb-1.0-0-dev libusb-dev libftdi1-dev libhidapi-dev automake libftfi-dev \
    apt-utils pkg-config libjim-dev libjaylink0
sudo apt-get install -y gdb-multiarch
./bootstrap
cd ..
git clone https://github.com/syntacore/libjaylink.git
cd libjaylink
./augogen.sh
./configure
make -j4
sudo make install
cd ..
cd openocd
./configure --enable-ftdi --enable-ft232r --enable-jlink --enable-armjtagew --enable-parport
make -j4
sudo make install