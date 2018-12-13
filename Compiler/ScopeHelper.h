#pragma once

#include <map>
#include "Scope.h"
#include "DataTypes.h"

class FunctionTree;

class ScopeHelper {
public:
	void beginNewFunction(std::string name, DataType d);
	void addVariable(std::string varName, DataType type);
	void leaveScope();
	void enterScope();
	Scope * topScope;
	Scope * currentScope;
	std::map<std::string, std::list<std::pair<DataType, int>*>> allVariables;
	std::map<std::string, FunctionTree*> * functions;
private:
	DataType currentType;
	std::string currentFunctionName;
	int currentStackSize;
};