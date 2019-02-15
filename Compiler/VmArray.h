#pragma once

template <class T>

class VmArray {
public:
	VmArray<T>(int size, int * dimensionSizes) {
		this->size = size;
		this->dimensionSizes = dimensionSizes;
		int totalSize = 1;
		this->multiplier = new int[size];
		for (int i = 0; i < size; i++) {
			int test = dimensionSizes[i];
			this->multiplier[i] = totalSize;
			totalSize *= dimensionSizes[i];
		}
		this->data = new T[totalSize];
	}
	~VmArray(){
		delete[] this->dimensionSizes;
		delete[] this->data;
		delete[] multiplier;
	}
	T getElement(int * indices) {
		int pos = 0;
		for (int i = 0; i < size; i++) {
			int test = multiplier[size - i - 1];
			int test2 = indices[i];
			pos += multiplier[size - i - 1] * indices[i];
		}
		return data[pos];
	}
	void storeElement(int * indices, T element) {
		int pos = 0;
		for (int i = 0; i < size; i++) {
			int test = multiplier[size - i - 1];
			int test2 = indices[i];
			pos += multiplier[size - i - 1] * indices[i];
		}
		data[pos] = element;
	}
	int * dimensionSizes;
	int * multiplier;
	int size;
	T * data;
};