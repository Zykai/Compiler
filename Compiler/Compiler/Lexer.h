#pragma once

#include <list>
#include "Token.h"


class Lexer {
public:
	std::list<Token> getTokenList();

	Lexer(std::string source);
private:
};