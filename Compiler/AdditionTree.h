#pragma once

#include "ExpressionTree.h"
#include "Token.h"


class AdditionTree : public ExpressionTree  {
public:
	AdditionTree(ExpressionTree * left, ExpressionTree * right, Token * addOperator) {
		this->left = left;
		this->right = right;
		this->addOperator = addOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Addition" << std::endl;
	}

	int evaluate() override {
		return left->evaluate() + right->evaluate();
	}

	ExpressionTree * left;
	ExpressionTree * right;
	Token * addOperator;

};