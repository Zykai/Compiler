#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class ComparisonTree : public ExpressionTree {
public:
	void output() override {
		left->output();
		right->output();
		std::cout << "Comparison" << std::endl;
	}
private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * comparisonOperator;
};
