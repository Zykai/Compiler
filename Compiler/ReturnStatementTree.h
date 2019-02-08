#pragma once

#include "StatementTree.h"
#include "Expressions.h"

class ReturnStatementTree : public StatementTree {
public:
	ReturnStatementTree(ExpressionTree * expr) {
		this->expr = expr;
	}
	ExpressionTree * expr;

	bool checkForErrors(ScopeHelper * s) override {
		DataType returnType = this->expr == nullptr ? Void : this->expr->checkDatatype(s);
		DataType expectedType = s->getCurrentFunctionType();
		if (returnType != expectedType) {
			this->error("Error in return statement expression");
			return false;
		}
		else {
			return true;
		}
	}

	void writeCode(CodeGenerator * c) override;
};
