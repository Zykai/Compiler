#pragma once
//#include "ValueTree.h"
#include <iostream>
#include "Token.h"
#include "DataTypes.h"

class VariableTree {
public:
	VariableTree(Token * value, DataType type, int offset) {
		this->value = value;
		this->type = type;
		this->offset = offset;
	}
	void output() {
		std::cout << type << "  " << value->getValue() << " at position " << offset;
	}

	Token * value;
	DataType type;
	int offset; // Position on stack
};