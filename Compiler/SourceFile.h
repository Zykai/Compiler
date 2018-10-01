#pragma once

#include <string>

class SourceFile {
public:
	std::string name;
	std::string text;

	SourceFile(std::string filename);
};