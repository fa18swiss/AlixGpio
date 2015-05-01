#include "JsonServer.h"
#include <string>	
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

using namespace rapidjson;
using std::string;
using std::cout;
using std::endl;

JsonServer::JsonServer(TurnoutList * turnoutList) {
	this->turnoutList = turnoutList;
}


JsonServer::~JsonServer() {
}

const char * JsonServer::KEY_CMD = "Cmd";
const char * JsonServer::KEY_ID = "Id";
const char * JsonServer::KEY_STATE = "State";
const char * JsonServer::KEY_ERROR = "Error";
const char * JsonServer::KEY_LIST = "List";
const char * JsonServer::CMD_LIST = "list";
const char * JsonServer::CMD_TOGGLE = "tog";
const char * JsonServer::CMD_DEFAULT = "def";
const char * JsonServer::CMD_SET = "set";

const char * JsonServer::Get(Document & document, const char * key) {
	if (document.HasMember(key)) {
		if (document[key].IsString()) {
			cout << "Has command: " << key << endl;
			return document[key].GetString();
		}
	}
	return 0;
}

string JsonServer::Error(const char * msg) {
	StringBuffer sb;
	PrettyWriter<StringBuffer> writer(sb);

	writer.StartObject();

	writer.String(KEY_ERROR);
	writer.String(msg);

	writer.EndObject();

	return sb.GetString();
}

string JsonServer::List() {
	StringBuffer sb;
	PrettyWriter<StringBuffer> writer(sb);

	writer.StartObject();

	writer.String(KEY_ERROR);
	writer.String("");
	
	writer.String(KEY_LIST);
	turnoutList->serialize(&writer);

	writer.EndObject();

	return sb.GetString();
}

string JsonServer::process(string message) {
	Document document;
	if (document.Parse(message.c_str()).HasParseError())
	{
		cout << "Error while parsing" << endl;
		return Error("Error while parsing");
	}
	cout << "Parsing to document succeeded." << endl;


	const char * cmd = Get(document, KEY_CMD);
	const char * id = Get(document, KEY_ID);
	const char * state = Get(document, KEY_STATE);

	if (!cmd) {
		return Error("No cmd attribute");
	}


	if (strcmp(cmd, CMD_LIST) == 0) {
		return List();
	} else if (strcmp(cmd, CMD_TOGGLE) == 0) {
		if (id) {
			Turnout * t = turnoutList->find(id);
			if (t) {
				t->toggle();
				return List();
			} else {
				return Error("No turnout found !");
			}
		} else {
			for (int i = 0 ; i < turnoutList->nb() ; i++) {
				turnoutList->get(i)->toggle();
			}
			return List();
		}
	} else if (strcmp(cmd, CMD_DEFAULT) == 0) {
		if (id) {
			Turnout * t = turnoutList->find(id);
			if (t) {
				t->setDefault();
				return List();
			} else {
				return Error("No turnout found !");
			}
		} else {
			for (int i = 0; i < turnoutList->nb(); i++) {
				turnoutList->get(i)->setDefault();
			}
			return List();
		}
	} else if (strcmp(cmd, CMD_SET) == 0) {
		if (id && state) {
			Turnout * t = turnoutList->find(id);
			if (t) {
				t->setDefault();
				return List();
			} else {
				return Error("No turnout found !");
			}
		} else {
			return Error("No id or state !");
		}		 
	}


	
	return "";
}