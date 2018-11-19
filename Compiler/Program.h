#pragma once


#include <unordered_map>
#include "Function.h"
#include "Variable.h"

class Program {
public:
	void addGlobal();
	void addFunction();
private:
	std::unordered_map<const char*, Variable> globals;
	std::unordered_map<const char*, Function> functions;

	Function *mainFunction;

};