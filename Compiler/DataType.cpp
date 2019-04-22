#include "stdafx.h"

#include "DataTypes.h"
#include <iostream>

bool isArray(DataType d){
	return d >= ByteArray && d <= ReferenceArray;
}

DataType getType(Token * token) {
	std::string datatype = token->getValue();
	if (datatype == "int") {
		return Integer;
	}
	else if (datatype == "float") {
		return Float;
	}
	else if (datatype == "bool") {
		return Bool;
	}
	else if (datatype == "short") {
		return Short;
	}
	else if (datatype == "byte") {
		return Byte;
	}
	else if (datatype == "void") {
		return Void;
	}
	else if (token->getType() == identifier) {
		return Custom;
	}
	else {
		std::cout << "Expecting data type; found: " << datatype;
		system("pause");
		exit(1);
	}
}

DataType getArrayType(Token * token) {
	std::string datatype = token->getValue();
	if (datatype == "int") {
		return IntegerArray;
	}
	else if (datatype == "float") {
		return FloatArray;
	}
	else if (datatype == "bool") {
		return BoolArray;
	}
	else if (datatype == "short") {
		return ShortArray;
	}
	else if (datatype == "byte") {
		return ByteArray;
	}
	else if (token->getType() == identifier) {
		return ReferenceArray;
	}
	else {
		std::cout << "Expecting data type; found: " << datatype;
		system("pause");
		exit(1);
	}
}

DataType getTypeForLiteral(Token * token) {
	Tokentype type = token->getType();
	if (type == integerNumber) return Integer;
	if (type == floatNumber) return Float;
	if (type == identifier) return Custom;
	if (type == TokenString) return String;
	if (type == TokenBool) return Bool;
	else return Error;
}

int getTypeSize(DataType d) {
	switch (d) {
	case Integer:
		return 4;
	case Float:
		return 4;
	case Bool:
		return sizeof(bool);
	case Byte:
		return 1;
	case Short:
		return 2;
	case Custom:
		return 64;
	default:
		std::cout << "Requested type size for unknown type: " << d << std::endl;
		return 0;
	}
}