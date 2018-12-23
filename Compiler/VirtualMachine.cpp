#include "stdafx.h"
#include "VirtualMachine.h"
#include <iostream>
#include <fstream>
#include "OperationCodes.h"

VirtualMachine::VirtualMachine(std::string name){
	std::streampos size;
	char * data;
	std::ifstream bytecodeFile = std::ifstream(name, std::ios::in | std::ios::binary | std::ios::ate);
	if (bytecodeFile.is_open()) {
		size = bytecodeFile.tellg();
		data = new char[size];
		bytecodeFile.seekg(0, std::ios::beg);
		bytecodeFile.read(data, size);
		bytecodeFile.close();
		std::cout << "The file size is " << size << " bytes" << std::endl;
		this->stack = new Stack(data, size);
	}
	else {
		std::cout << "ERROR: FILE " << name << " DOES NOT EXIST\n";
		system("pause");
		exit(1);
	}
}

VirtualMachine::~VirtualMachine(){
	delete this->stack;
}

void VirtualMachine::output() {
	this->stack->output();
}

void VirtualMachine::executeProgram(){
	while (true) {
		char opcode = this->stack->getNextOpCode();
		switch (opcode) {
		case OpCode::BO_STORE:
			std::cout << "STORE\n";
			break;
		}
	}
}
