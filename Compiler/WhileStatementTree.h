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

	bool checkForErrors(ScopeHelper * s) override {
		if (!this->whileHead->checkDatatype(s) == Bool) {
			this->error("While-head expression needs to be of type bool");
			return false;
		}
		s->enterScope();
		if (!this->whileBody->checkForErrors(s)) {
			//this->error("Error in for if body");
			return false;
		}
		s->leaveScope();
		return true;
	}

	void writeCode(CodeGenerator * c) override;
};