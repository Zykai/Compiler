#pragma once

#include "StatementTree.h"
#include "ExpressionTree.h"

class DeclStatementTree : public StatementTree {
public:
	DeclStatementTree(Token * name, DataType dataType, ExpressionTree * value) {
		this->name = name;
		this->dataType = dataType;
		this->value = value;
	}
	Token * name;
	DataType dataType;
	ExpressionTree * value;

	bool checkForErrors(ScopeHelper * s) override {
		s->addVariable(name->getValue(), dataType);
		if (this->value->checkDatatype(s) == dataType) {
			return true;
		}
		else {
			std::cout << "ERROR: datatype of declaration doesnt match expression type";
		}
	}

	void writeCode(CodeGenerator * c) override;
};