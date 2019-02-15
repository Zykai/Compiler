#pragma once

#include <list>
#include "StatementTree.h"
#include "ExpressionTree.h"

class DeclArrayStmtTree : public StatementTree {
public:
	DeclArrayStmtTree(Token * name, DataType dataType, int dimensions, std::list<ExpressionTree*> * sizes) {
		this->name = name;
		this->dataType = dataType;
		this->dimensions = dimensions;
		this->sizes = sizes;
	}

	Token * name;
	DataType dataType;
	int dimensions;
	std::list<ExpressionTree*> * sizes; // is declared as NEW

	bool checkForErrors(ScopeHelper * s) override {
		for (auto size : *this->sizes) {
			if (size->checkDatatype(s) != Integer) {
				std::cout << "ERROR: array access requires integer variables" << std::endl;
				return false;
			}
		}
		if (this->dimensions != this->sizes->size()) {
			std::cout << "ERROR: incorrect array size" << std::endl;
			return false;
		}
		s->addVariable(this->name->getValue(), this->dataType, this->dimensions);
		return true;
	}

	void writeCode(CodeGenerator * c) override;
};