#include "stdafx.h"

#include "SemanticAnalyser.h"
#include "ExpressionTree.h"

bool SemanticAnalyser::checkForErrors() {
	/*
	FunctionTree * f = program->functions["main"];
	if (f == nullptr) exit(1);
	f->statement->checkForErrors();
	return true;
	*/
	this->scopeHelper->beginNewFunction("main", program->functions["main"]);
	if (program->functions["main"]->statement->checkForErrors(this->scopeHelper)) {
		std::cout << "No errors\n";
		return true;
	}
	std::cout << "ERRORS" << std::endl;
	return false;
}

SemanticAnalyser::SemanticAnalyser(ProgramTree * program){
	this->scopeHelper = new ScopeHelper();
	//this->scopeHelper->currentScope = new Scope(nullptr); // temporary
	this->scopeHelper->setGlobalScope(&program->variables);
	this->scopeHelper->setFunctions(&program->functions);
	this->program = program;
}

bool SemanticAnalyser::checkExpression(ExpressionTree * expr, DataType type){
	return expr->checkDatatype(nullptr) == type;
}

bool SemanticAnalyser::hasMain(ProgramTree * program){
	return program->functions["main"] != nullptr;
}
