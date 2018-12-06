#pragma once

#include <exception>
#include <iostream>
#include "DataTypes.h"

class ExpressionTree {
public:
	virtual void output() {
		std::cout << "ExpressionTree" << std::endl;
	}

	virtual int evaluate() {
		std::cout << "ERROR: Evaluate called in base class";
		return -1;
	}
	virtual DataType checkDatatype() = 0;
private:
};
