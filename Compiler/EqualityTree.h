#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class EqualityTree : public ExpressionTree {
public:
	EqualityTree(ExpressionTree * left, ExpressionTree * right, Token * equalityOperator) {
		this->left = left;
		this->right = right;
		this->equalityOperator = equalityOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Equality" << std::endl;
	}

	DataType checkDatatype() override {
		DataType leftType = this->left->checkDatatype();
		DataType rightType = this->right->checkDatatype();
		if (leftType == Error || leftType == Custom) return Error;
		else if (leftType == rightType) return Bool;
		else return Error;
	}

	ExpressionTree * left;
	ExpressionTree * right;
	Token * equalityOperator;
};
