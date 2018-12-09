#pragma once

#include "ProgramTree.h"


class SemanticAnalyser {
public:
	bool checkForErrors(ProgramTree * program);
	bool checkExpression(ExpressionTree * expr, DataType type);
	bool hasMain(ProgramTree * program);
};
