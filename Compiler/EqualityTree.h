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

	ExpressionTree * left;
	ExpressionTree * right;
	Token * equalityOperator;
};
