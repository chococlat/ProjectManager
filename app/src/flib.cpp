#include "globals.h"
#include "flib.h"

struct File {
	std::string _name;
	std::string _content;
};

struct Directory {
	std::string _name;
	std::vector<Directory>* _subdirs;
	std::vector<File>* _files;
};

struct Parameters {

	std::unordered_map<std::string, int> *_int_params;
	std::unordered_map<std::string, bool>* _bool_params;
	std::unordered_map<std::string, std::string>* _string_params;
	std::unordered_map<std::string, std::vector<int>>* _int_vect_params;
	std::unordered_map<std::string, std::vector<bool>>* _bool_vect_params;
	std::unordered_map<std::string, std::vector<std::string>>* _string_vect_params;

};

std::vector<std::string>* file2vect(fs::path _path){

	std::ifstream file(_path);
	std::vector<std::string>* _ivect = new std::vector<std::string>;
	if (!file.is_open()) {
		std::cerr << "Failed to open file.\n";
	
	}
	else {
		std::string line;
		while (std::getline(file, line)) {
			_ivect->push_back(line);
			// print_raw(line);

		}
		file.close();
	}
	
	return _ivect;
}

void write_file(std::string _content, fs::path _path){
	std::ofstream file(_path);
	if (!file.is_open()) {
		std::cerr << "Failed to create file.\n";
	}
	file << _content;
	file.close();
}

void print_raw(std::string s) {
	for (char& c : s) {
		if (c == '\n') {
			std::cout << "\\n";
		}
		else if (c == '\t') {
			std::cout << "\\t";
		}
		else if (c == '\r') {
			std::cout << "\\r";
		}
		else if (c == '\b') {
			std::cout << "\\b";
		}
		else {
			std::cout << c;
		}
		
	}std::cout << "\n";
}


bool validate_template(std::string _template_name) {

	bool result = true;
	fs::path config_path = TEMPLATE_PATH / _template_name / "_config.dc";
	std::vector<std::string>* _ivect = file2vect(config_path);

	// Validate .dc File
	int counter = 0;
	for (auto vi = _ivect->begin(); vi != _ivect->end(); vi++) {
		counter++;

		// Find not allowed characters
		for (auto& c : *vi) {
			if (ALLOWED_CHARACTERS.find(c) == ALLOWED_CHARACTERS.end()) {
				std::cout << "Invalid characters found. (line " << counter << ") '" << c << "'\n";
				result = false;
			}
		}

		// Remove carriage return
		for (auto i = (*vi).begin(); i != (*vi).end();) {
			if (*i == '\r') {
				(*vi).erase(i);
			}
			else {
				i++;
			}
		}

		// Replace /t with /s/s/s/s
		for (auto i = (*vi).begin(); i != (*vi).end();) {
			if (*i == '\t') {
				(*vi).erase(i);
				i = (*vi).insert(i, 4, ' ') + 4;
			}
			else {
				i++;
			}
		}
	}
	return result;
}
