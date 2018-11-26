#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class PreUnaryTree : public ExpressionTree {
public:
	void output() override {
		right->output();
		std::cout << "PreUnary" << std::endl;
	}
private:
	ExpressionTree * right;
	Token * unaryOperator;
};
