#pragma once
#include <list>
#include "Token.h"
#include "Expressions.h"
#include "ProgramTree.h"
#include "StatementHeaders.h"
#include "DataTypes.h"

class Parser {
public:
	Parser();
	void setTokenList(std::list<Token>* list);


	ProgramTree * parseProgram();
	ExpressionTree * parseExpression(); // public for testing purposes
private:
	std::list<Token> * tokenList;
	std::list<Token>::iterator currentElement;

	bool match(std::initializer_list<Tokentype> possibleTypes);
	Token * getCurrent();
	Token * getPrevious();
	Token * getNext();

	
	ProgramTree * program();
	void parseImports(ProgramTree * program);
	void parseGlobals(ProgramTree * program);
	void parseGlobal(ProgramTree * program, std::string name, DataType dataType);
	void parseFunction(ProgramTree * program, std::string name, DataType dataType);
	std::list<std::pair<DataType, std::string>> * parseParameters();

	StatementTree * statement();
	StatementTree * declStatement();
	StatementTree * listStatement();
	StatementTree * whileStatement();
	StatementTree * forStatement();
	StatementTree * ifStatement();
	StatementTree * returnStatement();
	//ExpressionTree * parseExpression();
	ExpressionTree * assignment();
	ExpressionTree * logAndOr();
	ExpressionTree * equality();
	ExpressionTree * comparison();
	ExpressionTree * addition();
	ExpressionTree * multiplication();
	ExpressionTree * preUnary();
	ExpressionTree * postUnary();
	ExpressionTree * getElement();
	ExpressionTree * value();
	ExpressionTree * functionExpression();
	

	Token * literalValue();

	bool parseSemicolon();

	//DataType getType(Token * token);
	int getVariableSize(DataType var);
	int getOffset(DataType newVar);
	int currentOffset;

	void error(std::string message);
};