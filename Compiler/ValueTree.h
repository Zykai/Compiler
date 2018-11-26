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
private:
	// either a literal or a identifier
	Token * value;
};
