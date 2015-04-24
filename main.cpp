#include <iostream>
#include <cstdlib>
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filestream.h"	
#include <string>

#include "TurnoutLeft.h"
#include "TurnoutList.h"
#include "TurnoutRight.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using namespace rapidjson;

int main(void)
{
	cout << "start" << endl;
	io_type * io = 0;
	TurnoutList list(4);
	list.set(0, new TurnoutLeft(io, "1", 0, "Same"));
	list.set(1, new TurnoutLeft(io, "2", 1, "Switch"));
	list.set(2, new TurnoutRight(io, "3", 2, "Switch"));
	list.set(3, new TurnoutRight(io, "4", 3, "Same"));
	list.get(1)->setState(Left);
	list.get(2)->setState(Right);

	FileStream s(stdout);
	PrettyWriter<FileStream> writer(s);
	writer.StartArray();
	list.serialize(&writer);
	writer.StartArray();
	for (int i = 0; i < list.nb(); i++)
	{
		Turnout * t = list.get(i);
		/*
		cout << "Turnout id = " << t->getId() << " type " << t->getType() << " stat " << t->getState() << endl;
		cout << "\t img " << t->getImage() << endl;
		cout << "\t i64" << imageReader.getImage(t->getImage()) << endl;
		*/
		t->serializeImage(&writer);
	}
	writer.EndArray();
	writer.EndArray();
	

	cin.get();
	return EXIT_SUCCESS;
}