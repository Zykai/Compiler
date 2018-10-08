#include "stdafx.h"
#include "Lexer.h"
#include <iostream>
#include <cctype>

// TODO:
// -Problem: main() is invalid, as ( is interpreted as part of identifier
// -Solution: change DFAs to functions, perhabs come up with an elegant solution for constant names (while etc)

std::list<Token> Lexer::getTokenList() {
	this->buildLexerTree();
	source->print();
	//const char * cstring = source->text.c_str();

	for (std::string &s : this->source->textList) {
		this->analyzeLine(s);
	}
	return std::list<Token>();
}

Lexer::Lexer(std::string source) {
	this->source = new SourceFile(source);
	this->noError = true;
}


Lexer::~Lexer() {
	delete source;
	delete root;
}

void Lexer::buildLexerTree() {
	// TODO
	root = new RootTree();
}

// TODO test algorith, needs root implementation first, fails currently
void Lexer::analyzeLine(std::string & line) {
	std::cout << "Starting line" << std::endl;
	LexerTree * currentState = root;
	for (int i = 0; i < line.length(); i++) {
		char currentChar = line.at(i);
		if (std::isspace(currentChar)) {
			// Token is finished
			if (currentState != root) {
				if (currentState == nullptr) {

				}
				Tokentype type = currentState->getType();
				std::cout << "Found Token, Type: " << type << std::endl;
				Token token = Token(type);
				currentState = root;
			}
			continue;
		}
		//else if()
		std::cout << currentChar << std::endl;
		currentState = currentState->processChar(currentChar);
		if (currentState == nullptr) {
			std::cout << "ERROR in line..."; // TODO
			break; // TODO: allow multiple errors per line, 
		}
	}
	std::cout << "Line finished" << std::endl;
}