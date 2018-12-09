#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class ComparisonTree : public ExpressionTree {
public:
	ComparisonTree(ExpressionTree * left, ExpressionTree * right, Token * comparisonOperator) {
		this->left = left;
		this->right = right;
		this->comparisonOperator = comparisonOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Comparison" << std::endl;
	}

	DataType checkDatatype() override {
		DataType leftType = this->left->checkDatatype();
		DataType rightType = this->right->checkDatatype();
		if (leftType == Error || leftType == Custom || leftType == Bool) return Error;
		else if (leftType == rightType) return Bool;
		else return Error;
	}

	ExpressionTree * left;
	ExpressionTree * right;
	Token * comparisonOperator;
};
