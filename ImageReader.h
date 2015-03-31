#pragma once
#include <string>

using std::string;

class ImageReader
{
public:
	ImageReader(const string & folder);
	~ImageReader();
	string getImage(const string & name);
private:
	string folder;
};

