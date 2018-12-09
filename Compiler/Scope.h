#pragma once

#include <list>
#include <map>
#include "VariableTree.h"

class Scope {
public:
	Scope * topScope;
	std::map<std::string, VariableTree *> variables;
	std::list<Scope* > subScopes;
	VariableTree * getVariable(std::string name);
};