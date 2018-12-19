#pragma once

#include "ExpressionTree.h"
#include "Token.h"


class AdditionTree : public ExpressionTree  {
public:
	AdditionTree(ExpressionTree * left, ExpressionTree * right, Token * addOperator) {
		this->left = left;
		this->right = right;
		this->addOperator = addOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Addition" << std::endl;
	}

	int evaluate() override {
		return left->evaluate() + right->evaluate();
	}

	DataType checkDatatype(ScopeHelper * s) override {
		DataType leftType = this->left->checkDatatype(s);
		DataType rightType = this->right->checkDatatype(s);
		if (leftType == Error || leftType == Custom || leftType == Bool) return Error;
		else if (leftType == rightType) return leftType;
		else return Error;
	}

	void writeCode(CodeGenerator * c) override;

	ExpressionTree * left;
	ExpressionTree * right;
	Token * addOperator;

};