#pragma once


#include "ExpressionTree.h"
#include "Token.h"


class ValueTree : public ExpressionTree {
public:
	ValueTree(Token * value) {
		this->value = value;
		if (this->value->getType() == identifier) {
			this->isVariableType = true;
		}
		this->expressionType = valueExpr;
	}
	void output() override {
		std::cout << "Value: " << value->getValue() << std::endl;
	}

	int evaluate() override {
		return	std::stoi(this->value->getValue());
	}
	
	Token * getName() override {
		if (this->isVariableType) {
			return value;
		}
		return nullptr;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		if (this->value->getType() == identifier) {
			std::tuple<DataType, int, int> * var = s->currentScope->getVariable(this->value->getValue());
			if (var != nullptr) {
				DataType type = std::get<0>(*var);
				this->type = type;
				return type;
			}
			else {
				return Error;
			}
		}
		else {
			DataType t = getTypeForLiteral(this->value);
			this->type = t;
			return t;
		}
	}

	void writeCode(CodeGenerator * c) override;

	// either a literal or a identifier
	Token * value;
};
