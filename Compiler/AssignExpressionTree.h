#pragma once

#include "Expressions.h"

class AssignExpressionTree : public ExpressionTree {
public:
	AssignExpressionTree(Token * variable, ExpressionTree * value) {
		this->variable = variable;
		this->arrayAssign = nullptr;
		this->value = value;
	}
	AssignExpressionTree(ArrayExpression * arrayAssign, ExpressionTree * value) {
		this->variable = nullptr;
		this->arrayAssign = arrayAssign;
		this->value = value;
	}
	Token * variable;
	ArrayExpression * arrayAssign;
	ExpressionTree * value;

	DataType checkDatatype(ScopeHelper * s) override {
		DataType expected;
		if (arrayAssign == nullptr) {
			auto typeInfo = s->currentScope->getVariable(this->variable->getValue());
			expected = std::get<0>(*typeInfo);
		}
		else {
			expected = this->arrayAssign->checkDatatype(s);
		}
		DataType rightType = this->value->checkDatatype(s);
		if (expected != Error && expected == rightType) {
			this->type = Void;
			return Void;
		}
		else {
			this->type = Error;
			return Error;
		}
	}

	void writeCode(CodeGenerator * c) override;
};