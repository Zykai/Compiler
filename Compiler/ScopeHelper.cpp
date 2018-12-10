#include "stdafx.h"
#include "ScopeHelper.h"

void ScopeHelper::beginNewFunction(std::string name, DataType d){
	this->currentFunctionName = name;
	this->currentType = d;
	this->currentStackSize = 0;
}

void ScopeHelper::addVariable(std::string varName, DataType type){
	int offset = getTypeSize(type);
	int temp = this->currentStackSize;
	this->currentStackSize += offset;
	this->allVariables[this->currentFunctionName].emplace_back( new std::pair<DataType, int>(type, temp));
	this->currentScope->variables.emplace(varName, new std::pair<DataType, int>(type, temp));
}

void ScopeHelper::leaveScope(){
	this->currentScope = this->currentScope->topScope;
}

void ScopeHelper::enterScope(Scope * newScope){
	this->currentScope->subScopes.emplace_back(newScope);
	this->currentScope = newScope;
}
