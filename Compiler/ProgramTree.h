#pragma once

#include <map>
#include "VariableTree.h"
#include "FunctionTree.h"

class CodeGenerator;

class ProgramTree {
public:
	void output() {
		std::cout << "Imports: " << std::endl;
		for (auto & a : imports) {
			std::cout << "\t" << a.second << std::endl;
		}
		std::cout << "Variables: " << std::endl;
		for (auto & a : variables) {
			std::cout << "\t" << a.first << ", ";
			a.second->output();
			std::cout << std::endl;
		}
		std::cout << "Functions: " << std::endl;
		for (auto & f : functions) {
			std::cout << "\t" << f.first << ", ";
			std::cout << "type: " << f.second->type << std::endl;
			std::cout << "\t\tParameters: " << std::endl << "\t\t\t";
			for (auto & p : *f.second->arguments) {
				std::cout << p.second << ": " << p.first << ", ";
			}

			std::cout << std::endl;
		}
	}

	void writeCode(CodeGenerator * c);

	std::map<std::string, std::string> imports;
	std::list<std::pair<std::string, VariableTree*>> variables;
	std::map<std::string, FunctionTree*> functions;
};