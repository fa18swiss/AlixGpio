#include "TurnoutLeft.h"


TurnoutLeft::TurnoutLeft(IGpio * io, const string & id, int pin, const string & type)
	: Turnout(io, id, "Left" + type, Middle, Middle), pin(pin)
{
}


TurnoutLeft::~TurnoutLeft()
{
}

void TurnoutLeft::toggle() 
{
	setState(getState() == Left ? Middle : Left);
}

bool TurnoutLeft::isStateAllowed(States state) 
{
	return state == Middle || state == Left;
}
bool TurnoutLeft::isHighForState(States state)
{
	return state == Left;
}