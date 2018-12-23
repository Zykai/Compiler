#pragma once

#include "ExpressionTree.h"
#include "Token.h"

class PostUnaryTree : public ExpressionTree {
public:
	PostUnaryTree(ExpressionTree * left, Token * unaryOperator) {
		this->left = left;
		this->unaryOperator = unaryOperator;
	}

	void output() override {
		left->output();
		std::cout << "PostUnary (inc)" << std::endl;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		DataType t = left->checkDatatype(s);
		if (t == Error || t == Custom || t == Bool) {
			this->type = Error;
			return Error;
		}
		else {
			this->type = t;
			return t;
		}
	}

	void writeCode(CodeGenerator * c) override;

	ExpressionTree * left;
	Token * unaryOperator;
};
