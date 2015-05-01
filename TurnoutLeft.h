#pragma once
#include "Turnout.h"
class TurnoutLeft :
	public Turnout
{
public:
	TurnoutLeft(IGpio * io, const string & id, int pin, const string & type);
	~TurnoutLeft();
	bool isStateAllowed(States state) const;
	void toggle();
protected:
	int pinForState(States state) const { return pin; }
	bool isHighForState(States state) const;

private:
	int pin;
};

