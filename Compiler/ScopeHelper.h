#pragma once

#include <map>
#include "Scope.h"
#include "DataTypes.h"
#include "VariableTree.h"

class FunctionTree;

class ScopeHelper {
public:
	ScopeHelper();
	void setGlobalScope(std::map<std::string, VariableTree*> * variables);
	void setFunctions(std::map<std::string, FunctionTree*>* functions);
	void beginNewFunction(std::string name, FunctionTree * f);
	void addVariable(std::string varName, DataType type);
	void leaveScope();
	void enterScope();
	int getVarPosition(std::string functionName, std::string varName);
	Scope * topScope;
	Scope * currentScope;
	std::map<std::string, std::map<std::string, std::pair<DataType, int>*>> allVariables;
	std::map<std::string, FunctionTree*> * functions;
private:
	DataType currentType;
	std::string currentFunctionName;
	int currentStackSize;
};