#include "stdafx.h"
#include "Stack.h"
#include <iostream>

Stack::Stack(int stackSize){
	this->stackSize = stackSize;
	this->data = new  char[stackSize];
	for (int i = 0; i < stackSize; i++) {
		data[i] = 0x0;
	}
}

Stack::Stack(char * bytecode, int length){
	this->data = bytecode;
	this->stackSize = length;
	this->stackPosition = 0;
}

Stack::~Stack(){
	delete[] data;
}

char Stack::getNextOpCode(){
	char opcode = this->getCharAt(this->stackPosition);
	stackPosition++;
	return opcode;
}

int Stack::getNextInt(){
	int param = this->getIntAt(this->stackPosition);
	stackPosition += 4;
	return param;
}

unsigned char Stack::getCharAt(int position){
	return this->data[position];
}

int Stack::getIntAt(int position){
	return (data[position] << 24) | (data[position+1] << 16) | (data[position+2] << 8) | (data[position+3]);
}

void Stack::output(){
	for (int i = 0; i < this->stackSize; i++) {
		std::cout << (int)data[i] << " ";
	}
}