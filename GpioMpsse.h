#pragma once
#include "IGpio.h"

class GpioMpsse :
	public IGpio
{
public:
	GpioMpsse();
	void SetPin(int pin, bool isHigh);
	virtual ~GpioMpsse();

private:
	struct mpsse_context *io;
};
