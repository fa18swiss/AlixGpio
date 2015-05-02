#!binbash

#cd script directory
DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )
cd $DIR

#preare system
#sudo apt-get update

#insall dependencies
#yes  sudo apt-get install build-essential cmake libusb-1.0-0-dev swig python-dev libconfuse-dev libboost-all-dev libftdi-dev python-ftdi screen

#libftdi1-1.2
echo libftdi1-1.2
cd libftdi1-1.2
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=usr ..
time make
sudo make install
cd ....

#ibmpsse-1.3
echo ibmpsse-1.3
cd libmpsse-1.3src
.configure
make
sudo make install
cd ....

#enum34-1.0.4
echo enum34-1.0.4
cd enum34-1.0.4
sudo python2 setup.py install 
cd ..

#ServerCpp
echo ServerCpp
cd ServerCpp
make
cd ..

echo install  build finish


