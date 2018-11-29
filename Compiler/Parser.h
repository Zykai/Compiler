#pragma once
#include <list>
#include "Token.h"
#include "Expressions.h"
#include "ProgramTree.h"


enum DataType {
	Byte = 1,
	Short = 2,
	Integer = 4,
	Float = 4
};

class Parser {
public:
	Parser();
	void setTokenList(std::list<Token>* list);
	void startParsing();


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
	//ExpressionTree * parseExpression();
	ExpressionTree * logAndOr();
	ExpressionTree * equality();
	ExpressionTree * comparison();
	ExpressionTree * addition();
	ExpressionTree * multiplication();
	ExpressionTree * preUnary();
	ExpressionTree * postUnary();
	ExpressionTree * getElement();
	ExpressionTree * value();
	

	Token * literalValue();

	bool parseSemicolon();

	DataType getType(Token * token);
	int getOffset(DataType newVar);
	int currentOffset;
};