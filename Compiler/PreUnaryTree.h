#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class PreUnaryTree : public ExpressionTree {
public:

private:
	ExpressionTree * right;
	Token * unaryOperator;
};
