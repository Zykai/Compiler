#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class LogAndOrTree : public ExpressionTree {
public:

private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * logicalOperator;
};
