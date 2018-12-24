#include "stdafx.h"
#include "CodeGenerator.h"
#include "StatementHeaders.h"
#include "OperationCodes.h"

void DeclStatementTree::writeCode(CodeGenerator * c){
	std::cout << "DeclStatementTreeBEGIN" << std::endl;
	int varPos = c->scopeHelper->getVarPosition(c->currentFunction, this->name->getValue());
	unsigned char opcode = this->dataType == Integer ? OpCode::I_STORE : this->dataType == Float ? OpCode::F_STORE : this->dataType == Bool ? OpCode::BO_STORE : OpCode::BY_STORE;
	this->value->writeCode(c);
	c->writeByte(opcode);
	c->writeInteger(varPos);
	std::cout << "DeclStatementTreeEND" << std::endl;
}

void ExprStatementTree::writeCode(CodeGenerator * c){
	std::cout << "ExprStatementTree" << std::endl;
	this->expression->writeCode(c);
}

void ForStatementTree::writeCode(CodeGenerator * c){
	std::cout << "ForStatementTree" << std::endl;
	/*
		-init vars
		-save current position
		-write condition test with jump to end (placeholder)
		-write for body
		-write for update
		-write current pos to placeholder
		-jump to previously saved position
	*/
	this->initializer->writeCode(c);
	int beforeLoop = c->getCurrentPosition();
	this->condition->writeCode(c);
	c->writeByte(OpCode::JMP_NOT_EQUAL);
	int jumpPos = c->getCurrentPosition();
	c->writeInteger(0); // ->placeholder
	this->forBody->writeCode(c);
	this->update->writeCode(c);
	c->writeByte(OpCode::JMP);
	c->writeInteger(beforeLoop);
	int posAfterFor = c->getCurrentPosition();
	c->writePrevInteger(posAfterFor, jumpPos);
}

void IfStatementTree::writeCode(CodeGenerator * c){
	std::cout << "IfStatementTree" << std::endl;
	/*
		-write condition
		-write jump if true to pos1(placeholder)
		-write else body
		-write jump to pos2(placeholder)
		-write current pos to pos1
		-write if body
		-write currentpos to pos2
	*/
	this->condition->writeCode(c);
	c->writeByte(OpCode::JMP_NOT_EQUAL);
	int jumpPos = c->getCurrentPosition();
	c->writeInteger(0); // placeholder
	//c->writeInteger(0); // placeholder
	this->ifStatement->writeCode(c);
	int posAfterIf = c->getCurrentPosition();
	if (this->elseStatement != nullptr) {
		c->writeByte(OpCode::JMP);
		int jmpBehindElsePos = c->getCurrentPosition();
		c->writeInteger(0); // placeholder
		int elseStart = c->getCurrentPosition();
		c->writePrevByte(elseStart, jumpPos);
		this->elseStatement->writeCode(c);
		int posAfterElse = c->getCurrentPosition();
		c->writePrevInteger(posAfterElse, jmpBehindElsePos);
	}
	else {
		c->writePrevInteger(posAfterIf, jumpPos);
		std::cout << "LONG: " << posAfterIf << std::endl;
		//c->writePrevInteger(posAfterIf, jumpPos);
	}
}

void ReturnStatementTree::writeCode(CodeGenerator * c){
	std::cout << "ReturnStatementTree" << std::endl;
	std::cout << "CURRENTPOS " << c->getCurrentPosition() << std::endl;
	this->expr->writeCode(c);
	c->writeByte(OpCode::RETURN_32);
}

void StatementListTree::writeCode(CodeGenerator * c){
	std::cout << "StatementListTree" << std::endl;
	for (auto s : *this->statements) {
		s->writeCode(c);
	}
}

void WhileStatementTree::writeCode(CodeGenerator * c){
	std::cout << "WhileStatementTree" << std::endl;
	/*
	-save current position
	-write condition test with jump to end (placeholder)
	-write while body
	-write current pos to placeholder
	-jump to previously saved position
	*/
	int startPos = c->getCurrentPosition();
	this->whileHead->writeCode(c);
	c->writeByte(OpCode::JMP_NOT_EQUAL);
	int posAfterJmp = c->getCurrentPosition();
	c->writeInteger(0); // -> placeholder
	this->whileBody->writeCode(c);
	c->writeByte(OpCode::JMP);
	c->writeInteger(startPos);
	int posAfterBody = c->getCurrentPosition();
	c->writePrevInteger(posAfterBody, posAfterJmp);
}