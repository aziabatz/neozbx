# Cross Compiler install script for Debian derivatives

sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo
mkdir $HOME/src $HOME/src/gcc-build $HOME/src/binutils-build

./build_install_binutils.sh && ./build_install_gcc.sh
