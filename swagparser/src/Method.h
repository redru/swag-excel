#pragma once
#include "yaml-cpp/yaml.h"
#include "Parameter.h"

using namespace std;
using Tags = std::vector<std::string>;
using Parameters = std::vector<Parameter>;

class Method {

public:
	static const string Get;
	static const string Post;
	static const string Put;
	static const string Delete;

public:
	Method(YAML::Node = YAML::Node());

	string GetOperationId();
	string GetSummary();
	string GetDescription();
	Parameters GetParameters();

private:
	YAML::Node node;

	string operation_id;
	string summary;
	string description;
	Tags tags;
	string security;
	Parameters parameters;
	string responses;

};
