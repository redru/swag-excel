#pragma once
#include "yaml-cpp/yaml.h"

using namespace std;

class Parameter {

public:
	Parameter(YAML::Node node = YAML::Node());

	string GetName();
	string GetIn();
	string GetType();
	bool IsRequired();

private:
	YAML::Node node;

	string name;
	string in;
	string type;
	bool required;

};
