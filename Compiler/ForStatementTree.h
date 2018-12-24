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

	bool checkForErrors(ScopeHelper * s) override {
		s->enterScope(); // scope for variables initialized in for-head
		if (!this->initializer->checkForErrors(s)) {
			this->error("Error in for-declaration");
			return false;
		}
		if(!this->condition->checkDatatype(s) == Bool){
			this->error("For-condition statement needs to be of type bool");
			return false;
		}
		if (!this->update->checkDatatype(s) == Error) {
			this->error("Error in for update expression");
			return false;
		}
		s->enterScope();
		if (!this->forBody->checkForErrors(s)) {
			//this->error("Error in for body");
			return false;
		}
		s->leaveScope();
		s->leaveScope(); // leaving for-head scope
		return true;
	}

	void writeCode(CodeGenerator * c) override;
};