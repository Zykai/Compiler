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


	bool checkForErrors(ScopeHelper * s) override {
		if (this->condition->checkDatatype(s) != Bool) {
			this->error("If-condition expression needs to be of type bool");
			return false;
		}
		s->enterScope();
		if (!this->ifStatement->checkForErrors(s)) {
			//this->error("Error in for if body");
			return false;
		}
		s->leaveScope();
		s->enterScope();
		if (this->elseStatement != nullptr && !this->elseStatement->checkForErrors(s)) {
			//this->error("Error in for else body");
			return false;
		}
		s->leaveScope();
		return true;
	}

	void writeCode(CodeGenerator * c) override;
};

