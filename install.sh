#!/bin/bash

HELP="Usage: sudo ./install.sh <type>, with type: -cpp or -python"

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    echo $HELP
    exit 0
fi

key="$1"
case $key in
	-cpp|--cpp)
	FOLDER="ServerCpp/run.sh"
	;;
	-python|--python)
	FOLDER="ServerPython/main.py"
	;;
	*)
	echo $HELP
	exit 0
	;;
esac
echo "$DIR/$FOLDER"

#cd script directory
DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )
cd $DIR

#prepare system
sudo apt-get update

#install dependencies
yes | sudo apt-get install build-essential cmake libusb-1.0-0-dev swig python-dev libconfuse-dev libboost-all-dev libftdi-dev python-ftdi screen

#libftdi1-1.2
echo libftdi1-1.2
cd libftdi1-1.2
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="/usr/" ../
time make
sudo make install
cd ../..

#ibmpsse-1.3
echo ibmpsse-1.3
cd libmpsse-1.3/src
./configure
make
sudo make install
cd ../..

#enum34-1.0.4
echo enum34-1.0.4
cd enum34-1.0.4
sudo python2 setup.py install 
cd ..

#Adafruit_Python_GPIO
echo Adafruit_Python_GPIO
cd Adafruit_Python_GPIO
sudo python2 setup.py install
cd ..

#ServerCpp
echo ServerCpp
cd ServerCpp
make
cd ..

sudo touch /etc/init.d/alixgpio
sudo chmod +x /etc/init.d/alixgpio

sudo echo "#!/bin/bash" > /etc/init.d/alixgpio
sudo echo "$DIR/$FOLDER &"  >> /etc/init.d/alixgpio

sudo update-rc.d alixgpio defaults

echo install / build finished
