#include "Method.h"
Method::Method(YAML::Node node) : node(node) {
	if (node["operationId"]) operation_id = node["operationId"].as<string>();
	if (node["summary"]) summary = node["summary"].as<string>();
	if (node["description"]) description = node["description"].as<string>();
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
