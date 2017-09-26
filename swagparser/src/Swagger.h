#pragma once
#include <iostream>
#include <vector>

#include "yaml-cpp/yaml.h"
#include "Service.h"

using Services = std::vector<Service>;

class Swagger {

public:
	Swagger(std::string file = "");

	void Load(std::string file);

	YAML::Node GetNestedNode(std::string path);

	YAML::Node GetDefinitions();

	Services Swagger::GetServices();

private:
	YAML::Node root_node;
	std::string file;

};
