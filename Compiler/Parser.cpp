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
	this->parseImports(program);
	this->parseGlobals(program);
	return program;
}

void Parser::parseImports(ProgramTree * program){
	while (match({ importStmt })) {
		if (!match({ identifier })) {
			this->error("ERROR: expected identifier to import");
		}
		Token * id = this->getPrevious();
		program->imports.emplace(id->getValue(), id->getValue());
		this->parseSemicolon();
	}
}

void Parser::parseGlobals(ProgramTree * program){
	while (match({ typeName })) {
		Token * typeToken = this->getPrevious();
		DataType dataType = getType(typeToken);
		if (!match({ identifier })) {
			this->error("ERROR: expected var/func name");
		}
		Token * nameToken = this->getPrevious();
		if (match({ assignOperator })) {
			this->parseGlobal(program, nameToken->getValue(), dataType);
		}
		else if (match({ parentheseOpen })) {
			this->parseFunction(program, nameToken->getValue(), dataType);
		}
		else {
			//std::cout << "ERROR: assignment or parenthese";
			//exit(1);
		}
	}
}

void Parser::parseGlobal(ProgramTree * program, std::string name, DataType dataType){
	Token * value = nullptr;
	 value = this->literalValue();
	this->parseSemicolon();
	VariableTree * newVar = new VariableTree(value, dataType, this->getOffset(dataType));
	program->variables.emplace_back(std::make_pair(name, newVar));
}

void Parser::parseFunction(ProgramTree * program, std::string name, DataType dataType){
	auto params = this->parseParameters();
	StatementTree * s = this->statement();
	FunctionTree * f = new FunctionTree(params, dataType, s);
	program->functions.emplace(name, f);
}

std::list<std::pair<DataType, std::string>> * Parser::parseParameters(){
	auto parameterList = new std::list<std::pair<DataType, std::string>>();

	while (match({ typeName })) {
		DataType type = getType(this->getPrevious());
		if (!match({ identifier })) {
			this->error("ERROR: expected identifier; found " + this->getCurrent()->getTypeString());
		}
		std::string parameterName = this->getPrevious()->getValue();
		parameterList->emplace_back(std::pair<DataType, std::string>(type, parameterName));
		match({ TokenComma });
	}
	match({ parentheseClose });
	return parameterList;
}

StatementTree * Parser::statement(){
	if (match({ whileStmt })) {
		return this->whileStatement();
	}
	else if (match({ curlyBracesOpen })) {
		return this->listStatement();
	}
	else if (match({ TokenFor })) {
		return this->forStatement();
	}
	else if (match({ typeName })) {
		return this->declStatement();
	}
	else if (match({ TokenReturn })) {
		return this->returnStatement();
	}
	else if (match({ ifToken })) {
		return this->ifStatement();
	}
	else {
		ExpressionTree * e = this->parseExpression();
		this->parseSemicolon();
		StatementTree * s = new ExprStatementTree(e);
		return s;
	}
	return nullptr;
}

StatementTree * Parser::declStatement(){
	DataType type = getType(this->getPrevious());
	if (match({ TokenSquareBracketOpen })) {
		int dimensions = 1;
		while (match({ TokenComma })) {
			dimensions++;
		}
		if (!match({ TokenSquareBracketClose })) this->error("ERROR: Expected closing brackets of array declaration");
		if (!match({ identifier })) this->error("ERROR: expected identifier after type declaration; found" + this->getCurrent()->getTypeString());
		Token * arrayName = this->getPrevious();
		if (!match({ assignOperator })) this->error("ERROR: expected assignment; found" + this->getCurrent()->getTypeString());
		if (!match({ TokenNew })) this->error("ERROR: expected new for array declaration");
		if (!match({ typeName })) this->error("ERROR: expected typeName after new in array declaration");
		if (!match({ TokenSquareBracketOpen })) this->error("ERROR: expected opening bracket after typeName");
		std::list<ExpressionTree*> * dimensionSizes = new std::list<ExpressionTree*>();
		do {
			ExpressionTree * e = this->parseExpression();
			dimensionSizes->emplace_back(e);
		} while (match({ TokenComma }));
		if (!match({ TokenSquareBracketClose })) this->error("ERROR: expected closing bracket after typeName");
		this->parseSemicolon();
		return new DeclArrayStmtTree(arrayName, type, dimensions, dimensionSizes);
	}
	if (!match({ identifier })) this->error("ERROR: expected identifier after type declaration; found" + this->getCurrent()->getTypeString());
	Token * varName = this->getPrevious();
	if (!match({ assignOperator })) this->error("ERROR: expected assignment; found" + this->getCurrent()->getTypeString());
	ExpressionTree * expr = this->parseExpression();
	this->parseSemicolon();
	return new DeclStatementTree(varName, type, expr);
}

StatementTree * Parser::listStatement(){
	std::list<StatementTree*> * stmtList = new std::list<StatementTree*>();
	do {
		StatementTree * s = this->statement();
		stmtList->emplace_back(s);
	} while (!match({curlyBracesClose}));
	return new StatementListTree(stmtList);
}

StatementTree * Parser::whileStatement(){
	if (!match({ parentheseOpen })) {
		this->error("ERROR: missing opening parenthese after 'while'");
	}
	ExpressionTree * whileHead = this->parseExpression();
	if (!match({ parentheseClose })) {
		this->error("ERROR: missing opening parenthese after while head");
	}
	StatementTree * whileBody = this->statement();
	return new WhileStatementTree(whileHead, whileBody);
}

StatementTree * Parser::forStatement(){
	if (!match({ parentheseOpen })) this->error("ERROR: missing opening parenthese after 'for'");
	StatementTree * init;
	if (this->getCurrent()->getType() == typeName) {
		match({ typeName });
		init = this->declStatement();
	}
	else {
		ExpressionTree * e = this->parseExpression();
		this->parseSemicolon();
		init = new ExprStatementTree(e);
	}
	//if (!match({ semicolon })) this->error("ERROR: missing semicolon in for head");
	ExpressionTree * condition = this->parseExpression();
	if (!match({ semicolon })) this->error("ERROR: missing semicolon in for head");
	ExpressionTree * update = this->parseExpression();
	if (!match({ parentheseClose })) this->error("ERROR: missing closing parenthese in for head");
	StatementTree * forBody = this->statement();
	return new ForStatementTree(init, condition, update, forBody);
}

StatementTree * Parser::ifStatement(){
	if (!match({ parentheseOpen })) this->error("ERROR: missing opening parenthese after 'if'");
	ExpressionTree * condition = this->parseExpression();
	if (!match({ parentheseClose })) this->error("ERROR: missing opening parenthese after if head");
	StatementTree * ifStatement = this->statement();
	StatementTree * elseStatement = nullptr;
	if (match({TokenElse})) {
		elseStatement = this->statement();
	}
	return new IfStatementTree(condition, ifStatement, elseStatement);
}

StatementTree * Parser::returnStatement(){
	if (match({ semicolon })) {
		return new ReturnStatementTree(nullptr);
	}
	ExpressionTree * expr = this->parseExpression();
	this->parseSemicolon();
	return new ReturnStatementTree(expr);
}

ExpressionTree * Parser::parseExpression() {
	return assignment();
}

ExpressionTree * Parser::assignment(){
	ExpressionTree * variable = logAndOr();
	Token * variableName = this->getPrevious();
	if (match({ assignOperator })) {
		if (!variable->isVariableType) {
			this->error("Expected a variable type before assignment operator");
		}
		ArrayExpression * arrayAssign = nullptr;
		if (variableName->getType() == TokenSquareBracketClose) {
			arrayAssign = static_cast<ArrayExpression*>(variable);
			arrayAssign->store = true;
			ExpressionTree * value = logAndOr();
			return new AssignExpressionTree(arrayAssign, value);
		}
		else {
			ExpressionTree * value = logAndOr();
			return new AssignExpressionTree(variableName, value);
		}
		
	}
	return variable;
}

ExpressionTree * Parser::logAndOr(){
	ExpressionTree * expr = equality();
	while (match({ logicalAndOr })) {
		Token * andOrOperator = this->getPrevious();
		ExpressionTree * right = equality();
		expr = new LogAndOrTree(expr, right, andOrOperator);
	}
	return expr;
}

ExpressionTree * Parser::equality(){
	ExpressionTree * expr = comparison();
	while (match({ logicalEqual })) {
		Token * equOperator = this->getPrevious();
		ExpressionTree * right = comparison();
		expr = new EqualityTree(expr, right, equOperator);
	}
	return expr;
}

ExpressionTree * Parser::comparison(){
	ExpressionTree * expr = addition();
	while (match({ logicalComparison })) {
		Token * compOperator = this->getPrevious();
		ExpressionTree * right = addition();
		expr = new ComparisonTree(expr, right, compOperator);
	}
	return expr;
}

ExpressionTree * Parser::addition(){
	ExpressionTree * expr = multiplication();
	while (match({ TokenPlus })) {
		Token * additionOperator = this->getPrevious();
		ExpressionTree * right = multiplication();
		expr = new AdditionTree(expr, right, additionOperator);
	}
	return expr;
}

ExpressionTree * Parser::multiplication(){
	ExpressionTree * expr = preUnary();
	while (match({ TokenMultiply })) {
		Token * mulOperator = this->getPrevious();
		ExpressionTree * right = preUnary();
		expr = new MultiplicationTree(expr, right, mulOperator);
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
	return nullptr;
}

ExpressionTree * Parser::value(){
	if (match({ integerNumber, floatNumber, TokenBool, TokenString })) {
		return new ValueTree(this->getPrevious());
	}
	else if (match({ identifier })) {
		return this->identifierExpression();
	}
	else if (match({parentheseOpen})) {
		ExpressionTree * expr = parseExpression();
		if (match({parentheseClose})) {
			return expr;
		}
		else {
			this->error("ERROR: missing closing brace");
		}
	}
	else {
		this->error("ERROR: expected value; found: " + this->getCurrent()->getDescription());
	}
}

ExpressionTree * Parser::identifierExpression(){
	bool nameSpaceFunction = false;
	Token * name = this->getPrevious();
	if (match({ TokenSquareBracketOpen })) {
		std::list<ExpressionTree*> * indices = new std::list<ExpressionTree*>();
		do {
			indices->emplace_back(this->parseExpression());
		} while (match({ TokenComma }));
		if (!match({ TokenSquareBracketClose })) this->error("Expected closing brackets after in array expression");
		return new ArrayExpression(name, indices, false);
	}
	Token * functionName;
	if (match({ TokenDot })) {
		nameSpaceFunction = true;
		if (!match({ identifier })) {
			this->error("Namespace is missing a function name");
		}
		functionName = this->getPrevious();
	}
	else {
		functionName = name;
	}
	if (match({ parentheseOpen })) {
		std::list<ExpressionTree*> * parameters = new std::list<ExpressionTree*>();
		if (!match({ parentheseClose })) {
			do {
				ExpressionTree * param = this->parseExpression();
				parameters->emplace_back(param);
			} while (match({ TokenComma }));
			if (!match({ parentheseClose })) {
				this->error("Expected closing parenthese to complete function call");
			}
		}
		if (nameSpaceFunction) {
			return new NamespaceFunctionTree(name, functionName, parameters);
		}
		else {
			return new GetElementTree(name, parameters);
		}
	}
	else return new ValueTree(name);
}

Token * Parser::literalValue() {
	// + String
	if (match({ integerNumber, floatNumber, TokenBool })) {
		return this->getPrevious();
	}
	else {
		this->error("ERROR: Expected literal value; FOUND: " + getCurrent()->getTypeString());
		return nullptr;
	}
}

bool Parser::parseSemicolon(){
	if (!match({ semicolon })) {
		this->error("ERROR: missing semicolon");
	}
	return true;
}

int Parser::getVariableSize(DataType var){
	switch (var) {
	case Byte:
		return 1;
	case Short:
		return 2;
	case Integer:
		return 4;
	case Float:
		return 4;
	case Bool:
		return sizeof(bool);
	case Custom:
		return 0;
	default:
		this->error("ERROR: invalid typename: " + var);
		return -1;
	}

}

int Parser::getOffset(DataType newVar){
	int temp = this->currentOffset;
	this->currentOffset += this->getVariableSize(newVar);
	return temp;
}

void Parser::error(std::string message){
	std::cout << message << std::endl;
	system("pause");
	exit(1);
}
