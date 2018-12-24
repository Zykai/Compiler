#pragma once
class test{};

class ByteProgram {
public:
	ByteProgram() {}
	ByteProgram(int stackSize);
	ByteProgram(char * bytecode, int length);
	~ByteProgram();

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