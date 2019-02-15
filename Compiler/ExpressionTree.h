#pragma once

#include <exception>
#include <iostream>
#include "DataTypes.h"
#include "ScopeHelper.h"

class CodeGenerator;

class ExpressionTree {
public:
	virtual void output() {
		std::cout << "ExpressionTree" << std::endl;
	}

	virtual int evaluate() {
		std::cout << "ERROR: Evaluate called in base class";
		return -1;
	}
	bool isVariableType = false;
	virtual DataType checkDatatype(ScopeHelper * s) = 0;
	virtual void writeCode(CodeGenerator * c) = 0;
	DataType type = Error; // starts as error, gets assigned in checkDataType
private:
};
