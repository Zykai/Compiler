#include "stdafx.h"
#include "Expressions.h"
#include "OperationCodes.h"
#include "CodeGenerator.h"

void AdditionTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	this->right->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_ADD : this->type == Float ? OpCode::F_ADD : OpCode::BY_ADD;
	if (this->addOperator->getValue() == "-") opcode++; // Because sub opcode is ALWAYS directly after add opcode
	c->writeByte(opcode);
}

void AssignExpressionTree::writeCode(CodeGenerator * c){
	
}

void ComparisonTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	this->right->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_LESS_THAN : this->type == Float ? OpCode::F_LESS_THAN : OpCode::BY_LESS_THAN;
	// Increase opcode depending on operator
	if (this->comparisonOperator->getValue() == "<=") opcode++;
	else if (this->comparisonOperator->getValue() == ">") opcode += 2;
	else if (this->comparisonOperator->getValue() == ">=") opcode += 3;
	c->writeByte(opcode);
}

void EqualityTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	this->right->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_EQUAL : this->type == Bool ? OpCode::BO_EQUAL : this->type == Float ? OpCode::F_EQUAL : OpCode::BY_EQUAL;
	// Increase opcode depending on operator
	if (this->equalityOperator->getValue() == "!=") opcode++;
	c->writeByte(opcode);
}

void GetElementTree::writeCode(CodeGenerator * c){

}

void LogAndOrTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	this->right->writeCode(c);
	unsigned char opcode = OpCode::BO_AND;
	// Increase opcode depending on operator
	if (this->logicalOperator->getValue() == "||") opcode++;
	else if (this->logicalOperator->getValue() == "|") opcode += 2;
	c->writeByte(opcode);
}

void MultiplicationTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	this->right->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_MUL : this->type == Float ? OpCode::F_MUL : OpCode::BY_MUL;
	// Increase opcode depending on operator
	if (this->mulOperator->getValue() == "/") opcode++;
	else if (this->mulOperator->getValue() == "%") opcode++;
	c->writeByte(opcode);
}

void PostUnaryTree::writeCode(CodeGenerator * c){

}

void PreUnaryTree::writeCode(CodeGenerator * c){

}

void ValueTree::writeCode(CodeGenerator * c){

}