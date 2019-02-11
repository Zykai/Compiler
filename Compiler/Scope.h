#pragma once

#include <list>
#include <map>
#include "DataTypes.h"

class Scope {
public:
	Scope(Scope * top) {
		this->topScope = top;
		this->variables = std::map<std::string, std::tuple<DataType, int, int>* >();
	}
	Scope * topScope;
	// Datatype, position, dimensions
	std::map<std::string, std::tuple<DataType, int, int>* > variables;
	std::list<Scope* > subScopes;
	std::tuple<DataType, int, int> * getVariable(std::string name);
};