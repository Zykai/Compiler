#pragma once

#include <list>
#include <map>
#include "DataTypes.h"

class Scope {
public:
	Scope(Scope * top) {
		this->topScope = top;
		this->variables = std::map<std::string, std::pair<DataType, int>* >();
	}
	Scope * topScope;
	std::map<std::string, std::pair<DataType, int>* > variables;
	std::list<Scope* > subScopes;
	std::pair<DataType, int> * getVariable(std::string name);
};