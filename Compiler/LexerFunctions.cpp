#include "stdafx.h"
#include "Lexer.h"
#include <iostream>
#include <cctype>

// TODO: find a way to remove i++ in loop
std::list<Token> Lexer::getLineToken(std::string line, std::list<Token> & currentLilst) {
	
	for (int i = 0; i < line.length(); ) {
		char currentChar = line.at(i);
		i++;
		if (std::isspace(currentChar)) {
			continue;
		}
		Token t = this->startFunction[currentChar](line, i-1, i);
		currentLilst.emplace_back(t);
	}
	return currentLilst;
}

// In case of bad performance: use lambdas instead of member functions
void Lexer::createStartFunction() {
	for (int i = 0; i < '0'; i++) {

	}
	for (int i = '0'; i <= '9'; i++) {
		startFunction[i] = std::bind(&Lexer::findInteger, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	for (int i = 58; i < 65 ; i++) {

	}
	for (int i = 65; i <= 90; i++) {
		startFunction[i] = std::bind(&Lexer::findId, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	for (int i = 91; i < 97; i++) {

	}
	for (int i = 97; i <= 122; i++) {
		startFunction[i] = std::bind(&Lexer::findId, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	startFunction['.'] = std::bind(&Lexer::findInteger, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['i'] = std::bind(&Lexer::findIntImport, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['f'] = std::bind(&Lexer::findFloatFor, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['w'] = std::bind(&Lexer::findWhile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['='] = std::bind(&Lexer::findAssignEqual, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction[';'] = [](std::string, int, int& currentChar) { return Token(semicolon, ";");};
	startFunction['('] = [](std::string, int, int& currentChar) { return Token(parentheseOpen, "("); };
	startFunction[')'] = [](std::string, int, int& currentChar) { return Token(parentheseClose, ")"); };
	startFunction['{'] = [](std::string, int, int& currentChar) { return Token(curlyBracesOpen, "{"); };
	startFunction['}'] = [](std::string, int, int& currentChar) { return Token(curlyBracesClose, "}"); };
	//startFunction['+'] = [](std::string, int, int& currentChar) { return Token(TokenPlus, "+"); };
	startFunction['+'] = [](std::string line, int, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == '+') {
			currentChar++;
			return Token(increment, "++");
		}
		return Token(TokenPlus, "+");
	};
	startFunction['-'] = [](std::string, int, int& currentChar) { return Token(TokenMinus, "-"); };
	startFunction['*'] = [](std::string, int, int& currentChar) { return Token(TokenMultiply, "*"); };
	startFunction['/'] = [](std::string, int, int& currentChar) { return Token(TokenDivide, "=/"); };
	startFunction['<'] = [](std::string line, int, int& currentChar) { 
		char nextChar = line.at(currentChar);
		if (nextChar == '=') {
			currentChar++;
			return Token(logicalComparison, "<=");
		}
		return Token(logicalComparison, "<");
	};
	startFunction['>'] = [](std::string line, int, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == '=') {
			currentChar++;
			return Token(logicalComparison, ">=");
		}
		return Token(logicalComparison, ">");
	};
	startFunction['!'] = [](std::string line, int, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == '=') {
			currentChar++;
			return Token(logicalEqual, "!=");
		}
		return Token(TokenNegate, "!");
	};
	startFunction['&'] = [](std::string line, int, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == '&') {
			currentChar++;
			return Token(logicalAndOr, "&&");
		}
		return Token(errorToken, "&");
	};
	startFunction['|'] = [](std::string line, int, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == '|') {
			currentChar++;
			return Token(logicalAndOr, "||");
		}
		return Token(errorToken, "|");
	};

}

Token Lexer::findId(std::string line, int startChar, int & currentChar) {
	for (; currentChar < line.length(); currentChar++) {
		char nextChar = line.at(currentChar);
		if (nextChar >= 'a' && nextChar <= 'z') {

		}
		else if (nextChar >= 'A' && nextChar <= 'Z') {

		}
		else if (nextChar >= '0' && nextChar <= '9') {

		}
		else {
			break;
		}
	}
	return Token(identifier, line.substr(startChar, currentChar - startChar));
}

Token Lexer::findInteger(std::string line, int startChar, int & currentChar) {
	for (; currentChar < line.length(); currentChar++) {
		char nextChar = line.at(currentChar);
		if (nextChar >= '0' && nextChar <= '9') {

		}
		else if (nextChar == '.') {
			currentChar++;
			return findFloat(line, startChar, currentChar);
		}
		else {
			break;
		}
	}
	return Token(integerNumber, line.substr(startChar, currentChar - startChar));
}

Token Lexer::findFloat(std::string line, int startChar, int & currentChar) {
	for (; currentChar < line.length(); currentChar++) {
		char nextChar = line.at(currentChar);
		if (nextChar >= '0' && nextChar <= '9') {

		}
		else {
			break;
		}
	}
	return Token(floatNumber, line.substr(startChar, currentChar - startChar));
}

// starts with letter 'i' -> import, int and ids starting with i
// throws error if line ends with "im" , "imp" etc. -> however: line mustn't end with identifier, import etc. so only handle error
Token Lexer::findIntImport(std::string line, int startChar, int & currentChar) {
	char nextChar = line.at(currentChar);
	if (nextChar == 'n') {
		currentChar++;
		if (line.at(currentChar) == 't') {
			currentChar++;
			if (!std::isalpha(line.at(currentChar))) {
				return Token(typeName, line.substr(startChar, currentChar - startChar));
			}
		}
	}
	else if (nextChar == 'f') {
		currentChar++;
		if (!std::isalpha(line.at(currentChar))) {
			return Token(ifToken, line.substr(startChar, currentChar - startChar));
		}
	}
	else if(nextChar == 'm'){
		currentChar++;
		if (line.at(currentChar) == 'p') {
			currentChar++;
			if (line.at(currentChar) == 'o') {
				currentChar++;
				if (line.at(currentChar) == 'r') {
					currentChar++;
					if (line.at(currentChar) == 't') {
						currentChar++;
						if (!std::isalpha(line.at(currentChar))) {
							return Token(importStmt, line.substr(startChar, currentChar - startChar));
						}
					}
				}
			}
		}
	}
	return this->findId(line, startChar, currentChar);
}

Token Lexer::findWhile(std::string line, int startChar, int & currentChar) {
	char nextChar = line.at(currentChar);
	if (nextChar == 'h') {
		currentChar++;
		if (line.at(currentChar) == 'i') {
			currentChar++;
			if (line.at(currentChar) == 'l') {
				currentChar++;
				if (line.at(currentChar) == 'e') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(whileStmt, line.substr(startChar, currentChar - startChar));
					}
				}
			}
		}
	}
	return this->findId(line, startChar, currentChar);
}

Token Lexer::findFloatFor(std::string line, int startChar, int & currentChar) {
	char nextChar = line.at(currentChar);
	if (nextChar == 'l') {
		currentChar++;
		if (line.at(currentChar) == 'o') {
			currentChar++;
			if (line.at(currentChar) == 'a') {
				currentChar++;
				if (line.at(currentChar) == 't') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(typeName, line.substr(startChar, currentChar - startChar));
					}
				}
			}
		}
	}
	else if (nextChar == 'o') {
		currentChar++;
		if (line.at(currentChar) == 'r') {
			currentChar++;
			if (!std::isalpha(line.at(currentChar))) {
				return Token(TokenFor, line.substr(startChar, currentChar - startChar));
			}
		}
	}
	return this->findId(line, startChar, currentChar);
}

Token Lexer::findAssignEqual(std::string line, int startChar, int & currentChar) {
	char nextChar = line.at(currentChar);
	if (nextChar == '=') {
		currentChar++;
		return Token(logicalEqual, line.substr(startChar, currentChar - startChar));
	}
	return Token(assignOperator, "=");
}