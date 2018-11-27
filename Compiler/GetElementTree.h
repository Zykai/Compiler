#pragma once

#include <list>
#include "ExpressionTree.h"
#include "Token.h"

class GetElementTree : public ExpressionTree {
public:
	GetElementTree(Token * name, Token * braceOpen, std::list<ExpressionTree> parameters, Token * braceClose) {
		this->name = name;
		this->braceOpen = braceOpen;
		this->parameters = parameters;
		this->braceClose = braceClose;
	}

	void output() override {
		std::cout << "getElement" << std::endl;
	}

	Token * name;
	Token * braceOpen;
	std::list<ExpressionTree> parameters; // maybe turn into a pointer
	Token * braceClose;
};
