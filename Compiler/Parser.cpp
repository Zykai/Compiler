#include "stdafx.h"
#include "Parser.h"

#include <iostream>
#include <algorithm>

Parser::Parser() {
	this->currentOffset = 0;
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

bool Parser::match(std::initializer_list<Tokentype> possibleTypes){
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

ProgramTree * Parser::parseProgram(){
	return program();
}

ProgramTree * Parser::program(){
	ProgramTree * program = new ProgramTree();
	while (match({ importStmt })) {
		if (!match({ identifier })) {
			std::cout << "ERROR: expected identifier to import";
			exit(1);
			//throw error();
		}
		Token * id = this->getPrevious();
		program->imports.emplace(id->getValue(), id->getValue());
		this->parseSemicolon();
	}
	while (match({ typeName })) {
		Token * typeToken = this->getPrevious();
		DataType dataType = this->getType(typeToken);
		if (!match({ identifier })) {
			std::cout << "ERROR: expected var/func name" << std::endl;
			system("pause");
			exit(1);
		}
		Token * nameToken = this->getPrevious();
		if (match({ assignOperator })) {
			Token * name = getPrevious();
			Token * value = this->literalValue();
			VariableTree * newVar = new VariableTree(value, dataType, this->getOffset(dataType));
			program->variables.emplace(nameToken->getValue() ,newVar);
			this->parseSemicolon();
		}
		else if (match({ parentheseOpen })) {
			std::cout << "FUNCTION" << std::endl;
		}
		else {
			//std::cout << "ERROR: assignment or parenthese";
			//exit(1);
		}
	}
	return program;
}

ExpressionTree * Parser::parseExpression() {
	return logAndOr();
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
	ExpressionTree * expr = comparison();
	while (match({ logicalEqual })) {
		ExpressionTree * right = comparison();
		expr = new EqualityTree(expr, right, this->getPrevious());
	}
	return expr;
}

ExpressionTree * Parser::comparison(){
	ExpressionTree * expr = addition();
	while (match({ logicalComparison })) {
		ExpressionTree * right = addition();
		expr = new ComparisonTree(expr, right, this->getPrevious());
	}
	return expr;
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
	ExpressionTree * expr = preUnary();
	while (match({ TokenMultiply, TokenDivide })) {
		ExpressionTree * right = preUnary();
		expr = new MultiplicationTree(expr, right, this->getPrevious());
	}
	return expr;
}

ExpressionTree * Parser::preUnary(){
	if (match({ TokenNegate })) {
		Token * preOperator = this->getPrevious();
		ExpressionTree * right = preUnary();
		return new PreUnaryTree(right, preOperator);
	}
	else return postUnary();
}

ExpressionTree * Parser::postUnary(){
	ExpressionTree * expr = value();
	while (match({ increment })) {
		expr = new PostUnaryTree(expr, this->getPrevious());
	}
	return expr;
}

ExpressionTree * Parser::getElement(){
	return new ExpressionTree();
}

ExpressionTree * Parser::value(){
	if (match({ identifier, integerNumber, floatNumber })) {
		return new ValueTree(this->getPrevious());
	}
	else if (match({parentheseOpen})) {
		Token * brace = this->getPrevious();
		ExpressionTree * expr = parseExpression();
		if (match({parentheseClose})) {
			Token * bracend = getPrevious();
			return expr;
		}
		else {
			std::cout << "ERROR: missing closing brace" << std::endl;
			system("pause"); // TODO better errors handling
			exit(1);
		}
	}
	else {
		// Should never happen in correct program
		std::cout << "ERROR" << std::endl;
		system("pause");
		exit(1);
		//throw new Exception(); TODO: parsing errors
	}
}

Token * Parser::literalValue() {
	// + String
	if (match({ integerNumber, floatNumber })) {
		this->getPrevious();
	}
	else {
		std::cout << "ERROR: Expected literal value; FOUND: " + getCurrent()->getTypeString() << std::endl;
		system("pause");
		exit(1);
	}
}

bool Parser::parseSemicolon(){
	if (!match({ semicolon })) {
		std::cout << "ERROR: missing semicolon";
		system("pause");
		exit(1);
	}
	return true;
}

DataType Parser::getType(Token * token){
	std::string datatype = token->getValue();
	if (datatype == "int") {
		return Integer;
	}
	else if (datatype == "float") {
		return Float;
	}
	else if (datatype == "short") {
		return Short;
	}
	else if (datatype == "byte") {
		return Byte;
	}
	else {
		std::cout << "ERROR: invalid typename: " << datatype << std::endl;
		system("pause");
		exit(1);
	}

}

int Parser::getOffset(DataType newVar){
	int temp = this->currentOffset;
	this->currentOffset += newVar;
	return temp;
}
