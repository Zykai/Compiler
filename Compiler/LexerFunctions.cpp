#include "stdafx.h"
#include "Lexer.h"
#include <iostream>
#include <cctype>

// TODO: find a way to remove i++ in loop
std::list<Token> Lexer::getLineToken(std::string line, std::list<Token> & tokenList) {
	
	for (int i = 0; i < line.length(); ) {
		char currentChar = line.at(i);
		i++;
		if (std::isspace(currentChar)) {
			continue;
		}
		Token t = this->startFunction[currentChar](line, i - 1, i);
		tokenList.emplace_back(t);
	}
	return tokenList;
}

// In case of bad performance: use lambdas instead of member functions
void Lexer::createStartFunction() {
	for (int i = 0; i < '0'; i++) {

	}
	for (int i = '0'; i <= '9'; i++) {
		startFunction[i] = std::bind(&Lexer::findInteger, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	for (int i = 58; i < 65; i++) {

	}
	for (int i = 65; i <= 90; i++) {
		startFunction[i] = std::bind(&Lexer::findId, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	for (int i = 91; i < 97; i++) {

	}
	for (int i = 97; i <= 122; i++) {
		startFunction[i] = std::bind(&Lexer::findId, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	Lexer * self = this; // needed for lambdas that access member functions
	startFunction['.'] = std::bind(&Lexer::findInteger, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['i'] = std::bind(&Lexer::findIntImport, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['f'] = std::bind(&Lexer::findFloatFor, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['w'] = std::bind(&Lexer::findWhile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction['r'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'e') {
			currentChar++;
			if (line.at(currentChar) == 't') {
				currentChar++;
				if (line.at(currentChar) == 'u') {
					currentChar++;
					if (line.at(currentChar) == 'r') {
						currentChar++;
						if (line.at(currentChar) == 'n') {
							currentChar++;
							if (!std::isalpha(line.at(currentChar))) {
								return Token(TokenReturn, line.substr(startChar, currentChar - startChar));
							}
						}
					}
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['e'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'l') {
			currentChar++;
			if (line.at(currentChar) == 's') {
				currentChar++;
				if (line.at(currentChar) == 'e') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(TokenElse, line.substr(startChar, currentChar - startChar));
					}
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['v'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'o') {
			currentChar++;
			if (line.at(currentChar) == 'i') {
				currentChar++;
				if (line.at(currentChar) == 'd') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(typeName, "void");
					}
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['b'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'o') {
			currentChar++;
			if (line.at(currentChar) == 'o') {
				currentChar++;
				if (line.at(currentChar) == 'l') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(typeName, "bool");
					}
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['t'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'r') {
			currentChar++;
			if (line.at(currentChar) == 'u') {
				currentChar++;
				if (line.at(currentChar) == 'e') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(TokenBool, "1");
					}
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['n'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'e') {
			currentChar++;
			if (line.at(currentChar) == 'w') {
				currentChar++;
				if (!std::isalpha(line.at(currentChar))) {
					return Token(TokenNew, "new");
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['d'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == 'e') {
			currentChar++;
			if (line.at(currentChar) == 'l') {
				currentChar++;
				if (nextChar == 'e') {
					currentChar++;
					if (line.at(currentChar) == 't') {
						currentChar++;
						if (line.at(currentChar) == 'e') {
							currentChar++;
							if (!std::isalpha(line.at(currentChar))) {
								return Token(TokenDelete, "delete");
							}
						}
					}
				}
			}
		}
		return self->findId(line, startChar, currentChar);
	};
	startFunction['='] = std::bind(&Lexer::findAssignEqual, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	startFunction[';'] = [](std::string, int, int& currentChar) { return Token(semicolon, ";"); };
	startFunction[','] = [](std::string, int, int& currentChar) { return Token(TokenComma, ","); };
	startFunction['.'] = [](std::string, int, int& currentChar) { return Token(TokenDot, "."); };
	startFunction['('] = [](std::string, int, int& currentChar) { return Token(parentheseOpen, "("); };
	startFunction[')'] = [](std::string, int, int& currentChar) { return Token(parentheseClose, ")"); };
	startFunction['{'] = [](std::string, int, int& currentChar) { return Token(curlyBracesOpen, "{"); };
	startFunction['}'] = [](std::string, int, int& currentChar) { return Token(curlyBracesClose, "}"); };
	startFunction['['] = [](std::string, int, int& currentChar) { return Token(TokenSquareBracketOpen, "["); };
	startFunction[']'] = [](std::string, int, int& currentChar) { return Token(TokenSquareBracketClose, "]"); };
	startFunction['+'] = [](std::string line, int, int& currentChar) {
		char nextChar = line.at(currentChar);
		if (nextChar == '+') {
			currentChar++;
			return Token(increment, "++");
		}
		return Token(TokenPlus, "+");
	};
	startFunction['-'] = [](std::string, int, int& currentChar) { return Token(TokenPlus, "-"); };
	startFunction['*'] = [](std::string, int, int& currentChar) { return Token(TokenMultiply, "*"); };
	startFunction['/'] = [](std::string, int, int& currentChar) { return Token(TokenMultiply, "/"); };
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
	startFunction['"'] = [&](std::string line, int startChar, int& currentChar) {
		char nextChar = line.at(currentChar);
		while (nextChar != '"') {
			currentChar++;
			nextChar = line.at(currentChar);
		}
		currentChar++;
		std::string withSpecial = line.substr(startChar + 1, currentChar - startChar - 2);
		std::string withoutSpecial = this->insertSpecialCharacters(withSpecial);
		return Token(TokenString, withoutSpecial);
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
	else if (nextChar == 'a') {
		currentChar++;
		if (line.at(currentChar) == 'l') {
			currentChar++;
			if (line.at(currentChar) == 's') {
				currentChar++;
				if (line.at(currentChar) == 'e') {
					currentChar++;
					if (!std::isalpha(line.at(currentChar))) {
						return Token(TokenBool, "0");
					}
				}
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