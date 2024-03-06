#pragma once

#include <filesystem>

#include <fstream>
#include <iostream>

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

#include <cstdio>
#include <memory>
#include <stdexcept>

namespace fs = std::filesystem;

extern fs::path TEMPLATE_PATH;
extern std::unordered_set<char> ALLOWED_CHARACTERS;

enum Instruction {
	_ASK,
	_PARAM,
	_FOLDER,
	_FILE,
	_FOR,
	_IF,
	_ELIF,
	_ELSE,
	_SWITCH,
	_COMMENT,
	_EMPTY
};
