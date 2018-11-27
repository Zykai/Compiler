#include "stdafx.h"
#include "Parser.h"

#include <iostream>
#include <algorithm>

Parser::Parser() {

}

void Parser::setTokenList(std::list<Token> * list) {
	this->tokenList = list;
	this->currentElement = this->tokenList->begin();
}



void Parser::startParsing() {
	while (this->currentElement != this->tokenList->end()) {
		std::cout << getCurrent()->getDescription() << std::endl;
		currentElement++;
	}
	this->currentElement = this->tokenList->begin();
}

bool Parser::match(std::initializer_list<Tokentype> possibleTypes)
{
	Token * currentToken = this->getCurrent();
	//std::cout << "TO MATCH: " << currentToken->getTypeString() << "  ";
	// reference not possible for some reason
	for (Tokentype pType : possibleTypes) {
		//std::cout << "POSSIBLE: " << pType << "  ";
		if (currentToken->getType() == pType) {
			std::advance(this->currentElement, 1);
			//std::cout << "MATCH" << std::endl;
			return true;
		}
	}
	//std::cout << std::endl;
	return false;
}

Token * Parser::getCurrent(){
	return &*this->currentElement;
}

Token * Parser::getPrevious(){
	return &*std::next(currentElement, -1);
}

Token * Parser::getNext(){
	return &*std::next(currentElement, 1);
}

ExpressionTree * Parser::parseExpression(){
	return addition();
}

ExpressionTree * Parser::logAndOr(){
	ExpressionTree * expr = equality();
	while (match({ logicalAndOr })) {
		ExpressionTree * right = equality();
		expr = new LogAndOrTree(expr, right, this->getPrevious());
	}
	return expr;
}

ExpressionTree * Parser::equality(){
	return new ExpressionTree();
}

ExpressionTree * Parser::comparison(){
	return new ExpressionTree();
}

ExpressionTree * Parser::addition(){
	ExpressionTree * expr = multiplication();
	while (match({ TokenPlus, TokenMinus })) {
		ExpressionTree * right = multiplication();
		expr = new AdditionTree(expr, right, this->getPrevious());
	}
	return expr;
}

ExpressionTree * Parser::multiplication(){
	ExpressionTree * expr = value();
	while (match({ TokenMultiply, TokenDivide })) {
		ExpressionTree * right = value();
		expr = new MultiplicationTree(expr, right, this->getPrevious());
	}
	return expr;
}

ExpressionTree * Parser::preUnary(){
	return new ExpressionTree();
}

ExpressionTree * Parser::postUnary(){
	return new ExpressionTree();
}

ExpressionTree * Parser::getElement(){
	return new ExpressionTree();
}

ExpressionTree * Parser::value(){
	if (match({ identifier, integerNumber, floatNumber })) {
		return new ValueTree(this->getPrevious());
	}
	else {
		// Should never happen in correct program
		std::cout << "ERROR" << std::endl;
		system("pause");
		return nullptr;
		//throw new Exception(); TODO: parsing errors
	}
	
}
