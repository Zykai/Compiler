#include "stdafx.h"
#include "Scope.h"

VariableTree * Scope::getVariable(std::string name){
	VariableTree * v = this->variables[name];
	if (v == nullptr) {
		if (topScope != nullptr) {
			return topScope->getVariable(name);
		}
		else {
			return nullptr;
		}
	}
	else {
		return v;
	}
}
