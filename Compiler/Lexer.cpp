#include "stdafx.h"
#include "Lexer.h"
#include <iostream>

std::list<Token> Lexer::getTokenList() {
	this->buildLexerTree();
	std::cout << source->text;
	const char * cstring = source->text.c_str();

	while (true) {
		Token currentToken = getToken();
	}
}

Lexer::Lexer(std::string source) {
	this->source = new SourceFile(source);
}


Lexer::~Lexer() {
	delete source;
	delete root;
}

Token Lexer::getToken() {
	return Token();
}

void Lexer::buildLexerTree() {
	root = new LexerTree();
}