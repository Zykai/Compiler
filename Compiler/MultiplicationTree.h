#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class MultiplicationTree : public ExpressionTree {
public:

private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * mulOperator;
};
