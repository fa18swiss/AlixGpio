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

sudo touch /etc/init.d/alixgpio
sudo chmod +x /etc/init.d/alixgpio

echo "#!/bin/bash" | sudo tee /etc/init.d/alixgpio > /dev/null
echo "$DIR/$FOLDER &" | sudo tee -a /etc/init.d/alixgpio > /dev/null

sudo update-rc.d alixgpio defaults

echo install / build finished
