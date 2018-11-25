#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class PostUnaryTree : public ExpressionTree {
public:

private:
	ExpressionTree * left;
	Token * unaryOperator;
};
