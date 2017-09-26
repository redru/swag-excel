#pragma once
#include "yaml-cpp/yaml.h"

using namespace std;
using Tags = std::vector<std::string>;

class Method {

public:
	Method(YAML::Node = YAML::Node());

	string GetOperationId();
	string GetSummary();
	string GetDescription();

private:
	YAML::Node node;

	string operation_id;
	string summary;
	string description;
	Tags tags;
	string security;
	string parameters;
	string responses;

};
