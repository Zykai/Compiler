#pragma once
#include <string>
#include "Stack.h"

class VirtualMachine {
public:
	VirtualMachine(std::string name);
	~VirtualMachine();

	void output();
	void executeProgram();
	
private:
	Stack * stack;
};