#pragma once
#include <iostream>
#include <vector>

#include "yaml-cpp/yaml.h"
#include "Service.h"

using namespace std;
using Services = vector<Service>;

class Swagger {

public:
	Swagger(string file = "");

	void Load(string file);

	YAML::Node GetNestedNode(string path);

	YAML::Node GetDefinitions();

	Services Swagger::GetServices();

private:
	YAML::Node root_node;
	string file;

};
