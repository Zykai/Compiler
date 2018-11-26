#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class EqualityTree : public ExpressionTree {
public:
	void output() override {
		left->output();
		right->output();
		std::cout << "Equality" << std::endl;
	}
private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * equalityOperator;
};
