#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class ComparisonTree : public ExpressionTree {
public:

private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * comparisonOperator;
};
