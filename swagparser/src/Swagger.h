#pragma once
#include <iostream>
#include <vector>
#include "yaml-cpp/yaml.h"

class Swagger {

public:
	void Load(std::string file);

	YAML::Node GetNestedNode(std::string path);

	YAML::Node GetDefinitions();

private:
	YAML::Node root_node;
	std::string file;

};
