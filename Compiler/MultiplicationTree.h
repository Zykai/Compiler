#pragma once

#include "ExpressionTree.h"
#include "Token.h"


class MultiplicationTree : public ExpressionTree {
public:
	MultiplicationTree(ExpressionTree * left, ExpressionTree * right, Token * mulOperator) {
		this->left = left;
		this->right = right;
		this->mulOperator = mulOperator;
	}

	void output() override {
		left->output();
		right->output();
		std::cout << "Multiplication" << std::endl;
	}

	int evaluate() override {
		return left->evaluate() * right->evaluate();
	}

	DataType checkDatatype(ScopeHelper * s) override {
		DataType leftType = this->left->checkDatatype(s);
		DataType rightType = this->right->checkDatatype(s);
		if (leftType == Error || leftType == Custom || leftType == Bool) return Error;
		else if (leftType == rightType) {
			this->type = leftType;
			return leftType;
		}
		else return Error;
	}

	void writeCode(CodeGenerator * c) override;

	ExpressionTree * left;
	ExpressionTree * right;
	Token * mulOperator;
};
