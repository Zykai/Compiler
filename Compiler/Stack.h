#pragma once
class test{};

class Stack {
public:
	Stack() {}
	Stack(int stackSize);
	Stack(char * bytecode, int length);
	~Stack();

	char getNextOpCode();
	int getNextInt();

	unsigned char getCharAt(int position);
	int getIntAt(int position);
	long getLongAt(int position);
	void output();
private:
	int stackPosition;
	int stackSize;
	char* data;
};