#pragma once

#include "Expressions.h"

class AssignExpressionTree : public ExpressionTree {
public:
	AssignExpressionTree(Token * variable, ExpressionTree * value) {
		this->variable = variable;
		this->value = value;
	}
	Token * variable;
	ExpressionTree * value;

	DataType checkDatatype() override {
		return Integer;
	}
};