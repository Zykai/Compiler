#pragma once

#include "StatementTree.h"
#include "Expressions.h"

class ReturnStatementTree : public StatementTree {
public:
	ReturnStatementTree(ExpressionTree * expr) {
		this->expr = expr;
	}
	ExpressionTree * expr;
};
