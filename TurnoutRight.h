#pragma once
#include "Turnout.h"
class TurnoutRight :
	public Turnout
{
public:
	TurnoutRight(IGpio * io, const string & id, int pin, const string & type);
	~TurnoutRight();
	bool isStateAllowed(States state) const;
	void toggle();
protected:
	int pinForState(States state) const { return pin; }
	bool isHighForState(States state) const;

private:
	int pin;
};

