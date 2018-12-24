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
		this->byteProgram = new ByteProgram(data, size);
	}
	else {
		std::cout << "ERROR: FILE " << name << " DOES NOT EXIST\n";
		system("pause");
		exit(1);
	}
}

VirtualMachine::~VirtualMachine(){
	delete this->byteProgram;
}

void VirtualMachine::output() {
	this->byteProgram->output();
}

void VirtualMachine::executeProgram(){
	while (true) {
		char opcode = this->byteProgram->getNextOpCode();
		switch (opcode) {
		case OpCode::JMP:
			break;
		case OpCode::JMP_EQUAL:
			break;
		case OpCode::JMP_NOT_EQUAL:
			break;
		case OpCode::CALL_FUNCTION:
			break;
		case OpCode::RETURN:
			break;
		case OpCode::RETURN_32:
			break;
		case OpCode::FUNCTION_END:
			break;
		case OpCode::LOAD_GLOBAL_32:
			break;
		case OpCode::LOAD_CONSTANT_32:
			break;
		case OpCode::LOAD_CONSTANT_8:
			break;
		case OpCode::I_LOAD:
			break;
		case OpCode::I_STORE:
			break;
		case OpCode::I_ADD:
			break;
		case OpCode::I_SUB:
			break;
		case OpCode::I_MUL:
			break;
		case OpCode::I_DIV:
			break;
		case OpCode::I_MOD:
			break;
		case OpCode::I_INC:
			break;
		case OpCode::I_LESS_THAN:
			break;
		case OpCode::I_LESS_EQUAL:
			break;
		case OpCode::I_BIGGER_THAN:
			break;
		case OpCode::I_Bigger_EQUAL:
			break;
		case OpCode::I_EQUAL:
			break;
		case OpCode::I_NOT_EQUAL:
			break;
		case OpCode::I_FROM_F:
			break;
		case OpCode::F_LOAD:
			break;
		case OpCode::F_STORE:
			break;
		case OpCode::F_ADD:
			break;
		case OpCode::F_SUB:
			break;
		case OpCode::F_MUL:
			break;
		case OpCode::F_DIV:
			break;
		case OpCode::F_MOD:
			break;
		case OpCode::F_INC:
			break;
		case OpCode::F_LESS_THAN:
			break;
		case OpCode::F_LESS_EQUAL:
			break;
		case OpCode::F_BIGGER_THAN:
			break;
		case OpCode::F_Bigger_EQUAL:
			break;
		case OpCode::F_EQUAL:
			break;
		case OpCode::F_NOT_EQUAL:
			break;
		case OpCode::F_FROM_I:
			break;
		case OpCode::BY_LOAD:
			break;
		case OpCode::BY_STORE:
			break;
		case OpCode::BY_ADD:
			break;
		case OpCode::BY_SUB:
			break;
		case OpCode::BY_MUL:
			break;
		case OpCode::BY_DIV:
			break;
		case OpCode::BY_MOD:
			break;
		case OpCode::BY_INC:
			break;
		case OpCode::BY_LESS_THAN:
			break;
		case OpCode::BY_LESS_EQUAL:
			break;
		case OpCode::BY_BIGGER_THAN:
			break;
		case OpCode::BY_Bigger_EQUAL:
			break;
		case OpCode::BY_EQUAL:
			break;
		case OpCode::BY_NOT_EQUAL:
			break;
		case OpCode::BO_LOAD:
			break;
		case OpCode::BO_STORE:
			break;
		case OpCode::BO_EQUAL:
			break;
		case OpCode::BO_NOT_EQUAL:
			break;
		case OpCode::BO_AND:
			break;
		case OpCode::BO_OR:
			break;
		case OpCode::BO_XOR:
			break;
		case OpCode::BO_NEGATE:
			break;
		case OpCode::B_FROM_I:
			break;
		case OpCode::B_FROM_F:
		default:
			std::cout << "ERROR: unknown/not implemented operation code " << opcode << std::endl;
			exit(1);
		}
	}
}
