#pragma once

#include <list>
#include "Token.h"
#include "SourceFile.h"
#include "LexerTree.h"

class Lexer {
public:
	std::list<Token> getTokenList();

	SourceFile * source;

	Lexer(std::string source);
	~Lexer();
private:
	LexerTree * root;
	Token getToken();
	void buildLexerTree();
};