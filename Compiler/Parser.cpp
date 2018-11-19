#include "stdafx.h"
#include "Parser.h"

#include <iostream>
#include <algorithm>

Parser::Parser() {
	this->lineNumber = 0;
	this->tokenNumber = 0;
}

void Parser::setTokenList(std::list<std::list<Token>> * list) {
	this->tokenList = list;
	this->currentLine = this->tokenList->begin();
	this->currentToken = currentLine->begin();
}

Token * Parser::getNextToken() {
	if (currentToken != currentLine->end()) {
		std::cout << "BEGIN";
		Token * temp = &*currentToken;
		currentToken++;
		std::cout << "  END\n";
		return temp;
	}
	else if (currentLine != this->tokenList->end()) {
		currentLine++;
		currentToken = currentLine->begin();
		Token * temp = &*currentToken;
		currentToken++;
		//std::cout << currentToken->getDescription() << std::endl;
		//std::cout << "New Size: " << currentLine->size() << std::endl;
		//if (currentLine->cbegin() == currentLine->cend()) std::cout << "BEGIN == END" << std::endl;

		return temp;
	}
	return nullptr;
}

void Parser::startParsing() {
	std::for_each(this->tokenList->begin(), this->tokenList->end(), [&](std::list<Token> e) {
		std::for_each(e.begin(), e.end(), [&](Token t) {
			std::cout << t.getDescription() << std::endl;
		});
	});
}
