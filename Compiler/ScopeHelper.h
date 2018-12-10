#pragma once

#include <map>
#include "Scope.h"

class ScopeHelper {
public:
	void beginNewFunction(std::string name, DataType d);
	void addVariable(std::string varName, DataType type);
	void leaveScope();
	void enterScope(Scope * newScope);
	Scope * topScope;
	Scope * currentScope;
	std::map<std::string, std::list<std::pair<DataType, int>*>> allVariables;
private:
	DataType currentType;
	std::string currentFunctionName;
	int currentStackSize;
};