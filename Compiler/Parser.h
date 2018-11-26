#pragma once
#include <list>
#include "Token.h"
#include "Expressions.h"

class Parser {
public:
	Parser();
	void setTokenList(std::list<Token>* list);
	void startParsing();

	ExpressionTree * parseExpression(); // public for testing purposes
private:
	std::list<Token> * tokenList;
	std::list<Token>::iterator currentElement;

	bool match(std::initializer_list<Tokentype> possibleTypes);
	Token * getCurrent();
	Token * getPrevious();
	Token * getNext();

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
};