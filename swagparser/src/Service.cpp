#include "Service.h"
Method Service::GetMethod(std::string method) {
	return node[method] ? Method(node[method].as<YAML::Node>()) : Method();
}

MethodList Service::GetMethods() {
	MethodList methods(node.size());

	YAML::const_iterator it;
	int idx;

	for (it = node.begin(), idx = 0; it != node.end(); ++it, idx++) {
		methods[idx] = it->first.as<std::string>();
	}

	return methods;
}

void Service::SetNode(YAML::Node node) {
	this->node = node;
}

YAML::Node Service::GetNode() {
	return node;
}

void Service::SetName(std::string name) {
	this->name = name;
}

std::string Service::GetName() {
	return name;
}
