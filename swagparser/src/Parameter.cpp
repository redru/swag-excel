#include "Parameter.h"
Parameter::Parameter(YAML::Node node) : node(node) {
	if (node["name"]) name = node["name"].as<string>();
	if (node["in"]) in = node["in"].as<string>();
	if (node["type"]) type = node["type"].as<string>();
	if (node["required"]) required = node["required"].as<bool>();
}

string Parameter::GetName() {
	return name;
}

string Parameter::GetIn() {
	return in;
}

string Parameter::GetType() {
	return type;
}

bool Parameter::IsRequired() {
	return required;
}
