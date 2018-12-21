#include "stdafx.h"
#include "ProgramTree.h"
#include "CodeGenerator.h"

void ProgramTree::writeCode(CodeGenerator * c) {
	// Write global variables and starting point (main)

	// Write functions
	for (auto function : this->functions) {
		c->currentFunction = function.first;
		function.second->writeCode(c);
	}
}

void FunctionTree::writeCode(CodeGenerator * c){
	// Perhaps write operators

	// Write statement code
	this->statement->writeCode(c);
}