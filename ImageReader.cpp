#include "ImageReader.h"
#include <fstream>

using std::ifstream;
using std::getline;

ImageReader::ImageReader(const string & folder) 
	: folder(folder)
{
}


ImageReader::~ImageReader()
{
}

string ImageReader::getImage(const string & name) 
{
	ifstream myfile;
	string content = folder + "/" + name + ".txt";
	myfile.open(folder + "/" + name + ".txt");
	if (myfile.is_open())
	{
		getline(myfile, content);
		myfile.close();
	}
	else
	{
		//content = "Not open";
	}
	return content;
}
