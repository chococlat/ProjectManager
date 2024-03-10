#include "globals.h"
#include "flib.h"

bool file2vect(fs::path _path, std::vector<std::string>* _ivect){

	std::ifstream file(_path);
	if (!file.is_open()) {
		return false;
	}
	else {
		std::string line;
		while (std::getline(file, line)) {
			_ivect->push_back(line);
		}
		file.close();
		return true;
	}
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

bool extract_f(std::string& _input, std::string* _output, int _offset, int _section, std::vector<std::string>* _substrings){
	
	if (_substrings->size() == 0) return false;
	if (_input.size() < _offset + 1) return false;
	if (std::find(_substrings->begin(), _substrings->end(), "") != _substrings->end()) return false;
	int vi = 0;
	std::string ioutput = "";
	for (int i = _offset; i < _input.length(); i++) {
		if (vi == _section) ioutput += _input[i];
		if (i + (*_substrings)[vi].length() <= _input.length()) {
			bool same = true;
			for (int ci = 0; ci < (*_substrings)[vi].length() && same; ci++) {
				if ((*_substrings)[vi][ci] != _input[i + ci]) same = false;
			}
			if (same) {
				ioutput = ioutput.substr(0, ioutput.size() - 1);
				i += (*_substrings)[vi].length() - 1;
				vi++;
				if (_section == vi == _substrings->size()) ioutput == _input.substr(i, _input.length() - i);
			}
		}
		else break;
	}
	if (vi == _substrings->size()) {
		*_output = ioutput;
		return true;
	}
	else return false;
}

int count_begin_spaces(std::string _input){
	int count = 0;
	for (auto c : _input) {
		if (c == ' ') count++;
		else break;
	}
	return count;
}

void adjust_spaces(std::string& _input, int _n){
	_input.erase(0, count_begin_spaces(_input));
	std::string prefix = "";
	for (auto i = 0; i < _n; i++) prefix += " ";
	_input = prefix + _input;
}

void clean_spaces(std::string& _input){
	bool lbegin = true;
	bool quotes = false;
	std::string temps = "";

	// First traverse
	for (auto i = 0; i < _input.size(); i++) {
		if (_input[i] == '\"') quotes = !quotes;

		if (lbegin) {
			temps += _input[i];
			if (_input[i] != ' ') lbegin = false;
		}
		else {
			if (_input[i] == ' ' && !quotes) {
				for (; i < _input.size(); i++) if (_input[i] != ' ') break;
				if (i != _input.size()) {
					i--;
					temps += _input[i];
				} 
			}else temps += _input[i];
		}
	}
	_input = temps;
	temps = "";

	// Second traverse
	quotes = false;
	for (auto i = 0; i < _input.size(); i++) {
		if (_input[i] == '\"') quotes = !quotes;
		if (_input[i] == '=' && !quotes) {
			if (i > 0 && _input[i - 1] == ' ') {
				temps.erase(temps.size() - 1);
			}
			temps += '=';
			if (i < _input.size() - 1 && _input[i + 1] == ' ') {
				i++;
			}
		}
		else temps += _input[i];
	}
	_input = temps;
}
