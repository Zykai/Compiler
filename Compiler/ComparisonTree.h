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
		return Custom;
	}

	ExpressionTree * left;
	ExpressionTree * right;
	Token * comparisonOperator;
};
