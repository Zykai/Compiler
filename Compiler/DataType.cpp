#include "stdafx.h"

#include "DataTypes.h"
#include <iostream>

DataType getType(Token * token) {
	std::string datatype = token->getValue();
	if (datatype == "int") {
		return Integer;
	}
	else if (datatype == "float") {
		return Float;
	}
	else if (datatype == "short") {
		return Short;
	}
	else if (datatype == "byte") {
		return Byte;
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

DataType getTypeForLiteral(Token * token) {
	Tokentype type = token->getType();
	if (type == integerNumber) return Integer;
	if (type == floatNumber) return Float;
	if (type == identifier) return Custom;
	else return Error;
}