#pragma once
#include <string>
#include "rapidjson/prettywriter.h" // for stringify JSON

using std::string;
using rapidjson::Writer;

class ImageReader
{
public:
	ImageReader(const string & folder);
	~ImageReader();
	string getImage(const string & name) const;
	template <typename Writer>
	void serialize(Writer * writer, const string & name) {
		writer->StartObject();
		writer->String("Id");
		writer->String(name.c_str());
		writer->String("Data");
		writer->String(getImage(name).c_str());
		writer->EndObject();
	}
private:
	string folder;
};

