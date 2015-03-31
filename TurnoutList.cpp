#include "TurnoutList.h"


TurnoutList::TurnoutList(int nb) 
	: number(nb)
{
	turnouts = new Turnout*[number];
	for (int i = 0; i < number; i++)
	{
		turnouts[i] = 0;
	}
}

TurnoutList::~TurnoutList()
{
	for (int i = 0; i < number; i++) {
		delete turnouts[i];
	}
	delete[] turnouts;
}

bool TurnoutList::validate(int i) 
{
	return i >= 0 && i < number;
}

Turnout * TurnoutList::get(int i) 
{
	if (validate(i)) {
		return turnouts[i];
	}
	else
	{
		return 0;
	}
}
void TurnoutList::set(int i, Turnout * turnout)
{
	if (validate(i)) {
		turnouts[i] = turnout;
	}
}
