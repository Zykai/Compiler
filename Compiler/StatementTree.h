#pragma once

#include "ScopeHelper.h"

class CodeGenerator;

class StatementTree {
public:
	static void error(std::string message) {
		std::cout << message << std::endl;
		//system("pause");
		//exit(1);
	}
	virtual bool checkForErrors(ScopeHelper * s) = 0;
	virtual void writeCode(CodeGenerator * c) = 0;
};