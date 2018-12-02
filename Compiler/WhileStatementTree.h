#pragma once

#include "StatementTree.h"

class WhileStatementTree : public StatementTree{
public:
	WhileStatementTree(ExpressionTree * whileHead, StatementTree * whileBody) {
		this->whileHead = whileHead;
		this->whileBody = whileBody;
	}
	ExpressionTree * whileHead;
	StatementTree * whileBody;
};