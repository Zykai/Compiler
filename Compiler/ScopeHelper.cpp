#include "stdafx.h"
#include "ScopeHelper.h"

void ScopeHelper::beginNewFunction(std::string name, DataType d){
	this->currentFunctionName = name;
	this->currentType = d;
	this->currentStackSize = 0;
	// Set current scope to global scope
	while (this->currentScope->topScope != nullptr) {
		this->currentScope = this->currentScope->topScope;
	}
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

void ScopeHelper::enterScope(){
	Scope * subScope = new Scope(this->currentScope);
	this->currentScope->subScopes.emplace_back(subScope);
	this->currentScope = subScope;
}
