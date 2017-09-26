#include "Method.h"
const string Method::Get = "get";
const string Method::Post = "post";
const string Method::Put = "put";
const string Method::Delete = "delete";

Method::Method(YAML::Node node) : node(node) {
	if (node["operationId"]) operation_id = node["operationId"].as<string>();
	if (node["summary"]) summary = node["summary"].as<string>();
	if (node["description"]) description = node["description"].as<string>();

	if (node["parameters"]) {
		YAML::Node parameters_node = node["parameters"].as<YAML::Node>();
		parameters.resize(parameters_node.size());

		YAML::const_iterator it;
		int idx;

		for (it = parameters_node.begin(), idx = 0; it != parameters_node.end(); ++it, idx++) {
			parameters[idx] = Parameter(it->as<YAML::Node>());
		}
	}
}

string Method::GetOperationId() {
	return operation_id;
}

string Method::GetSummary() {
	return summary;
}

string Method::GetDescription() {
	return description;
}

Parameters Method::GetParameters() {
	return parameters;
}
