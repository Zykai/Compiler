#include "stdafx.h"

#include "SemanticAnalyser.h"

bool SemanticAnalyser::checkForErrors(ProgramTree * program) {
	return true;
}

bool SemanticAnalyser::checkExpression(ExpressionTree * expr, DataType type){
	return expr->checkDatatype() == type;
}

bool SemanticAnalyser::hasMain(ProgramTree * program){
	return program->functions["main"] != nullptr;
}
