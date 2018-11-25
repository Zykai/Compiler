#pragma once

#include "ExpressionTree.h"
#include "Token.h"


class AdditionTree : public ExpressionTree  {
public:

private:
	ExpressionTree * left;
	ExpressionTree * right;
	Token * addOperator;

};