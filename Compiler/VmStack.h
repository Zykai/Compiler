#pragma once


class VmStack {
public:
	VmStack(unsigned int size);
	~VmStack();

	void setStackPointer(unsigned int position);
	unsigned int getStackPointer();
	void setBottomPointer(unsigned int position);
	unsigned int getBottomPointer();

	void pushInt(int value);
	void pushFloat(float value);
	void pushByte(char value);
	void pushBool(bool value);
	void pushBytes(char * bytes, unsigned int number);

	int popInt();
	float popFloat();
	char popByte();
	bool popBool();

	void storeInt(int value, unsigned int position);
	void storeFloat(float value, unsigned int position);
	void storeChar(char value, unsigned int position);
	void storeBool(bool value, unsigned int position);
	void storePointer(void* pointer, unsigned int position);

	int loadInt(unsigned int position);
	float loadFloat(unsigned int position);
	char loadChar(unsigned int position);
	bool loadBool(unsigned int position);
	void * loadPointer(unsigned int positioin);

	char * popBytes(unsigned int number);
private:
	unsigned int stackPointer;
	unsigned int bottomPointer;
	char * stack;
};