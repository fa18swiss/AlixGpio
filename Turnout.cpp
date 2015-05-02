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
string Turnout::getImage() const
{
	return getType() + "." + stateToString(state);
}

static const char * STATE_UNKNOWN = "Unknown";
static const char * STATE_LEFT = "Left";
static const char * STATE_RIGHT = "Right";
static const char * STATE_MIDDLE = "Middle";
static const char * STATE_CROSS = "Cross";
static const char * STATE_OUTSIDE = "Middle";

const char * Turnout::stateToString(States state)
{
	switch (state)
	{
	case Left:
		return STATE_LEFT;
	case Right:
		return STATE_RIGHT;
	case Middle:
		return STATE_MIDDLE;
	case Cross:
		return STATE_CROSS;
	case Outside:
		return STATE_OUTSIDE;

	case Unknown:
	default:
		return STATE_UNKNOWN;
	}
}
States Turnout::stringToState(const char * state) {
	if (strcmp(state, STATE_LEFT) == 0) {
		return Left;
	} else if (strcmp(state, STATE_RIGHT) == 0) {
		return Right;
	} else if (strcmp(state, STATE_MIDDLE) == 0) {
		return Middle;
	} else if (strcmp(state, STATE_CROSS) == 0) {
		return Cross;
	} else if (strcmp(state, STATE_OUTSIDE) == 0) {
		return Outside;
	}
	return Unknown;
}