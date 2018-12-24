#pragma once
#include <string>
#include "ByteProgram.h"

class VirtualMachine {
public:
	VirtualMachine(std::string name);
	~VirtualMachine();

	void output();
	void executeProgram();
	
private:
	ByteProgram * byteProgram;
};