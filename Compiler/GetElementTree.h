#pragma once

#include <list>
#include "ExpressionTree.h"
#include "Token.h"
#include "FunctionTree.h"



class GetElementTree : public ExpressionTree {
public:
	GetElementTree(Token * name, std::list<ExpressionTree*> *  parameters) {
		this->expressionType = getElement;
		this->name = name;
		this->parameters = parameters;
	}

	void output() override {
		std::cout << "Function " << name->getValue() << " with " << parameters->size() << " parameters" << std::endl;
		
	}

	Token * getName() override {
		return this->name;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		// Work-around, since []-operator add values to map
		auto map = *s->functions;
		if (map.find(name->getValue()) == map.end()){
			std::cout << "ERROR function " << this->name->getValue() << " doesnt exist" << std::endl;
			return Error;
		}
		FunctionTree * calledFunction = (*s->functions).at(name->getValue());
		if (this->parameters->size() != calledFunction->arguments->size()) {
			std::cout << "ERROR: number of parameter not equal to number of arguments in function " << this->name->getValue() << std::endl;
		}
		std::list<std::tuple<std::string, DataType, int>>::iterator arg = calledFunction->arguments->begin();
		int i = 0;
		for (std::list<ExpressionTree*>::iterator param = parameters->begin(); param != parameters->end(); param++, arg++, i++) {
			DataType argumentType = (*param)->checkDatatype(s);
			DataType expectedType = std::get<DataType>(*arg);
			if (argumentType != expectedType) {
				std::cout << "ERROR in parameter number " << i << "in function call of " << this->name->getValue() << std::endl;
				this->type = Error;
				return Error;
			}
			if (isArray(expectedType)) {
				int argumentDimensions = std::get<2>(*s->getVarInformation((*param)->getName()->getValue()));
				int expectedDimensions = std::get<2>(*arg);
				if (argumentDimensions != expectedDimensions) {
					std::cout << "ERROR in parameter number " << i << "in function call of " << this->name->getValue() << ": expected parameter dimensions (" << expectedDimensions << ") not equal to received parameter dimensions (" << argumentDimensions << std::endl;
					this->type = Error;
					return Error;
				}
			}
		}
		this->type = calledFunction->type;
		return calledFunction->type;
	}

	void writeCode(CodeGenerator * c) override;
	// name needs to be first element of class for typecast
	Token * name;
	std::list<ExpressionTree*> * parameters;
protected:
	GetElementTree() {}
};
