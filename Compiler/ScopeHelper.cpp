#include "stdafx.h"
#include "ScopeHelper.h"
#include "FunctionTree.h"


ScopeHelper::ScopeHelper(){
	this->allVariables = std::map<std::string, std::map<std::string, std::pair<DataType, int>*>>();
}

void ScopeHelper::setGlobalScope(std::list<std::pair<std::string, VariableTree*>>* variables){
	this->currentScope = new Scope(nullptr);
	for (std::pair<std::string, VariableTree*> p : *variables) {
		std::cout << "Added var " << p.first << " to scope" << std::endl;
		currentScope->variables.emplace(p.first, new std::pair<DataType, int>(p.second->type, p.second->offset));
	}
}

void ScopeHelper::setFunctions(std::map<std::string, FunctionTree*>* functions){
	this->functions = functions;
}

void ScopeHelper::beginNewFunction(std::string name, FunctionTree * f){
	this->currentFunctionName = name;
	this->currentType = f->type;
	this->currentStackSize = 0;
	// Set current scope to global scope
	while (this->currentScope->topScope != nullptr) {
		this->currentScope = this->currentScope->topScope;
	}
	for (std::pair<DataType, std::string> p : *f->arguments) {
		this->addVariable(p.second, p.first);
	}
}

void ScopeHelper::addVariable(std::string varName, DataType type){
	int offset = getTypeSize(type);
	int temp = this->currentStackSize;
	this->currentStackSize += offset;
	this->allVariables[this->currentFunctionName].emplace(varName, new std::pair<DataType, int>(type, temp));
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

int ScopeHelper::getVarPosition(std::string functionName, std::string varName){
	return this->allVariables[functionName][varName]->second;
}
