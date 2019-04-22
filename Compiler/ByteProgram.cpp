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

void ByteProgram::setPosition(int position){
	this->stackPosition = position;
}

int ByteProgram::getPosition(){
	return this->stackPosition;
}

OpCode::OpCode ByteProgram::getNextOpCode(){
	OpCode::OpCode opcode = static_cast<OpCode::OpCode>(this->data[stackPosition]);
	stackPosition++;
	return opcode;
}

int ByteProgram::getNextInt(){
	char * bytes = this->getNextBytes(sizeof(int));
	int temp;
	std::memcpy(&temp, bytes, sizeof(int));
	return temp;
}

float ByteProgram::getNextFloat(){
	char * bytes = this->getNextBytes(sizeof(float));
	float temp;
	std::memcpy(&temp, bytes, sizeof(float));
	return temp;
}

bool ByteProgram::getNextBool(){
	char * bytes = this->getNextBytes(sizeof(bool));
	bool temp;
	std::memcpy(&temp, bytes, sizeof(bool));
	return temp;
}

char ByteProgram::getNextChar(){
	char character = this->data[stackPosition];
	stackPosition++;
	return character;
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
	std::cout << "The file size is " << this->stackSize << " bytes" << std::endl;
	for (int i = 0; i < this->stackSize; i++) {
		std::cout << (int)data[i] << " ";
	}
	std::cout << std::endl;
}

char * ByteProgram::getNextBytes(int number){
	char * bytes = &this->data[stackPosition];
	this->stackPosition += number;
	return bytes;
}
