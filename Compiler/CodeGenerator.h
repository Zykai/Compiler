#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "ProgramTree.h"
#include "ExpressionTree.h"

class CodeGenerator {
public:
	CodeGenerator(std::string filename);
	~CodeGenerator();

	void writeProgram(ProgramTree * p);
	void writeExpression(ExpressionTree * e);

	void writeInteger(int value);
	void writeByte(unsigned char value);
	void writeFloat(float value);
private:
	std::ofstream * byteFile; // throws compile error when not declared as pointer
};