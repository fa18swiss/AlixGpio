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

bool TurnoutList::validate(int i) const
{
	return i >= 0 && i < number;
}

Turnout * TurnoutList::get(int i) const
{
	if (validate(i))
	{
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

Turnout * TurnoutList::find(const char * name) const {
	for (int i = 0; i < number; i++) {
		if (turnouts[i]->getId() == name) {
			return turnouts[i];
		}
	}
	return 0;
}
