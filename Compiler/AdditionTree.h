#pragma once

#include "ExpressionTree.h"
#include "Token.h"


class AdditionTree : public ExpressionTree  {
public:
	void output() override {
		left->output();
		right->output();
		std::cout << "Addition" << std::endl;
	}
private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * addOperator;

};