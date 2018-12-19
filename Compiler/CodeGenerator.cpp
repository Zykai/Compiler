#include "stdafx.h"
#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(std::string filename){
	this->byteFile = new std::ofstream();
	this->byteFile->open(filename + "c", std::ios::binary | std::ios::trunc | std::ios::out);
}

CodeGenerator::~CodeGenerator(){
	this->byteFile->close();
	delete this->byteFile;
}

void CodeGenerator::writeProgram(ProgramTree * p)
{
}

void CodeGenerator::writeExpression(ExpressionTree * e){
	
}

void CodeGenerator::writeInteger(int value){
	*this->byteFile << value;
}

void CodeGenerator::writeByte(unsigned char value){
	*this->byteFile << value;
}

void CodeGenerator::writeFloat(float value){
	*this->byteFile << value;
}
