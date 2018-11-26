#pragma once

#include <list>
#include "ExpressionTree.h"
#include "Token.h"

class GetElementTree : public ExpressionTree {
public:
	void output() override {
		std::cout << "getElement" << std::endl;
	}
private:
	Token * name;
	Token * braceOpen;
	std::list<ExpressionTree> parameters;
	Token * braceClose;
};
