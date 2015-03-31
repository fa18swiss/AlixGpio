#pragma once
#include <string>
#include <strstream>
#include <sstream>
#include "rapidjson/prettywriter.h" // for stringify JSON

using std::string;
using rapidjson::Writer;

typedef enum States {
	Unknown = 0	,
	Left = 1	,
	Right = 2	,
	Middle = 3	,
	Cross = 4	,
	Outside = 5	,
};

typedef void io_type;

class Turnout
{
public:
	Turnout(io_type * io, const string & id, const string & type, States currentState, States defaultState);
	virtual ~Turnout();
	string getId() { return id; }
	string getType() { return type; }
	States getState () { return state; }
	virtual void toggle() = 0;
	virtual void setState(States newState);
	void setDefault() { setState(defaultState); }
	string getImage();
	template <typename Writer>
	void serialize(Writer * writer) {
		writer->StartObject();
		writer->String("Id");
		writer->String(this->getId().c_str());
		writer->String("Type");
		writer->String(this->getType().c_str());
		writer->String("Img");
		writer->String(this->getImage().c_str());
		writer->String("State");
		writer->String(this->stateToString(this->getState()).c_str());
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
	static string stateToString(States state);
	template <typename Writer>
	void serializeImage(Writer * writer) 
	{
		writer->StartObject();
		writer->String("Id");
		writer->String(this->getImage().c_str());
		writer->String("Data");
		string path = string("Images/") + this->getImage() + string(".txt");
		std::ifstream inFile;
		inFile.open(path);//open the input file

		std::stringstream strStream;
		strStream << inFile.rdbuf();//read the file
		string str = strStream.str();//str holds the content of the file
		inFile.close();
		writer->String(str.c_str());
		writer->EndObject();
	}

protected:
	virtual bool isStateAllowed(States state) = 0;
	string type;
	virtual int pinForState(States state) = 0;
	virtual bool isHighForState(States state) = 0;
	States * allowedStates;

private:
	io_type * io;
	string id;
	States state;
	States defaultState;
	template <typename Writer>
	void writeState(Writer * writer, States state) 
	{
		if (isStateAllowed(state)) 
		{
			writer->String(stateToString(state).c_str());
		}
	}
};

