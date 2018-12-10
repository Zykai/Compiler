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
		if (!this->initializer->checkForErrors(s)) {
			this->error("Error in for-declaration");
			return false;
		}
		else if(!this->condition->checkDatatype() != Bool){
			this->error("For-condition statement needs to be of type bool");
			return false;
		}
		else if (!this->condition->checkDatatype() == Error) {
			this->error("Error in for update expression");
			return false;
		}
		else if (!this->forBody->checkForErrors(s)) {
			//this->error("Error in for body");
			return false;
		}
		else {
			return true;
		}
	}
};