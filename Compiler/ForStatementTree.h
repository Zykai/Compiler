#pragma once

#include "StatementTree.h"
#include "ExpressionTree.h"


class ForStatementTree : public StatementTree{
public:
	ForStatementTree(StatementTree * initializer, ExpressionTree * condition, ExpressionTree * update, StatementTree * forBody) {
		this->initializer = initializer;
		this->condition = condition;
		this->update = update;
		this->forBody = forBody;
	}
	// Head
	StatementTree * initializer; // needs to be expression or declaration
	ExpressionTree * condition;
	ExpressionTree * update;

	// Body
	StatementTree * forBody;
};