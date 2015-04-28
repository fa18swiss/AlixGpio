#include "GpioMpsse.h"
#include <iostream>

extern "C"
{
#include <mpsse.h>
}

using std::cout;
using std::endl;


GpioMpsse::GpioMpsse()
{
	io = MPSSE(GPIO, 0, 0);
	if (io) {
		cout << "IO pass" << endl;
	}
	else {
		cout << "IO not pass" << endl;
	}

	if (io->open) {
		cout << "IO open" << endl;
	}
	else {
		cout << "IO not open" << endl;
	}
}


GpioMpsse::~GpioMpsse()
{
	Close(io);
}

void GpioMpsse::SetPin(int pin, bool isHigh)
{
	cout << "SetPin " << pin << " : " << isHigh << endl;
	int write;
	if (isHigh) {
		write = PinHigh(io, pin);
	}
	else {
		write = PinLow(io, pin);
	}
	cout << "State:  << " << PinState(io, pin, -1) << " / " << write << endl;
}
