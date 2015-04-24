#pragma once
#include "Turnout.h"
#include "rapidjson/prettywriter.h" // for stringify JSON

using rapidjson::Writer;

class TurnoutList
{
public:
	TurnoutList(int nb);
	~TurnoutList();
	Turnout * get(int i);
	void set(int i, Turnout * turnout);
	int nb() { return number; }
	template <typename Writer>
	void serialize(Writer * writer) {
		writer->StartArray();
		for (int i = 0; i < number; i++) {
			turnouts[i]->serialize(writer);
		}
		writer->EndArray();
	}
private:
	bool validate(int i);
	int number;
	Turnout ** turnouts;
};

