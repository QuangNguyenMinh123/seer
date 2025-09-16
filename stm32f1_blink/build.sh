set -x
TOP_DIR=${PWD}
cd ..
git submodule update --init --recursive
cd stm32f1_blink
# install package
sudo apt install gcc-arm-none-eabi
# make
make
# make flash, assume that openocd is installed by running install_openocd.sh
make flash JLINK_CFG=${PWD}/../openocd/tcl/interface/jlink.cfg

