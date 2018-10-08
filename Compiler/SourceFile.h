#pragma once

#include <string>
#include <list>

class SourceFile {
public:
	std::string name;
	std::list<std::string> textList;
	SourceFile(std::string filename);

	void print();
};