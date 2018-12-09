#include "stdafx.h"
#include "ScopeHelper.h"

void ScopeHelper::beginNewFunction(std::string name){
	this->currentFunctionName = name;
	this->currentStackSize = 0;
}

void ScopeHelper::addVariable(std::string varName, VariableTree * variable){
	this->allVariables[this->currentFunctionName].emplace_back(variable);
	this->currentScope->variables.emplace(varName, variable);
}

void ScopeHelper::leaveScope(){
	this->currentScope = this->currentScope->topScope;
}

void ScopeHelper::enterScope(Scope * newScope){
	this->currentScope->subScopes.emplace_back(newScope);
	this->currentScope = newScope;
}
