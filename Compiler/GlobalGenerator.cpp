#include "stdafx.h"
#include "ProgramTree.h"
#include "CodeGenerator.h"

void ProgramTree::writeCode(CodeGenerator * c) {
	// Write global variables and starting point (main)
	c->writeInteger(0); // placeholder, becomes location of main function once known
	for (auto a : this->variables) {
		VariableTree * var = a.second;
		std::cout << a.first << "  offset: " << var->offset << std::endl;
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
		if(function.first == "main") function.second->writeCode(c);
	}
}

void FunctionTree::writeCode(CodeGenerator * c){
	// Save current position for function calls
	c->saveFunctionStart();
	// Write statement code
	this->statement->writeCode(c);
}