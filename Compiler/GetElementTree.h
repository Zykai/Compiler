#pragma once

#include <list>
#include "ExpressionTree.h"
#include "Token.h"

class GetElementTree : public ExpressionTree {
public:

private:
	Token * name;
	Token * braceOpen;
	std::list<ExpressionTree> parameters;
	Token * braceClose;
};
