#pragma once
#include <string>
#include <strstream>
#include <sstream>
#include <fstream>
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "IGpio.h"

using std::string;
using rapidjson::Writer;

typedef enum States {
	Unknown = 0,
	Left = 1,
	Right = 2,
	Middle = 3,
	Cross = 4,
	Outside = 5,
};

class Turnout
{
public:
	Turnout(IGpio * io, const string & id, const string & type, States currentState, States defaultState);
	virtual ~Turnout();
	string getId() const { return id; }
	string getType() const { return type; }
	States getState() const { return state; }
	virtual void toggle() = 0;
	virtual void setState(States newState);
	void setDefault() { setState(defaultState); }
	string getImage() const;
	template <typename Writer>
	void serialize(Writer * writer) const {
		writer->StartObject();
		writer->String("Id");
		writer->String(this->getId().c_str());
		writer->String("Type");
		writer->String(this->getType().c_str());
		writer->String("Img");
		writer->String(this->getImage().c_str());
		writer->String("State");
		writer->String(this->stateToString(this->getState()));
		writer->String("Allowed");
		writer->StartArray();
		writeState(writer, Left);
		writeState(writer, Middle);
		writeState(writer, Right);
		writeState(writer, Cross);
		writeState(writer, Outside);
		writer->EndArray();
		writer->EndObject();
	}
	static States stringToState(const char *);
	static const char * stateToString(States state);

protected:
	virtual bool isStateAllowed(States state) const = 0;
	virtual int pinForState(States state) const = 0;
	virtual bool isHighForState(States state) const = 0;

private:
	IGpio * io;
	string id;
	States state;
	States defaultState;
	string type;
	template <typename Writer>
	void writeState(Writer * writer, States state) const
	{
		if (isStateAllowed(state))
		{
			writer->String(stateToString(state));
		}
	}
	static const char * STATE_UNKNOWN;
	static const char * STATE_LEFT;
	static const char * STATE_RIGHT;
	static const char * STATE_MIDDLE;
	static const char * STATE_CROSS;
	static const char * STATE_OUTSIDE;
};

