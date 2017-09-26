#include <iostream>
#include <fstream>
#include <assert.h>

#include "yaml-cpp/yaml.h"
#include "libxl\libxl.h"
#include "Swagger.h"

using namespace std;
using namespace libxl;

std::string src_file = "";
std::string target_file = "";

int line = 2;
int col = 0;

void createInfoSheet(YAML::Node node, Sheet* sheet);
void createServicesSheet(YAML::Node node, Sheet* sheet);
void createDefinitionsSheet(YAML::Node node, Sheet* sheet);
void writeValueTo(YAML::Node node, Sheet* sheet, std::string key, int x, int y, bool log = false);
bool fileExists(const std::string& name);
void newLine();
void resetPositional();

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Invalid number of arguments. Expected " << 2 << " but found " << argc - 1 << std::endl;
		return 1;
	}

	src_file = argv[1];
	target_file = argv[2];

	if (!fileExists(src_file)) {
		std::cout << "Sorce file " << src_file << " does not exsits" << std::endl;
		return 1;
	}

	/* YAML::Node swagger = YAML::LoadFile(src_file);

	Book* book = xlCreateBook();

	Sheet* info_sheet = book->addSheet("Info");
	Sheet* services_sheet = book->addSheet("Services");
	Sheet* definitions_sheet = book->addSheet("Definitions");

	createInfoSheet(swagger, info_sheet);
	createDefinitionsSheet(swagger, definitions_sheet);
	createServicesSheet(swagger, services_sheet);

	book->save(target_file.c_str());
	book->release(); */

	Swagger swagger(src_file);
	Services services = swagger.GetServices();
	cout << services[0].GetMethod("post").GetDescription() << endl;

	return 0;
}

void createInfoSheet(YAML::Node node, Sheet* sheet) {
	std::cout << "----> Sheet [" << sheet->name() << "]" << std::endl;

	int counter = 1;

	sheet->writeStr(counter, 0, "Swagger");
	writeValueTo(node, sheet, "swagger", counter++, 1, true);

	sheet->writeStr(counter++, 0, "Info");
	YAML::Node info_node = node["info"].as<YAML::Node>();

	sheet->writeStr(counter, 0, "Description");
	writeValueTo(info_node, sheet, "description", counter++, 1, true);

	sheet->writeStr(counter, 0, "Version");
	writeValueTo(info_node, sheet, "version", counter++, 1, true);

	sheet->writeStr(counter, 0, "Title");
	writeValueTo(info_node, sheet, "title", counter++, 1, true);

	sheet->writeStr(counter++, 0, "Contact");
	YAML::Node contact_node = info_node["contact"].as<YAML::Node>();

	sheet->writeStr(counter, 0, "Email");
	writeValueTo(contact_node, sheet, "email", counter++, 1, true);
}

void createDefinitionsSheet(YAML::Node node, Sheet* sheet) {
	YAML::Node def_node = node["definitions"].as<YAML::Node>();
	std::cout << "----> Sheet [" << sheet->name() << "]" << std::endl;
	std::cout << "Definitions found: " << def_node.size() << std::endl;

	// Reset position to 1, 0
	resetPositional();

	// Write header line
	sheet->writeStr(1, 0, "Definition");
	sheet->writeStr(1, 1, "Description");
	sheet->writeStr(1, 2, "Property");
	sheet->writeStr(1, 3, "Type");

	// Declare loop variables
	std::string def_name = "";
	YAML::Node def;
	YAML::Node def_properties;
	YAML::Node prop;

	// Iterate over all definitions
	for (YAML::const_iterator it = def_node.begin(); it != def_node.end(); ++it) {

		std::cout << "- " + it->first.as<std::string>() << std::endl;
		def = it->second.as<YAML::Node>();
		def_name = it->first.as<std::string>();

		// Write first line with full description
		sheet->writeStr(line, col++, def_name.c_str());
		writeValueTo(def, sheet, "description", line, col);
		newLine();
		
		// If properties are defined for this Definition, proceed
		if (def["properties"]) {
			def_properties = def["properties"].as<YAML::Node>();
			for (YAML::const_iterator prop_it = def_properties.begin(); prop_it != def_properties.end(); ++prop_it, newLine()) {
				// Write a new line with Definition data

				// Definition name
				sheet->writeStr(line, col++, def_name.c_str());

				// Definition description
				sheet->writeStr(line, col++, "//");

				// Definition property name
				sheet->writeStr(line, col++, prop_it->first.as<std::string>().c_str());
				prop = prop_it->second.as<YAML::Node>();

				// Definition property type
				writeValueTo(prop, sheet, "type", line, col++);
			}
		}
	}
}

void createServicesSheet(YAML::Node node, Sheet* sheet) {
	YAML::Node paths_node = node["paths"].as<YAML::Node>();
	std::cout << "----> Sheet [" << sheet->name() << "]" << std::endl;
	std::cout << "Services found: " << paths_node.size() << std::endl;

	resetPositional();

	// Write header line
	sheet->writeStr(1, 0, "Service");
	sheet->writeStr(1, 1, "Description");
	sheet->writeStr(1, 2, "Method");
	sheet->writeStr(1, 3, "Parameters");

	// Declare loop variables
	std::string service_name = "";
	YAML::Node service;

	// Iterate over all paths
	for (YAML::const_iterator it = paths_node.begin(); it != paths_node.end(); ++it) {
		std::cout << "- " + it->first.as<std::string>() << std::endl;
		service = it->second.as<YAML::Node>();
		service_name = it->first.as<std::string>();

		// Write first line with full description
		sheet->writeStr(line, col++, service_name.c_str());
		writeValueTo(service, sheet, "description", line, col);
		newLine();

		// If properties are defined for this Definition, proceed
		/* if (def["properties"]) {
			def_properties = def["properties"].as<YAML::Node>();
			for (YAML::const_iterator prop_it = def_properties.begin(); prop_it != def_properties.end(); ++prop_it, newLine()) {
				// Write a new line with Definition data

				// Definition name
				sheet->writeStr(line, col++, def_name.c_str());

				// Definition description
				sheet->writeStr(line, col++, "//");

				// Definition property name
				sheet->writeStr(line, col++, prop_it->first.as<std::string>().c_str());
				prop = prop_it->second.as<YAML::Node>();

				// Definition property type
				writeValueTo(prop, sheet, "type", line, col++);
			}
		} */
	}
}

void writeValueTo(YAML::Node node, Sheet* sheet, std::string key, int x, int y, bool log) {
	if (node[key]) {
		sheet->writeStr(x, y, node[key].as<std::string>().c_str());
		
		if (log) {
			std::cout << "[" + std::to_string(x) + "," + std::to_string(y) + "] " << key << ": " << node[key].as<std::string>().c_str() << std::endl;
		}
	}
}

bool fileExists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void newLine() {
	line++;
	col = 0;
}

void resetPositional() {
	line = 1;
	col = 0;
}
