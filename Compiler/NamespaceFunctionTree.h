#pragma once

#include "GetElementTree.h"
#include "StandardLibrary.h"

class NamespaceFunctionTree : public GetElementTree {
public:
	NamespaceFunctionTree(Token * nameSpace, Token * name, std::list<ExpressionTree*> parameters) {
		this->nameSpace = nameSpace;
		this->name = name;
		this->parameters = parameters;
	}

	DataType checkDatatype(ScopeHelper * s) override {
		if (this->nameSpace->getValue() == "std") {
			return StandardLibrary::getInstance()->checkErrors(this->name->getValue(), s, this->parameters);
		}
		// Work-around, since []-operator add values to map
		auto map = *s->functions;
		if (map.find(name->getValue()) == map.end()) {
			std::cout << "ERROR function " << this->name->getValue() << " doesnt exist" << std::endl;
			return Error;
		}
		FunctionTree * calledFunction = (*s->functions).at(name->getValue());
		if (this->parameters.size() != calledFunction->arguments->size()) {
			std::cout << "ERROR: number of parameter not equal to number of arguments in function " << this->name->getValue() << std::endl;
		}
		std::list<std::pair<DataType, std::string>>::iterator arg = calledFunction->arguments->begin();
		int i = 0;
		for (std::list<ExpressionTree*>::iterator param = parameters.begin(); param != parameters.end(); param++, arg++, i++) {
			DataType argumentType = (*param)->checkDatatype(s);
			DataType expectedType = arg->first;
			if (argumentType != expectedType) {
				std::cout << "ERROR in parameter no" << i << "in function call of " << this->name->getValue() << std::endl;
				return Error;
			}
		}
		this->type = calledFunction->type;
		return calledFunction->type;
	}

	void writeCode(CodeGenerator * c) override;

	Token * nameSpace;
};
