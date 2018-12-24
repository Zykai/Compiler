#include "stdafx.h"
#include "ByteProgram.h"
#include <iostream>

ByteProgram::ByteProgram(int stackSize){
	this->stackSize = stackSize;
	this->data = new  char[stackSize];
	for (int i = 0; i < stackSize; i++) {
		data[i] = 0x0;
	}
}

ByteProgram::ByteProgram(char * bytecode, int length){
	this->data = bytecode;
	this->stackSize = length;
	this->stackPosition = 0;
}

ByteProgram::~ByteProgram(){
	delete[] data;
}

char ByteProgram::getNextOpCode(){
	char opcode = this->getCharAt(this->stackPosition);
	stackPosition++;
	return opcode;
}

int ByteProgram::getNextInt(){
	int param = this->getIntAt(this->stackPosition);
	stackPosition += 4;
	return param;
}

unsigned char ByteProgram::getCharAt(int position){
	return this->data[position];
}

int ByteProgram::getIntAt(int position){
	return (data[position+3] << 24) | (data[position+2] << 16) | (data[position+1] << 8) | (data[position]);
}

long ByteProgram::getLongAt(int position){
	return ( data[position+7] << 56) | (data[position+6] << 48) | (data[position+5] << 40) | (data[position+4] << 32 | (data[position+3] << 24) | (data[position+2] << 16) | (data[position+1] << 8) | (data[position]));
}

void ByteProgram::output(){
	for (int i = 0; i < this->stackSize; i++) {
		std::cout << (int)data[i] << " ";
	}
	std::cout << "\nRead long: " << this->getLongAt(12) << std::endl;;
}
