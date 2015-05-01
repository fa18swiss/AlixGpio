#include <iostream>
#include <cstdlib>
#include "rapidjson/writer.h" // for stringify JSON
#include <string>

#include "TurnoutLeft.h"
#include "TurnoutList.h"
#include "TurnoutRight.h"
#include "ImageReader.h"
#include "JsonServer.h"
#include "GpioMpsse.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using namespace rapidjson;

int main(void)
{
	cout << "start" << endl;
	GpioMpsse gpio;
	TurnoutList list(4);
	ImageReader imageReader("Images/");
	list.set(0, new TurnoutLeft(&gpio, "1", 0, "Same"));
	list.set(1, new TurnoutLeft(&gpio, "2", 1, "Switch"));
	list.set(2, new TurnoutRight(&gpio, "3", 2, "Switch"));
	list.set(3, new TurnoutRight(&gpio, "4", 3, "Same"));
	list.get(1)->setState(Left);
	list.get(2)->setState(Right);

	StringBuffer sb;
	Writer<StringBuffer> writer(sb);
	writer.StartArray();
	list.serialize(&writer);
	writer.StartArray();
	imageReader.serialize(&writer, "RightSame.Middle");
	imageReader.serialize(&writer, "RightSame.Left");
	
	writer.EndArray();
	writer.EndArray();
	cout << sb.GetString();

	JsonServer server(&list, &imageReader);
		
	cout << "Result : '" << server.process("{\"Cmd\":\"tog\", \"Id\":\"4\"}") << "'" << endl;

	cout << "Result : '" << server.process("{\"Cmd\":\"img\", \"Id\":\"RightSame.Middle\"}") << "'" << endl;
	
	cin.get();
	return EXIT_SUCCESS;
}