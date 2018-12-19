#include "stdafx.h"

#include "SemanticAnalyser.h"
#include "ExpressionTree.h"

bool SemanticAnalyser::checkForErrors() {
	bool noErrors = true;
	for (auto a : this->program->functions) {
		if (!a.second->checkForErrors(a.first, this->scopeHelper)) {
			std::cout << "Error in function " << a.first << std::endl;
			noErrors = false;
		}
	}
	if (!this->hasMain()) {
		std::cout << "Program is missing a main function" << std::endl;
		noErrors = false;
	}
	if (!noErrors) {
		std::cout << "Errors found in semantic analysis" << std::endl;
	}
	return noErrors;
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

bool SemanticAnalyser::hasMain(){
	return this->program->functions["main"] != nullptr;
}
