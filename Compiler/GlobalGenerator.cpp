#include "stdafx.h"
#include "ProgramTree.h"
#include "CodeGenerator.h"
#include "OperationCodes.h"

void ProgramTree::writeCode(CodeGenerator * c) {
	// Write global variables and starting point (main)
	c->writeInteger(0); // placeholder, becomes location of main function once known
	for (auto a : this->variables) {
		VariableTree * var = a.second;
		switch (var->type) {
		case Integer:
			c->writeInteger(std::stoi(var->value->getValue()));
			break;
		case Float:
			c->writeInteger(std::stof(var->value->getValue()));
			break;
		case Bool:
			c->writeBool(var->value->getValue().at(0) == '1');
			break;
		case Byte:
			c->writeByte(0); // TODO
			break;
		}
	}
	// Write functions
	
	for (auto function : this->functions) {
		if (function.first == "main") {
			int mainPos = c->getCurrentPosition();
			c->writePrevInteger(mainPos, 0);
		}
		c->currentFunction = function.first;
		function.second->writeCode(c);
	}
}

void FunctionTree::writeCode(CodeGenerator * c){
	DataType test = this->type;
	// Save current position for function calls
	c->saveFunctionStart();
	// Write number of parameters
	c->writeInteger(this->arguments->size());
	// Write number of bytes need for the following function
	c->writeInteger(c->scopeHelper->getStackSize(c->currentFunction));
	for (auto a : *this->arguments) {
		switch (std::get<DataType>(a)) {
		case Integer:
			c->writeByte(OpCode::I_LOAD);
			break;
		case Float:
			c->writeByte(OpCode::F_LOAD);
			break;
		case Bool:
			c->writeByte(OpCode::BO_LOAD);
			break;
		case Byte:
			c->writeByte(OpCode::BY_LOAD);
			break;
		case ByteArray:
		case ShortArray:
		case IntegerArray:
		case FloatArray:
		case BoolArray:
		case ReferenceArray:
			c->writeByte(OpCode::REF_LOAD);
			break;
		default:
			std::cout << "Illegal type in function parameters" << std::endl;
			system("pause");
			exit(1);
		}
	}
	
	// Write statement code
	this->statement->writeCode(c);
	// Write function end
	c->writeByte(OpCode::FUNCTION_END);
}