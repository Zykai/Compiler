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
	void writeLong(long value);

	void addUnfinishedFunctionCall(std::string name);
	std::pair<bool, long> getFunctionPosition(std::string functionName);
	ScopeHelper * scopeHelper;
	std::string currentFunction;
private:
	std::list<std::pair<std::string, long>> unfinishedCalls;
	std::map<std::string, long> functionPositions;
	std::ofstream * byteFile; // throws compile error when not declared as pointer
};