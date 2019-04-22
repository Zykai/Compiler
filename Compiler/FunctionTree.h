#pragma once

#include <utility>
#include <string>
#include <list>

#include "StatementTree.h"

class FunctionTree {
public:
	FunctionTree(std::list<std::tuple<std::string, DataType, int>> * arguments, DataType type, int dimensions, StatementTree * statement) {
		this->arguments = arguments;
		this->type = type;
		this->dimensions = dimensions;
		this->statement = statement;
	}

	bool checkForErrors(std::string name, ScopeHelper * s) {
		s->beginNewFunction(name, this);
		return this->statement->checkForErrors(s);
	}

	void writeCode(CodeGenerator * c);

	std::list<std::tuple<std::string, DataType, int>> * arguments;
	//std::list<std::pair<DataType, std::string>> * arguments;
	DataType type;
	int dimensions;
	StatementTree * statement;
};