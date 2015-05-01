#include "Turnout.h"


Turnout::Turnout(IGpio * ioP, const string & idP, const string & typeP, States currentStateP, States defaultStateP)
	: io(ioP), id(idP), type(typeP), state(currentStateP), defaultState(defaultStateP)
{

}


Turnout::~Turnout()
{

}

void Turnout::setState(States newState) {
	if (newState != state) {
		state = newState;
		// TODO change gpio
		int pin = pinForState(state);
		bool high = isHighForState(state);
		io->SetPin(pin, high);
	}
}
string Turnout::stateToString(States state)
{
	string strState = "";
	switch (state)
	{
	case Left:
		strState = "Left";
		break;
	case Right:
		strState = "Right";
		break;
	case Middle:
		strState = "Middle";
		break;

	case Unknown:
	default:
		strState = "Unknown";
		break;
	}
	return strState;
}
string Turnout::getImage() const
{	
	return getType() + "." + stateToString(state);
}
