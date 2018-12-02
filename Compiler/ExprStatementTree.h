#pragma once

#include "StatementTree.h"
#include "ExpressionTree.h"

class ExprStatementTree : public StatementTree {
public:
	ExprStatementTree(ExpressionTree * expression) {
		this->expression = expression;
	}
	ExpressionTree * expression;
};