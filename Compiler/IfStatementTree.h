#pragma once

#include "StatementTree.h"
#include "ExpressionTree.h"

class IfStatementTree : public StatementTree {
public:
	IfStatementTree(ExpressionTree * condition, StatementTree * ifStatement, StatementTree * elseStatement) {
		this->condition = condition;
		this->ifStatement = ifStatement;
		this->elseStatement = elseStatement;
	}
	ExpressionTree * condition;
	StatementTree * ifStatement;
	StatementTree * elseStatement;

};

