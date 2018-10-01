#include "stdafx.h"

#include "SourceFile.h"

#include <iostream>
#include <fstream>
#include <sstream>

SourceFile::SourceFile(std::string filename) {
	std::ifstream file;
	file.open(filename);

	std::string line;
	
	for (int i = 0; std::getline(file, line); i++) {
		std::cout << "(" << i << ") " << line << std::endl;
	}

	file.close();
}