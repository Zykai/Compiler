#include "stdafx.h"
#include "ProgramTree.h"
#include "CodeGenerator.h"

void ProgramTree::writeCode(CodeGenerator * c) {
	// Write global variables and starting point (main)

	// Write functions
	/*
	for (auto function : this->functions) {
		c->currentFunction = function.first;
		function.second->writeCode(c);
	}
	*/
	// Debug
	c->currentFunction = "main";
	this->functions["main"]->writeCode(c);
}

void FunctionTree::writeCode(CodeGenerator * c){
	// Save current position for function calls
	c->saveFunctionStart();
	// Write statement code
	this->statement->writeCode(c);
}