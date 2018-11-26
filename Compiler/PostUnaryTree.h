#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class PostUnaryTree : public ExpressionTree {
public:
	void output() override {
		left->output();
		std::cout << "PostUnary" << std::endl;
	}
private:
	ExpressionTree * left;
	Token * unaryOperator;
};
