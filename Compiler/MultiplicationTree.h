#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class MultiplicationTree : public ExpressionTree {
public:
	void output() override {
		left->output();
		right->output();
		std::cout << "Multiplication" << std::endl;
	}
private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * mulOperator;
};
