#pragma once
#include "Turnout.h"
#include "rapidjson/prettywriter.h" // for stringify JSON

using rapidjson::Writer;

class TurnoutList
{
public:
	TurnoutList(int nb);
	~TurnoutList();
	Turnout * get(int i) const;
	void set(int i, Turnout * turnout);
	int nb() const { return number; }
	template <typename Writer>
	void serialize(Writer * writer) {
		writer->StartArray();
		for (int i = 0; i < number; i++) {
			turnouts[i]->serialize(writer);
		}
		writer->EndArray();
	}
	Turnout * find(const char * id) const;
private:
	bool validate(int i) const;
	int number;
	Turnout ** turnouts;
};

