#include "GpioMpsse.h"
#include <iostream>

#ifdef _MSC_VER
int PinHigh(struct mpsse_context *, int) 
{
	return 0;
}
int PinState(struct mpsse_context *, int, int)
{
	return 0;
}
int PinLow(struct mpsse_context *, int)
{
	return 0;
}
int Close(struct mpsse_context *)
{
	return 0;
}
#else
extern "C"
{
#include <mpsse.h>
}
#endif

using std::cout;
using std::endl;


GpioMpsse::GpioMpsse()
{
#ifndef _MSC_VER
	io = MPSSE(GPIO, 0, 0);
	if (io) {
		cout << "IO pass" << endl;
	} else {
		cout << "IO not pass" << endl;
	}

	if (io->open) {
		cout << "IO open" << endl;
	} else {
		cout << "IO not open" << endl;
	}
#endif
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
	cout << "State: " << PinState(io, pin, -1) << " / " << write << endl;
}
