#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class ComparisonTree : public ExpressionTree {
public:
	ComparisonTree(ExpressionTree * left, ExpressionTree * right, Token * comparisonOperator) {
		this->left = left;
		this->right = right;
		this->comparisonOperator = comparisonOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Comparison" << std::endl;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		DataType leftType = this->left->checkDatatype(s);
		DataType rightType = this->right->checkDatatype(s);
		if (leftType == Error || leftType == Custom || leftType == Bool) return Error;
		else if (leftType == rightType) return Bool;
		else return Error;
	}

	void writeCode(CodeGenerator * c) override;

	ExpressionTree * left;
	ExpressionTree * right;
	Token * comparisonOperator;
};
