#include "Swagger.h"
Swagger::Swagger(std::string file) : file(file) {
	if (file != "")
		Load(file);
}

void Swagger::Load(std::string file) {
	this->file = file;

	root_node = YAML::LoadFile(file);
}

YAML::Node Swagger::GetNestedNode(std::string path) {
	return YAML::Node();
}

YAML::Node Swagger::GetDefinitions() {
	return root_node["definitions"] ? root_node["definitions"].as<YAML::Node>() : YAML::Node();
}

Services Swagger::GetServices() {
	if (!root_node["paths"]) return Services(0);

	YAML::Node paths_node = root_node["paths"].as<YAML::Node>();
	Services services(paths_node.size());

	std::cout << "Found " << paths_node.size() << " services" << std::endl;
	YAML::const_iterator it;
	int idx = 0;

	for (it = paths_node.begin(), idx = 0; it != paths_node.end(); ++it, idx++) {
		Service service;
		service.SetName(it->first.as<std::string>());
		service.SetNode(it->second.as<YAML::Node>());

		services[idx] = service;
	}

	return services;
}
