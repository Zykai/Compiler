#include "stdafx.h"
#include "CodeGenerator.h"
#include "StatementHeaders.h"
#include "OperationCodes.h"

void addPopInstruction(CodeGenerator * c, DataType type) {
	switch (type) {
	case Byte:
		c->writeByte(OpCode::BY_POP);
		break;
	case Short:
		//c->writeByte(OpCode::S_POP);
		break;
	case Integer:
		c->writeByte(OpCode::I_POP);
		break;
	case Float:
		c->writeByte(OpCode::F_POP);
		break;
	case Bool:
		c->writeByte(OpCode::BO_POP);
		break;
		//case Double:
		//	break;
	}
}

void DeclArrayStmtTree::writeCode(CodeGenerator * c){
	for (ExpressionTree * e : *this->sizes) {
		e->writeCode(c);
	}
	
	c->writeByte(OpCode::I_CREATE_ARRAY);
	int pos = c->scopeHelper->getVarPosition(c->currentFunction, this->name->getValue());
	c->writeInteger(pos);
	c->writeInteger(this->dimensions);
}

void DeclStatementTree::writeCode(CodeGenerator * c){
	int varPos = c->scopeHelper->getVarPosition(c->currentFunction, this->name->getValue());
	unsigned char opcode = this->dataType == Integer ? OpCode::I_STORE : this->dataType == Float ? OpCode::F_STORE : this->dataType == Bool ? OpCode::BO_STORE : OpCode::BY_STORE;
	this->value->writeCode(c);
	c->writeByte(opcode);
	c->writeInteger(varPos);
}

void ExprStatementTree::writeCode(CodeGenerator * c){
	this->expression->writeCode(c);
	addPopInstruction(c, this->expression->type);
}

void ForStatementTree::writeCode(CodeGenerator * c){
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
	c->writeByte(OpCode::JMP_FALSE);
	int jumpPos = c->getCurrentPosition();
	c->writeInteger(0); // ->placeholder
	this->forBody->writeCode(c);
	this->update->writeCode(c);
	addPopInstruction(c, this->update->type);
	c->writeByte(OpCode::JMP);
	c->writeInteger(beforeLoop);
	int posAfterFor = c->getCurrentPosition();
	c->writePrevInteger(posAfterFor, jumpPos);
}

void IfStatementTree::writeCode(CodeGenerator * c){
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
	c->writeByte(OpCode::JMP_FALSE);
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
		//c->writePrevInteger(posAfterIf, jumpPos);
	}
}

void ReturnStatementTree::writeCode(CodeGenerator * c){
	this->expr->writeCode(c);
	char cmd;
	switch (this->expr->type) {
	case Byte:
		cmd = OpCode::RETURN_8;
		break;
	case Short:
		cmd = OpCode::RETURN_16;
		break;
	case Integer:
		cmd = OpCode::RETURN_32;
		break;
	case Float:
		cmd = OpCode::RETURN_32;
		break;
	case Bool:
		if(sizeof(bool) == 1) cmd = OpCode::RETURN_8;
		else cmd = OpCode::RETURN_32;
		break;
	case Void:
		cmd = OpCode::RETURN;
		break;
	default:
		cmd = Error;
	}
	c->writeByte(OpCode::RETURN_32);
}

void StatementListTree::writeCode(CodeGenerator * c){
	for (auto s : *this->statements) {
		s->writeCode(c);
	}
}

void WhileStatementTree::writeCode(CodeGenerator * c){
	/*
	-save current position
	-write condition test with jump to end (placeholder)
	-write while body
	-write current pos to placeholder
	-jump to previously saved position
	*/
	int startPos = c->getCurrentPosition();
	this->whileHead->writeCode(c);
	c->writeByte(OpCode::JMP_FALSE);
	int posAfterJmp = c->getCurrentPosition();
	c->writeInteger(0); // -> placeholder
	this->whileBody->writeCode(c);
	c->writeByte(OpCode::JMP);
	c->writeInteger(startPos);
	int posAfterBody = c->getCurrentPosition();
	c->writePrevInteger(posAfterBody, posAfterJmp);
}