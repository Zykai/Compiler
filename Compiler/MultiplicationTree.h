#pragma once

#include "ExpressionTree.h"
#include "Token.h"


class MultiplicationTree : public ExpressionTree {
public:
	MultiplicationTree(ExpressionTree * left, ExpressionTree * right, Token * mulOperator) {
		this->left = left;
		this->right = right;
		this->mulOperator = mulOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Multiplication" << std::endl;
	}

	int evaluate() override {
		return left->evaluate() * right->evaluate();
	}

	DataType checkDatatype() override {
		DataType leftType = this->left->checkDatatype();
		DataType rightType = this->right->checkDatatype();
		if (leftType == Error || leftType == Custom || leftType == Bool) return Error;
		else if (leftType == rightType) return leftType;
		else return Error;
	}

	ExpressionTree * left;
	ExpressionTree * right;
	Token * mulOperator;
};
