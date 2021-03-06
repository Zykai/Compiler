#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "ProgramTree.h"
#include "ExpressionTree.h"

class CodeGenerator {
public:
	CodeGenerator(std::string filename, ProgramTree * program, ScopeHelper * s);
	~CodeGenerator();

	void writeProgram(ProgramTree * p);
	void writeExpression(ExpressionTree * e);

	void writeInteger(int value);
	void writeByte(unsigned char value);
	void writeFloat(float value);
	void writeLong(long value);
	void writeBool(bool value);
	void writeString(std::string value);
	void writePrevInteger(int value, long position);
	void writePrevByte(char value, long position);
	void writeprevFloat(float value, long position);
	void writePrevLong(long value, long position);
	void writePrevBool(bool value, long position);

	int getCurrentPosition();
	void addUnfinishedFunctionCall(std::string name);
	void saveFunctionStart();
	std::pair<bool, int> getFunctionPosition(std::string functionName);
	ScopeHelper * scopeHelper;
	std::string currentFunction;
private:
	std::list<std::pair<std::string, int>> unfinishedCalls;
	std::map<std::string, int> functionPositions;
	std::ofstream * byteFile; // throws compile error when not declared as pointer
	ProgramTree * program;
};