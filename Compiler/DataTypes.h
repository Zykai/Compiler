#pragma once

#include "Token.h"

enum DataType {
	Byte,
	Short,
	Integer,
	Float,
	Bool,
	Reference,
	Array,
	Custom,
	Error,
	Void,
	String,
	ByteArray,
	ShortArray,
	IntegerArray,
	FloatArray,
	BoolArray,
	ReferenceArray
};

bool isArray(DataType d);
DataType getType(Token * token);
DataType getArrayType(Token * token);
DataType getTypeForLiteral(Token * token);
int getTypeSize(DataType d);