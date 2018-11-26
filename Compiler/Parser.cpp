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
	return new ExpressionTree();
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

	}
	return expr;
}

ExpressionTree * Parser::multiplication(){
	ExpressionTree * expr = value();
	while (match({ TokenMultiply, TokenDivide })) {

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
	return new ValueTree(this->getCurrent());
}
