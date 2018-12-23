#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class LogAndOrTree : public ExpressionTree {
public:
	LogAndOrTree(ExpressionTree * left, ExpressionTree * right, Token * logicalOperator) {
		this->left = left;
		this->right = right;
		this->logicalOperator = logicalOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "LogAndOr" << std::endl;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		DataType leftType = this->left->checkDatatype(s);
		DataType rightType = this->right->checkDatatype(s);
		if (leftType == Bool && rightType == Bool) {
			this->type = Bool;
			return Bool;
		}
		else return Error;
	}

	void writeCode(CodeGenerator * c) override;

	ExpressionTree * left;
	ExpressionTree * right;
	Token * logicalOperator;
};
