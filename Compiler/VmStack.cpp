#include "stdafx.h"
#include "VmStack.h"
#include <iostream>

VmStack::VmStack(unsigned int size){
	this->stack = new char[size];
}

VmStack::~VmStack(){
	delete[] stack;
}

void VmStack::setStackPointer(unsigned int position){
	this->stackPointer = position;
}

unsigned int VmStack::getStackPointer(){
	return this->stackPointer;
}

void VmStack::setBottomPointer(unsigned int position){
	this->bottomPointer = position;
}

unsigned int VmStack::getBottomPointer(){
	return this->bottomPointer;
}
	
void VmStack::pushInt(int value){
	std::memcpy(&stack[stackPointer], &value, sizeof(int));
	/*
	char * bytes = reinterpret_cast<char*>(&value);
	this->stack[stackPointer] = bytes[0];
	this->stack[stackPointer+1] = bytes[1];
	this->stack[stackPointer+2] = bytes[2];
	this->stack[stackPointer+3] = bytes[3];
	*/
	this->stackPointer += sizeof(int);
}

void VmStack::pushFloat(float value){
	std::memcpy(&stack[stackPointer], &value, sizeof(float));
	/*
	char * bytes = reinterpret_cast<char*>(&value);
	this->stack[stackPointer] = bytes[0];
	this->stack[stackPointer + 1] = bytes[1];
	this->stack[stackPointer + 2] = bytes[2];
	this->stack[stackPointer + 3] = bytes[3];
	*/
	this->stackPointer += sizeof(float);
}

void VmStack::pushByte(char value){
	this->stack[stackPointer] = value;
	this->stackPointer += sizeof(char);
}

void VmStack::pushBool(bool value){
	std::memcpy(&stack[stackPointer], &value, sizeof(bool));
	this->stackPointer += sizeof(bool);
}

void VmStack::pushBytes(char * bytes, unsigned int number){
	std::memcpy(&stack[stackPointer], bytes, number);
	this->stackPointer += number;
}

int VmStack::popInt(){
	char * bytes = this->popBytes(sizeof(int));
	int temp;
	std::memcpy(&temp, bytes, sizeof(int));
	return temp;
	//return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | (bytes[0]);
}

float VmStack::popFloat(){
	char * bytes = this->popBytes(sizeof(float));
	float temp;
	std::memcpy(&temp, bytes, sizeof(float));
	return temp;
}

char VmStack::popByte(){
	this->stackPointer -= 1;
	char temp = this->stack[stackPointer];
	return temp;
}

bool VmStack::popBool(){
	char * bytes = this->popBytes(sizeof(bool));
	bool temp;
	std::memcpy(&temp, bytes, sizeof(bool));
	return temp;
}

void VmStack::storeInt(int value, unsigned int position){
	std::memcpy(&stack[bottomPointer + position], &value, sizeof(int));
}

void VmStack::storeFloat(float value, unsigned int position){
	std::memcpy(&stack[bottomPointer + position], &value, sizeof(float));
}

void VmStack::storeChar(char value, unsigned int position){
	this->stack[bottomPointer + position] = value;
}

void VmStack::storeBool(bool value, unsigned int position){
	std::memcpy(&stack[bottomPointer + position], &value, sizeof(bool));
}

void VmStack::storePointer(void * pointer, unsigned int position){
	std::memcpy(&stack[bottomPointer + position], &pointer, sizeof(void*));
}

int VmStack::loadInt(unsigned int position){
	int temp;
	std::memcpy(&temp, &this->stack[this->bottomPointer + position], sizeof(int));
	return temp;
}

float VmStack::loadFloat(unsigned int position){
	float temp;
	std::memcpy(&temp, &this->stack[this->bottomPointer + position], sizeof(float));
	return temp;
}

char VmStack::loadChar(unsigned int position){
	return this->stack[bottomPointer + position];
}

bool VmStack::loadBool(unsigned int position){
	bool temp;
	std::memcpy(&temp, &this->stack[this->bottomPointer + position], sizeof(bool));
	return temp;
}

void * VmStack::loadPointer(unsigned int position){
	void * temp;
	std::memcpy(&temp, &this->stack[this->bottomPointer + position], sizeof(void*));
	return temp;
}

char * VmStack::popBytes(unsigned int number){
	this->stackPointer -= number;
	char * bytes = &this->stack[stackPointer];
	return bytes;
}
