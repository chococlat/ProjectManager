#pragma once
#include "globals.h"
namespace fs = std::filesystem;

// File IO
bool file2vect(fs::path _path, std::vector<std::string>* _ivect);
static void write_file(std::string _content, fs::path _path);
void print_raw(std::string s);

// {a,b,c,d,e}
// 0 1 2 3 4 5

bool extract_f(std::string& _input, std::string* _output, int _offset, int _section, std::vector<std::string> *_substrings);

template<typename ...Args>
inline bool extract(std::string& _input, int _offset, const Args & ...args) {
	std::vector<std::string> *vec = new std::vector<std::string>;
	int currentPos = 0;
	int sectionPos = 0;
	std::string* psi;
	bool foundOutput = false;

	(([&] {

		if constexpr (std::is_same_v<std::string*, Args>) {
			sectionPos = currentPos;
			psi = args;
			foundOutput = true;
		}
		else if constexpr (std::is_convertible_v<Args, std::string>) vec->push_back(args);
		++currentPos;

		}()), ...);

	if (!foundOutput) psi = new std::string;
	return extract_f(_input,psi,_offset,sectionPos,vec);
}

int count_begin_spaces(std::string _input);
void adjust_spaces(std::string& _input, int _n);
void clean_spaces(std::string& _input);