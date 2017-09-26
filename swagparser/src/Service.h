#pragma once
#include "yaml-cpp/yaml.h"
#include "Method.h"

using MethodList = std::vector<std::string>;

class Service {

public:
	MethodList GetMethods();

	Method GetMethod(std::string method);

	void SetNode(YAML::Node node);
	YAML::Node GetNode();

	void SetName(std::string name);
	std::string GetName();

private:
	std::string name;
	YAML::Node node;

};
