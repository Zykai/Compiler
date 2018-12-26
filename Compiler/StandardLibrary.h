#pragma once
#include <map>
#include <functional>
#include "DataTypes.h"
#include <list>
#include "ExpressionTree.h"
#include "ScopeHelper.h"
#include "OperationCodes.h"
#include "CodeGenerator.h"

class StandardLibrary {
public:
	static StandardLibrary * getInstance();
	DataType checkErrors(std::string name, ScopeHelper * s, std::list<ExpressionTree*> parameters);
	void writeCode(std::string name, CodeGenerator * c, std::list<ExpressionTree*> parameters);
private:
	std::map<std::string, std::function<DataType(ScopeHelper * s, std::list<ExpressionTree*> parameters )>> checkTypeFunction;
	std::map<std::string, std::function<void(CodeGenerator * c, std::list<ExpressionTree* >)>> codegenFunction;
	StandardLibrary();
	static StandardLibrary * instance;
};
