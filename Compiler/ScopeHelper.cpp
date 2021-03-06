#include "stdafx.h"
#include "ScopeHelper.h"
#include "FunctionTree.h"


ScopeHelper::ScopeHelper(){
	this->allVariables = std::map<std::string, std::map<std::string, std::tuple<DataType, int, int>*>>();
}

DataType ScopeHelper::getCurrentFunctionType(){
	return this->currentType;
}

int ScopeHelper::getCurrentFunctionDimensions(){
	return this->currentDimensions;
}

std::string ScopeHelper::getCurrentFunctionName(){
	return this->currentFunctionName;
}

void ScopeHelper::setGlobalScope(std::list<std::pair<std::string, VariableTree*>>* variables){
	this->currentScope = new Scope(nullptr);
	for (std::pair<std::string, VariableTree*> p : *variables) {
		currentScope->variables.emplace(p.first, new std::tuple<DataType, int, int>(p.second->type, p.second->offset, 0));
	}
}

void ScopeHelper::setFunctions(std::map<std::string, FunctionTree*>* functions){
	this->functions = functions;
}

void ScopeHelper::beginNewFunction(std::string name, FunctionTree * f){
	this->currentFunctionName = name;
	this->currentType = f->type;
	this->currentStackSize = 0;
	this->currentDimensions = f->dimensions;
	// Set current scope to global scope
	while (this->currentScope->topScope != nullptr) {
		this->currentScope = this->currentScope->topScope;
	}
	for (auto p : *f->arguments) {
		this->addVariable(std::get<std::string>(p), std::get<DataType>(p), std::get<int>(p));
	}
}

void ScopeHelper::addVariable(std::string varName, DataType type, int dimensions){
	int offset;
	if (dimensions > 0) {
		offset = sizeof(void*);
	}
	else {
		offset = getTypeSize(type);
	}
	int varPosition = this->currentStackSize;
	this->currentStackSize += offset;
	this->allVariables[this->currentFunctionName].emplace(varName, new std::tuple<DataType, int, int>(type, varPosition, dimensions));
	this->currentScope->variables.emplace(varName, new std::tuple<DataType, int, int>(type, varPosition, dimensions));
	this->functionStackSize[this->currentFunctionName] = this->currentStackSize;
}

void ScopeHelper::leaveScope(){
	this->currentScope = this->currentScope->topScope;
}

void ScopeHelper::enterScope(){
	Scope * subScope = new Scope(this->currentScope);
	this->currentScope->subScopes.emplace_back(subScope);
	this->currentScope = subScope;
}

int ScopeHelper::getStackSize(std::string functionName){
	return this->functionStackSize[functionName];
}

int ScopeHelper::getVarPosition(std::string functionName, std::string varName){
	return std::get<1>(*this->allVariables[functionName][varName]);
}

FunctionTree * ScopeHelper::getFunction(std::string name){
	if (functions->find(name) == functions->end()) {
		return nullptr;
	}
	else {
		return functions->at(name);
	}
}

std::tuple<DataType, int, int>* ScopeHelper::getVarInformation(std::string varName){
	if (allVariables[currentFunctionName].find(varName) == allVariables[currentFunctionName].end()) {
		return nullptr;
	}
	else {
		return allVariables[currentFunctionName].at(varName);
	}
}
