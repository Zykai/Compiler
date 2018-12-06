#pragma once

#include <list>
#include "ExpressionTree.h"
#include "Token.h"

class GetElementTree : public ExpressionTree {
public:
	GetElementTree(Token * name, std::list<ExpressionTree*> parameters) {
		this->name = name;
		this->parameters = parameters;
	}

	void output() override {
		std::cout << "Function " << name->getValue() << " with " << parameters.size() << " parameters" << std::endl;
		
	}

	DataType checkDatatype() override {
		return Custom;
	}

	Token * name;
	std::list<ExpressionTree*> parameters;
};
