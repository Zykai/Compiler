#include "stdafx.h"
#include "Scope.h"

std::pair<DataType, int> * Scope::getVariable(std::string name){
	if (this->variables.find(name) == this->variables.end()) {
		if (topScope != nullptr) {
			return topScope->getVariable(name);
		}
		else {
			return nullptr;
		}
	}
	return this->variables.at(name);
}
