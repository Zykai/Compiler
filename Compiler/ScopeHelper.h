#pragma once

#include <map>
#include "Scope.h"
#include "DataTypes.h"
#include "VariableTree.h"

class FunctionTree;

class ScopeHelper {
public:
	ScopeHelper();
	DataType getCurrentFunctionType();
	int getCurrentFunctionDimensions();
	std::string getCurrentFunctionName();
	void setGlobalScope(std::list<std::pair<std::string, VariableTree*>> * variables);
	void setFunctions(std::map<std::string, FunctionTree*>* functions);
	void beginNewFunction(std::string name, FunctionTree * f);
	void addVariable(std::string varName, DataType type, int dimensions);
	void leaveScope();
	void enterScope();
	int getStackSize(std::string functionName);
	int getVarPosition(std::string functionName, std::string varName);
	FunctionTree * getFunction(std::string name);
	// Tuple structure: type, position, dimensions
	std::tuple<DataType, int, int>* getVarInformation(std::string varName);
	Scope * topScope;
	Scope * currentScope;
	// Tuple structure: type, position, dimensions
	std::map<std::string, std::map<std::string, std::tuple<DataType, int, int>*>> allVariables;
	std::map<std::string, FunctionTree*> * functions;
private:
	std::map<std::string, unsigned int> functionStackSize;
	DataType currentType;
	int currentDimensions;
	std::string currentFunctionName;
	int currentStackSize;
};