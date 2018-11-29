#pragma once

#include <map>
#include "VariableTree.h"

class ProgramTree {
public:
	void output() {
		std::cout << "Imports: " << std::endl;
		for (auto & a : imports) {
			std::cout << a.second << std::endl;
		}
		std::cout << "Variables: " << std::endl;
		for (auto & a : variables) {
			std::cout << a.first << ", ";
			a.second->output();
			std::cout << std::endl;
		}
	}

	std::map<std::string, std::string> imports;
	std::map<std::string, VariableTree*> variables;
};