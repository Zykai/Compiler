#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class PreUnaryTree : public ExpressionTree {
public:
	PreUnaryTree(ExpressionTree * right, Token * unaryOperator) {
		this->right = right;
		this->unaryOperator = unaryOperator;
	}

	void output() override {
		right->output();
		std::cout << "PreUnary (Negate)" << std::endl;
	}

	DataType checkDatatype() override {
		if (right->checkDatatype() == Bool) return Bool;
		else return Error;
	}

	ExpressionTree * right;
	Token * unaryOperator;
};
