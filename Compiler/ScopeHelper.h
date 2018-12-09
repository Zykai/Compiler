#pragma once

#include <map>
#include "Scope.h"

class ScopeHelper {
public:
	void beginNewFunction(std::string name);
	void addVariable(std::string varName, VariableTree * variable);
	void leaveScope();
	void enterScope(Scope * newScope);
	Scope * topScope;
	Scope * currentScope;
	std::map<std::string, std::list<VariableTree *>> allVariables;
private:
	std::string currentFunctionName;
	int currentStackSize;
};