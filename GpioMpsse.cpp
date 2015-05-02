#include "GpioMpsse.h"
#include <iostream>

extern "C"
{
#include <mpsse.h>
}

using std::cout;
using std::cerr;
using std::endl;


GpioMpsse::GpioMpsse() {
	io = MPSSE(GPIO, 0, 0);
	if (!io || !io->open) {
		cerr << "No GPIO found ! (maybe try run as root)" << endl;
		exit(-1);
	}
}

GpioMpsse::~GpioMpsse() {
	Close(io);
}

void GpioMpsse::SetPin(int pin, bool isHigh) {
	cout << "SetPin " << pin << " : " << isHigh << endl;
	int write;
	if (isHigh) {
		write = PinHigh(io, pin);
	} else {
		write = PinLow(io, pin);
	}
	cout << "State: " << PinState(io, pin, -1) << " / " << write << endl;
}
