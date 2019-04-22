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

	~ArrayExpression() {
		delete this->indices;
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
		DataType valuetype = std::get<DataType>(*varInfo);
		// TODO: improve performance by using valuetype = datatype - x
		switch (valuetype) {
		case ByteArray:
			this->type = Byte;
			break;
		case ShortArray:
			this->type = Short;
			break;
		case IntegerArray:
			this->type = Integer;
			break;
		case FloatArray:
			this->type = Float;
			break;
		case BoolArray:
			this->type = Bool;
			break;
		case ReferenceArray:
			this->type = Reference;
			break;
		default:
			std::cout << "ERROR: type " << valuetype << " incompatible with array" << std::endl;
			return Error;
		}
		if (std::get<2>(*varInfo) != indices->size()) {
			std::cout << "ERROR: array expression doesn't have the correct number of indices" << std::endl;
			return Error;
		}
		return this->type;
	}

	void writeCode(CodeGenerator * c) override;
};