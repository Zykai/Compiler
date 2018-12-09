#pragma once


#include "ExpressionTree.h"
#include "Token.h"


class ValueTree : public ExpressionTree {
public:
	ValueTree(Token * value) {
		this->value = value;
	}
	void output() override {
		std::cout << "Value: " << value->getValue() << std::endl;
	}

	int evaluate() override {
		return	std::stoi(this->value->getValue());
	}

	DataType checkDatatype() override {
		if (this->value->getType() == identifier) return Error;
		return getTypeForLiteral(this->value);
	}

	// either a literal or a identifier
	Token * value;
};
