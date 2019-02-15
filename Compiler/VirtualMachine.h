#pragma once
#include <string>
#include "ByteProgram.h"
#include "VmStack.h"
#include "VmArray.h"



class VirtualMachine {
public:
	VirtualMachine(std::string name, long long int maxOperations, bool writeToFile);
	~VirtualMachine();

	void output();
	void executeProgram();
	
private:
	void executeCommand();
	void callFunction(int position);
	void returnFunction(int size);
	void printString();
	template <typename T> void createArray();
	template <typename T> void loadArrayElement();
	template <typename T> void storeArrayElement();
	long long int maxOperations;
	bool notFinished;
	bool writeToFile;
	std::ostream * out;
	VmStack * stack;
	ByteProgram * byteProgram;
};