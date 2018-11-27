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


	ExpressionTree * left;
	ExpressionTree * right;
	Token * mulOperator;
};
