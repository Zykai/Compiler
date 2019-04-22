#include "stdafx.h"
#include "StandardLibrary.h"

StandardLibrary * StandardLibrary::instance = nullptr;

StandardLibrary * StandardLibrary::getInstance(){
	if (StandardLibrary::instance == nullptr) {
		StandardLibrary::instance = new StandardLibrary();
	}
	return StandardLibrary::instance;
}

DataType StandardLibrary::checkErrors(std::string name, ScopeHelper * s, std::list<ExpressionTree*> parameters){
	if (this->checkTypeFunction.find(name) == this->checkTypeFunction.end()) {
		std::cout << "Function " << name << " does not exist in the standard libary" << std::endl;
		return Error;
	}
	else {
		return this->checkTypeFunction[name](s, parameters);
	}
}

void StandardLibrary::writeCode(std::string name, CodeGenerator * c, std::list<ExpressionTree*> parameters){
	this->codegenFunction[name](c, parameters);
}

StandardLibrary::StandardLibrary(){
	this->checkTypeFunction["print"] = [&](ScopeHelper * s, std::list<ExpressionTree*> parameters) {
		int size = parameters.size();
		for (auto & p : parameters) {
			DataType t = p->checkDatatype(s);
			if (t == Error || t == Custom || t == Void) {
				std::cout << "Error in standard library function print" << std::endl;
				return Error;
			}
		}
		return Void;
	};
	this->codegenFunction["print"] = [&](CodeGenerator * c, std::list<ExpressionTree*> parameters) {
		for (auto & p : parameters) {
			DataType t = p->type;
			switch (t) {
			case Integer:
				p->writeCode(c);
				c->writeByte(OpCode::I_PRINT);
				break;
			case Float:
				p->writeCode(c);
				c->writeByte(OpCode::F_PRINT);
				break;
			case Byte:
				p->writeCode(c);
				c->writeByte(OpCode::BY_PRINT);
				break;
			case Bool:
				p->writeCode(c);
				c->writeByte(OpCode::BO_PRINT);
				break;
			case String:
				c->writeByte(OpCode::STR_PRINT);
				p->writeCode(c);
				break;
			default:
				std::cout << "Error in code generation, illegal type" << std::endl;
				exit(1);
			}
		}
	};
	this->checkTypeFunction["len"] = [&](ScopeHelper * s, std::list<ExpressionTree*> parameters) {
		int size = parameters.size();
		if (size != 2) {
			std::cout << "Error in std.len: 2 arguments are required" << std::endl;
			return Error;
		}
		auto iter = parameters.begin();
		if (!isArray((*iter)->checkDatatype(s))) {
			std::cout << "Error in std.len: first argument must be an array" << std::endl;
			return Error;
		}
		iter++;
		if ((*iter)->checkDatatype(s) != Integer) {
			std::cout << "Error in std.len: first argument must be an integer" << std::endl;
			return Error;
		}
		return Integer;
	};
	this->codegenFunction["len"] = [&](CodeGenerator * c, std::list<ExpressionTree*> parameters) {
		auto iter = parameters.begin();
		(*iter)->writeCode(c);
		iter++;
		(*iter)->writeCode(c);
		c->writeByte(OpCode::LEN_ARRAY);
	};
}
