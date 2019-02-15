#pragma once

#include <list>
#include "ExpressionTree.h"
#include "Token.h"

class ArrayExpression : public ExpressionTree {
public:
	ArrayExpression(Token * var, std::list<ExpressionTree*> * indices, bool store) {
		this->var = var;
		this->indices = indices;
		this->isVariableType = true;
	}

	Token * var;
	std::list<ExpressionTree*> * indices; // NEW
	bool store;

	DataType checkDatatype(ScopeHelper * s) override {
		std::tuple<DataType, int, int> * varInfo = s->getVarInformation(this->var->getValue());
		for (auto i : *this->indices) {
			DataType type = i->checkDatatype(s);
			if (type != Integer) {
				std::cout << "ERROR in array index" << std::endl;
				return Error;
			}
		}
		if (std::get<2>(*varInfo) != indices->size()) {
			std::cout << "ERROR: array expression doesn't have the correct number of indices" << std::endl;
			return Error;
		}
		DataType t = std::get<0>(*varInfo);
		this->type = t;
		return t;
	}

	void writeCode(CodeGenerator * c) override;
};