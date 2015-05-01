#pragma once

#include "TurnoutList.h"
#include "rapidjson/document.h" 


class JsonServer
{
public:
	JsonServer(TurnoutList * turnoutList);
	virtual ~JsonServer();
	std::string process(std::string message);
private:
	static const char * Get(rapidjson::Document & document, const char * key);
	static std::string Error(const char * msg);
	std::string List();
	TurnoutList * turnoutList;
	static const char * KEY_CMD;
	static const char * KEY_ID;
	static const char * KEY_STATE;
	static const char * KEY_ERROR;
	static const char * KEY_LIST;
	static const char * CMD_LIST;
	static const char * CMD_TOGGLE;
	static const char * CMD_DEFAULT;
	static const char * CMD_SET;
};

