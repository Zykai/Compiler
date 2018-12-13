#pragma once

#include <exception>
#include <iostream>
#include "DataTypes.h"
#include "ScopeHelper.h"

class ExpressionTree {
public:
	virtual void output() {
		std::cout << "ExpressionTree" << std::endl;
	}

	virtual int evaluate() {
		std::cout << "ERROR: Evaluate called in base class";
		return -1;
	}
	virtual DataType checkDatatype(ScopeHelper * s) = 0;
private:
};
