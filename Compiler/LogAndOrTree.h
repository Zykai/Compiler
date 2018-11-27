#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class LogAndOrTree : public ExpressionTree {
public:
	LogAndOrTree(ExpressionTree * left, ExpressionTree * right, Token * logicalOperator) {
		this->left = left;
		this->right = right;
		this->logicalOperator = logicalOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "LogAndOr" << std::endl;
	}

	ExpressionTree * left;
	ExpressionTree * right;
	Token * logicalOperator;
};
