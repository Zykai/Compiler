#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class EqualityTree : public ExpressionTree {
public:
	EqualityTree(ExpressionTree * left, ExpressionTree * right, Token * equalityOperator) {
		this->left = left;
		this->right = right;
		this->equalityOperator = equalityOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Equality" << std::endl;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		DataType leftType = this->left->checkDatatype(s);
		DataType rightType = this->right->checkDatatype(s);
		if (leftType == Error || leftType == Custom) return Error;
		else if (leftType == rightType) {
			this->type = Bool;
			return Bool;
		}
		else return Error;
	}

	void writeCode(CodeGenerator * c) override;

	ExpressionTree * left;
	ExpressionTree * right;
	Token * equalityOperator;
};
