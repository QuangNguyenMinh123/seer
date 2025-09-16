set -x
#########################################################
TOP_DIR=${PWD}
#########################################################
sudo rm -f /usr/bin/seergdb
sudo apt install -y debhelper dh-exec cmake build-essential mesa-common-dev libgl1-mesa-dev
sudo apt install -y qt6-base-dev libqt6gui6 libqt6charts6-dev libqt6opengl6-dev \
    libqt6svg6-dev libqt6core6 qt6-base-abi

cd ${TOP_DIR}/src
mkdir -p build
cd ${TOP_DIR}/src/build
cmake -DCMAKE_PREFIX_PATH=/home/quangnm/Qt/6.6.0 ..     
# export LD_LIBRARY_PATH=/home/quangnm/Qt/6.6.0/lib
# export CMAKE_PREFIX_PATH=/home/quangnm/Qt/6.6.0
# to launch  /usr/local/bin/seergdb
# Eg: LD_LIBRARY_PATH=/home/quangnm/Qt/6.6.0/lib CMAKE_PREFIX_PATH=/home/quangnm/Qt/6.6.0 /usr/local/bin/seergdb
make seergdb -j8
cd ${TOP_DIR}
sudo dpkg-buildpackage -j8
cd ${TOP_DIR}/src/build
sudo make install
sudo cp ${TOP_DIR}/src/resources/seergdb.desktop ~/.local/share/applications/