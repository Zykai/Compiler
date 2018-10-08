#pragma once

#include <list>
#include "Token.h"
#include "SourceFile.h"
#include "LexerTree.h"
#include "RootTree.h"

class Lexer {
public:
	std::list<Token> getTokenList();

	SourceFile * source;

	Lexer(std::string source);
	~Lexer();
private:
	LexerTree * root;
	void buildLexerTree();
	void analyzeLine(std::string & line);
	bool noError;
};