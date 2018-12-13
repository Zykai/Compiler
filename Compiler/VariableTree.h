#pragma once
//#include "ValueTree.h"
#include <iostream>
#include "Token.h"

class VariableTree {
public:
	VariableTree(Token * value, int type, int offset) {
		this->value = value;
		this->type = type;
		this->offset = offset;
	}
	void output() {
		std::cout << type << "  " << value->getValue() << " at position " << offset;
	}

	Token * value;
	int type;
	int offset; // Position on stack
};