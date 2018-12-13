#pragma once

#include <utility>
#include <string>
#include <list>

#include "StatementTree.h"

class FunctionTree {
public:
	FunctionTree(std::list<std::pair<DataType, std::string>> * arguments, DataType type, StatementTree * statement) {
		this->arguments = arguments;
		this->type = type;
		this->statement = statement;
	}


	std::list<std::pair<DataType, std::string>> * arguments;
	DataType type;
	StatementTree * statement;
};