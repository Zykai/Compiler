#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class LogAndOrTree : public ExpressionTree {
public:
	void output() override {
		left->output();
		right->output();
		std::cout << "LogAndOr" << std::endl;
	}
private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * logicalOperator;
};
