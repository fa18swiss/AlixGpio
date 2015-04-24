#include <iostream>
#include <cstdlib>
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filestream.h"	
#include <string>

#include "TurnoutLeft.h"
#include "TurnoutList.h"
#include "TurnoutRight.h"
#include "ImageReader.h"
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
	ImageReader imageReader("Images/");
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
	imageReader.serialize(&writer, "RightSame.Middle");
	imageReader.serialize(&writer, "RightSame.Left");
	
	writer.EndArray();
	writer.EndArray();
	

	cin.get();
	return EXIT_SUCCESS;
}