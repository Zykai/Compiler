#include "stdafx.h"
#include "Lexer.h"
#include <iostream>
#include <cctype>

std::list<Token> Lexer::getTokenList() {
	std::list<Token> allTokenList = std::list<Token>();

	for (std::string &s : this->source->textList) {
		getLineToken(s, allTokenList);
	}
	allTokenList.emplace_back(endOfFile, "");
	return allTokenList;
}

Lexer::Lexer(std::string source) {
	this->createStartFunction();
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
				Token token = Token(type, "");
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

std::string Lexer::insertSpecialCharacters(std::string s){
	/*
	int count = 0;
	for (int i = 0; i < s.size(); i++) {
		if(s.at(i) == '\\') {
			count++;
			i++; // to allow for double backslash
		}
	}
	char * newString = new char[s.size() - count];
	std::string test = std::string();
	test.reserve(s.size() - count);
	int c = test.size();
	int sPos = 0;
	for (int i = 0; i < s.size() - count; i++, sPos++) {
		char current = s.at(sPos);
		if (s.at(sPos) == '\\') {
			sPos++;
			switch (s.at(sPos)) {
			case '\\':
				newString[i] = '\\';
				break;
			case 'n':
				newString[i] = 0x0a;
				break;
			case 't':
				newString[i] = '\t';
				break;
			default:
				std::cout << "Unknown special character, using normal char instead" << std::endl;
			}
		}
		else {
			newString[i] = s.at(sPos);
			char n = newString[i];
			std::cout << "placeholder\n";
		}
	}
	return std::string(newString);
	*/
	std::string test = "";
	for (int i = 0; i < s.size(); i++) {
		if (s.at(i) == '\\') {
			i++;
			switch (s.at(i)) {
			case '\\':
				test += '\\';
				break;
			case 'n':
				test += '\n';
				break;
			case 't':
				test += '\t';
				break;
			default:
				std::cout << "Unknown special character, using normal char instead" << std::endl;
			}
		}
		else {
			test += s.at(i);
		}
	}
	return test;
}
