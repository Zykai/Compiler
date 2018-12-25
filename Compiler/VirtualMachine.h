#pragma once
#include <string>
#include "ByteProgram.h"
#include "VmStack.h"

class VirtualMachine {
public:
	VirtualMachine(std::string name);
	~VirtualMachine();

	void output();
	void executeProgram();
	
private:
	void callFunction(int position);
	void returnFunction(int size);
	VmStack * stack;
	ByteProgram * byteProgram;
};