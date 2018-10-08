#include "stdafx.h"

#include "SourceFile.h"

#include <iostream>
#include <fstream>
#include <sstream>

SourceFile::SourceFile(std::string filename) {
	this->textList = std::list<std::string>();
	std::ifstream file;
	file.open(filename);

	std::string line;

	for (int i = 0; std::getline(file, line); i++) {
		textList.emplace_back(line);
	}

	file.close();
}

void SourceFile::print() {
	int i = 1;
	for (std::string &s : textList) {
		std::cout << "(" << i << ") " << s << std::endl;
		i++;
	}
}