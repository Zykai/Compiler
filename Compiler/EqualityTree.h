#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class EqualityTree : public ExpressionTree {
public:

private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * equalityOperator;
};
