#pragma once
#include "Turnout.h"
class TurnoutLeft :
	public Turnout
{
public:
	TurnoutLeft(IGpio * io, const string & id, int pin, const string & type);
	~TurnoutLeft();
	bool isStateAllowed(States state);
	void toggle();
protected:
	int pinForState(States state) { return pin; }
	bool isHighForState(States state);

private:
	int pin;
};

