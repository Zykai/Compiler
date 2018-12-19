#pragma once

#include "ProgramTree.h"
#include "ScopeHelper.h"
#include "ExpressionTree.h"

class SemanticAnalyser {
public:
	SemanticAnalyser(ProgramTree * program);
	bool checkForErrors();
	bool checkExpression(ExpressionTree * expr, DataType type);
	bool hasMain();
private:
	ProgramTree * program;
	ScopeHelper * scopeHelper;
};
