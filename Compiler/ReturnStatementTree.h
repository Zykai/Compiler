#pragma once

#include "StatementTree.h"
#include "Expressions.h"

class ReturnStatementTree : public StatementTree {
public:
	ReturnStatementTree(ExpressionTree * expr) {
		this->expr = expr;
	}
	ExpressionTree * expr;

	bool checkForErrors(ScopeHelper * s) override {
		DataType returnType = this->expr == nullptr ? Void : this->expr->checkDatatype(s);
		DataType expectedType = s->getCurrentFunctionType();
		if (returnType != expectedType) {
			this->error("Error in return statement expression");
			return false;
		}
		else {
			if (isArray(returnType)) {
				// Check wether returned dimensions equal array dimensions
				ArrayExpression * arr = static_cast<ArrayExpression*>(this->expr);
				
				int returnedDimensions;
				if (expr->expressionType == valueExpr){
					returnedDimensions = std::get<2>(*s->getVarInformation(arr->var->getValue()));
				}
				else if (expr->expressionType == getElement) {
					returnedDimensions = s->getFunction(expr->getName()->getValue())->dimensions;
				}
				else {
					std::cout << "ERROR: array type is neither getElement or valueExpr (compiler error)" << std::endl;
					exit(1);
				}
				int expectedDimensions = s->getCurrentFunctionDimensions();
				bool b = returnedDimensions == expectedDimensions;
				if (!b) {
					std::cout << "Error: tried to return array with " << returnedDimensions << " in function with " << expectedDimensions << "dimensions" << std::endl;
				}
				return b;
			}
			return true;
		}
	}

	void writeCode(CodeGenerator * c) override;
};
