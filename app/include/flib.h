#pragma once
#include "globals.h"
namespace fs = std::filesystem;

static std::vector<std::string>* file2vect(fs::path _path);
static void write_file(std::string _content, fs::path _path);
void print_raw(std::string s);

// Template Validation
bool validate_template(std::string _template_name);

