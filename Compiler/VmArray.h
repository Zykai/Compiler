#pragma once

template <class T>

class VmArray {
public:
	VmArray<T>(int size, int * dimensionSizes) {
		this->dimensionSizes = dimensionSizes;
		int totalSize = 1;
		for (int i = 0; i < size; i++) {
			totalSize *= dimensionSizes[i];
		}
		this->data = new T[totalSize];
		this->data[0] = 123;
	}
	~VmArray(){
		delete this->dimensionSizes;
		delete[] this->data;
	}
	T getElement(int * indices) {
		return data[0];
	}
	int * dimensionSizes;
	T * data;
};