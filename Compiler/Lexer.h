#pragma once

#include <list>
#include <functional>
#include "Token.h"
#include "SourceFile.h"
#include "LexerTree.h"
#include "RootTree.h"

class Lexer {
public:
	std::list<Token> getLineToken(std::string line);
	std::list<std::list<Token>> getTokenList();

	SourceFile * source;

	Lexer(std::string source);
	~Lexer();
private:
	LexerTree * root;
	void buildLexerTree();
	void createStartFunction();
	void analyzeLine(std::string & line);
	bool noError;
public:
	std::function<Token(std::string, int, int & currentChar)> startFunction[128];
	Token findId(std::string line, int startChar, int & currentChar), findInteger(std::string line, int startChar, int & currentChar), findFloat(std::string line, int startChar, int & currentChar), findIntImport(std::string line, int startChar, int & currentChar),
		findWhile(std::string line, int startChar, int & currentChar), findFloatFor(std::string line, int startChar, int & currentChar), findAssignEqual(std::string line, int startChar, int & currentChar);
};