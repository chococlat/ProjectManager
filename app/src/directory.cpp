#include "directory.h"
#include "flib.h"

Instruction instruction_type(std::string _input) {
	if (extract(_input, 0, "!ask")) return Instruction::_ASK;
	if (extract(_input, 0, "!for")) return Instruction::_FOR;
	if (extract(_input, 0, "!if")) return Instruction::_IF;
	if (extract(_input, 0, "!elif")) return Instruction::_ELIF;
	if (extract(_input, 0, "!else")) return Instruction::_ELSE;
	if (extract(_input, 0, "!switch")) return Instruction::_SWITCH;

}

Directory::Directory(){
	_params_p = new Parameters;
}

Directory::Directory(Parameters* parent_params, std::vector<std::string>* _ivect){
	_params_p = parent_params;
	this->_ivect = _ivect;
}

bool Directory::input_template(std::string _template_name){
	if (_ivect != nullptr) {
		delete _ivect;
	}
	_ivect = new std::vector<std::string>;
	fs::path _config_path = TEMPLATE_PATH / _template_name / "_config.dc";
	return file2vect(_config_path, _ivect);
}

bool Directory::validate_template(){
	
	// First pass
	int counter = 0;
	bool result = true;
	bool counted = false;
	int s_step = 0;

	for (auto vi = _ivect->begin(); vi != _ivect->end();vi++) {
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

		// Replace \t with \s\s\s\s
		for (auto i = (*vi).begin(); i != (*vi).end();) {
			if (*i == '\t') {
				(*vi).erase(i);
				i = (*vi).insert(i, 4, ' ') + 4;
			}
			else {
				i++;
			}
		}

		// Remove unnecessary \s
		clean_spaces(*vi);

		// Adjust indentation
		if (!counted) {
			s_step = count_begin_spaces(*vi);
			if (s_step != 0) counted = true;
			adjust_spaces(*vi, 1);
		}
		else {
			int count = count_begin_spaces(*vi);
			if (count % s_step == 0) {
				adjust_spaces(*vi, count / s_step);
			}
			else {
				result = false;
				std::cout << "E : Bad indentation (Line " << counter << ")\n";
			}
		}
	}

	// Remove empty lines
	for (auto vi = _ivect->begin(); vi != _ivect->end();) {
		
		bool space_only = true;
		for (auto i = (*vi).begin(); i != (*vi).end(); i++) {

			if (*i != ' ') {
				space_only = false;
			}
		}
		if (space_only) {
			vi = _ivect->erase(vi);
		}
		else {
			vi++;
		}
	}

	if (result) std::cout << "Template validated and cleaned.\n";
	return result;
}

void Directory::print_ivect(){
	for (std::string l : *_ivect) {
		std::cout << l << '\n';
	}
}
