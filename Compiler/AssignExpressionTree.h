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

	DataType checkDatatype(ScopeHelper * s) override {
		auto typeInfo = s->currentScope->getVariable(this->variable->getValue());
		DataType expected = std::get<0>(*typeInfo);
		DataType rightType = this->value->checkDatatype(s);
		if (typeInfo != nullptr && rightType != Error && expected == rightType) {
			this->type = expected;
			return expected;
		}
		else {
			this->type = Error;
			return Error;
		}
	}

	void writeCode(CodeGenerator * c) override;
};