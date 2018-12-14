#include "stdafx.h"
#include "Scope.h"

std::pair<DataType, int> * Scope::getVariable(std::string name){
	std::pair<DataType, int> * v = this->variables[name];
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
