#pragma once

#include "Expressions.h"

class AssignExpressionTree : public ExpressionTree {
public:
	AssignExpressionTree(Token * variable, ExpressionTree * expr) {
		this->variable = variable;
		this->arrayAssign = nullptr;
		this->expr = expr;
	}
	AssignExpressionTree(ArrayExpression * arrayAssign, ExpressionTree * expr) {
		this->variable = nullptr;
		this->arrayAssign = arrayAssign;
		this->expr = expr;
	}
	Token * variable;
	ArrayExpression * arrayAssign;
	ExpressionTree * expr;

	DataType checkDatatype(ScopeHelper * s) override {
		DataType expected;
		if (arrayAssign == nullptr) {
			auto typeInfo = s->currentScope->getVariable(this->variable->getValue());
			expected = std::get<0>(*typeInfo);
		}
		else {
			expected = this->arrayAssign->checkDatatype(s);
		}
		DataType rightType = this->expr->checkDatatype(s);
		if (expected != Error && expected == rightType) {
			if (isArray(expected)) {
				int expectedDimensions = std::get<2>(*s->getVarInformation(variable->getValue()));
				int receivedDimensions;
				if (expr->expressionType == getElement) {
					receivedDimensions = s->getFunction(expr->getName()->getValue())->dimensions;
				}
				else if (expr->expressionType == valueExpr) {
					receivedDimensions = std::get<2>(*s->getVarInformation(expr->getName()->getValue()));
				}
				if(!expectedDimensions == receivedDimensions){
					std::cout << "ERROR: tried to assign array with " << receivedDimensions << " dimensions to array with " << expectedDimensions << "dimensions" << std::endl;
					this->type = Error;
					return Error;
				}
			}
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