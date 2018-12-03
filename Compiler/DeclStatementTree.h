#pragma once

#include "StatementTree.h"
#include "ExpressionTree.h"

class DeclStatementTree : public StatementTree {
public:
	DeclStatementTree(Token * name, int dataType, ExpressionTree * value) {
		this->name = name;
		this->dataType = dataType;
		this->value = value;
	}
	Token * name;
	int dataType;
	ExpressionTree * value;
};