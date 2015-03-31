#pragma once
#include "Turnout.h"
class TurnoutList
{
public:
	TurnoutList(int nb);
	~TurnoutList();
	Turnout * get(int i);
	void set(int i, Turnout * turnout);
	int nb() { return number; }
private:
	bool validate(int i);
	int number;
	Turnout ** turnouts;
};

