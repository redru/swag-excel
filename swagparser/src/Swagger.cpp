#include "Swagger.h"
void Swagger::Load(std::string file) {
	this->file = file;

	root_node = YAML::LoadFile(file);
}

YAML::Node Swagger::GetNestedNode(std::string path) {

}

YAML::Node Swagger::GetDefinitions() {
	return root_node["definitions"] ? root_node["definitions"].as<YAML::Node>() : YAML::Node();
}
