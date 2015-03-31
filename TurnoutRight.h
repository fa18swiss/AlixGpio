#pragma once
#include "Turnout.h"
class TurnoutRight :
	public Turnout
{
public:
	TurnoutRight(io_type * io, const string & id, int pin, const string & type);
	~TurnoutRight();
	bool isStateAllowed(States state);
	void toggle();
protected:
	int pinForState(States state) { return pin; }
	bool isHighForState(States state);

private:
	int pin;
};

