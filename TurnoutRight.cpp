#include "TurnoutRight.h"


TurnoutRight::TurnoutRight(IGpio * ioP, const string & idP, int pinP, const string & type) : Turnout(ioP, idP, "Right" + type, Middle, Middle), pin(pinP)
{

}


TurnoutRight::~TurnoutRight()
{

}

void TurnoutRight::toggle()
{
	setState(getState() == Right ? Middle : Right);
}

bool TurnoutRight::isStateAllowed(States state) const
{
	return state == Middle || state == Right;
}
bool TurnoutRight::isHighForState(States state) const
{
	return state == Right;
}