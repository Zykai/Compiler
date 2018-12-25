#pragma once
class test{};

class ByteProgram {
public:
	ByteProgram() {}
	ByteProgram(int stackSize);
	ByteProgram(char * bytecode, int length);
	~ByteProgram();

	void setPosition(int position);
	int getPosition();

	char getNextOpCode();
	int getNextInt();
	float getNextFloat();
	bool getNextBool();
	char getNextChar();
	char * getNextBytes(int number);

	unsigned char getCharAt(int position);
	int getIntAt(int position);
	long getLongAt(int position);
	void output();
private:
	int stackPosition;
	int stackSize;
	char* data;
};