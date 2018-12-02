#pragma once

#include <utility>
#include <string>
#include <list>

#include "StatementTree.h"

class FunctionTree {
public:
	FunctionTree(std::list<std::pair<int, std::string>> * arguments, int type, StatementTree * statement) {
		this->arguments = arguments;
		this->type = type;
		this->statement = statement;
	}


	std::list<std::pair<int, std::string>> * arguments;
	int type;
	StatementTree * statement;
};