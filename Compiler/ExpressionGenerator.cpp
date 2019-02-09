#include "stdafx.h"
#include "Expressions.h"
#include "OperationCodes.h"
#include "CodeGenerator.h"

void AdditionTree::writeCode(CodeGenerator * c){
	// Reverse order due to stack data access
	this->right->writeCode(c);
	this->left->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_ADD : this->type == Float ? OpCode::F_ADD : OpCode::BY_ADD;
	if (this->addOperator->getValue() == "-") opcode++; // Because sub opcode is ALWAYS directly after add opcode
	c->writeByte(opcode);
}

void AssignExpressionTree::writeCode(CodeGenerator * c){
	int varPos = c->scopeHelper->getVarPosition(c->currentFunction, this->variable->getValue());
	this->value->writeCode(c);

	unsigned char opcode = this->type == Integer ? OpCode::I_STORE : this->type == Float ? OpCode::F_STORE : this->type == Bool ? OpCode::BO_STORE : OpCode::BY_STORE;
	c->writeByte(opcode);
	c->writeInteger(varPos);

	c->writeByte(opcode - 1);
	c->writeBool(varPos);
}

void ComparisonTree::writeCode(CodeGenerator * c){
	// Reverse order due to stack data access
	this->right->writeCode(c);
	this->left->writeCode(c);
	DataType t = left->type; // needs to look at child's type (because type changes from int to bool)
	unsigned char opcode = t == Integer ? OpCode::I_LESS_THAN : t == Float ? OpCode::F_LESS_THAN : OpCode::BY_LESS_THAN;
	// Increase opcode depending on operator
	if (this->comparisonOperator->getValue() == "<=") opcode++;
	else if (this->comparisonOperator->getValue() == ">") opcode += 2;
	else if (this->comparisonOperator->getValue() == ">=") opcode += 3;
	c->writeByte(opcode);
}

void EqualityTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	this->right->writeCode(c);
	DataType t = this->left->type; // needs to look at child's type (because type can change from int to bool)
	unsigned char opcode = t == Integer ? OpCode::I_EQUAL : t == Bool ? OpCode::BO_EQUAL : t == Float ? OpCode::F_EQUAL : OpCode::BY_EQUAL;
	// Increase opcode depending on operator
	if (this->equalityOperator->getValue() == "!=") opcode++;
	c->writeByte(opcode);
}

void GetElementTree::writeCode(CodeGenerator * c){
	for (auto & a : this->parameters) {
		a->writeCode(c);
	}
	c->writeByte(OpCode::CALL_FUNCTION);
	auto functionInfo = c->getFunctionPosition(this->name->getValue());
	if (functionInfo.first) {
		c->writeInteger(functionInfo.second);
	}
	// Function not written yet (in bytecode), position not yet known -> save function call for later
	else {
		c->addUnfinishedFunctionCall(this->name->getValue());
		c->writeInteger(0); // placeholder
	}
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
	// Reverse order due to stack data access
	this->right->writeCode(c);
	this->left->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_MUL : this->type == Float ? OpCode::F_MUL : OpCode::BY_MUL;
	// Increase opcode depending on operator
	if (this->mulOperator->getValue() == "/") opcode++;
	else if (this->mulOperator->getValue() == "%") opcode++;
	c->writeByte(opcode);
}

void NamespaceFunctionTree::writeCode(CodeGenerator * c) {
	StandardLibrary::getInstance()->writeCode(this->name->getValue(), c, this->parameters);
}

void PostUnaryTree::writeCode(CodeGenerator * c){
	this->left->writeCode(c);
	unsigned char opcode = this->type == Integer ? OpCode::I_INC : this->type == Float ? OpCode::F_INC : OpCode::BY_INC;
	c->writeByte(opcode);
}

void PreUnaryTree::writeCode(CodeGenerator * c){
	this->right->writeCode(c);
	c->writeByte(OpCode::BO_NEGATE);
}

void ValueTree::writeCode(CodeGenerator * c){
	// Variables
	if (this->value->getType() == identifier) {
		unsigned char opcode;
		switch (this->type) {
		case Integer:
			opcode = OpCode::I_LOAD;
			break;
		case Float:
			opcode = OpCode::F_LOAD;
			break;
		case Bool:
			opcode = OpCode::BO_LOAD;
			break;
		case Byte:
			opcode = OpCode::BY_LOAD;
			break;
		}
		int varPos = c->scopeHelper->getVarPosition(c->currentFunction, this->value->getValue());
		c->writeByte(opcode);
		c->writeInteger(varPos);
	}
	// Constant values
	else {
		switch (this->type) {
		case Integer:
			c->writeByte(OpCode::LOAD_CONSTANT_32);
			c->writeInteger(std::stoi(this->value->getValue()));
			break;
		case Float:
			c->writeByte(OpCode::LOAD_CONSTANT_32);
			c->writeFloat(std::stof(this->value->getValue()));
			break;
		case String:
			c->writeString(this->value->getValue());
			break;
		case Bool:
			c->writeByte(OpCode::LOAD_CONSTANT_8);
			c->writeBool(this->value->getValue().at(0) == '1' ? true : false);
			break;
		/*
		case byteNumber:
			unsigned char byteValue = std::stoi(this->value->getValue()); // need a converter
			c->writeByte(OpCode::LOAD_CONSTANT_8);
			c->writeByte(byteValue);
			break;
		*/
		}

	}
}