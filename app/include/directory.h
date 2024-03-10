#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "globals.h"

struct Parameters {

	std::unordered_map<std::string, int>* _int_params;
	std::unordered_map<std::string, bool>* _bool_params;
	std::unordered_map<std::string, std::string>* _string_params;
	std::unordered_map<std::string, std::vector<int>>* _int_vect_params;
	std::unordered_map<std::string, std::vector<bool>>* _bool_vect_params;
	std::unordered_map<std::string, std::vector<std::string>>* _string_vect_params;

};

struct File {
	std::string _name;
	std::string _content;
};

// Comp functions
Instruction instruction_type(std::string _input);

// Main class
class Directory {

	int layer;
	std::vector<std::string>* _ivect;
	Parameters* _params_p;
	std::string _name;
	std::vector<Directory>* _subdirs;
	std::vector<File>* _files;

public:

	Directory();
	Directory(Parameters* parent_params, std::vector<std::string>* _ivect);

	bool input_template(std::string _template_name);
	bool validate_template();
	void print_ivect();
	

};