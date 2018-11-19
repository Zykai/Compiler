#pragma once
#include <list>
#include "Token.h"

class Parser {
public:
	Parser();
	void setTokenList(std::list<std::list<Token>>* list);
	void startParsing();
private:
	Token * getNextToken();
	std::list<std::list<Token>>::iterator currentLine;
	std::list<Token>::iterator currentToken;
	int lineNumber, tokenNumber;
	std::list<std::list<Token>>* tokenList;
};