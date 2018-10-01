#pragma once
#include <string>

// enumerator for each differen type of token
enum Tokentype {
	includeStatement,
	parentheseOpen,
	parentheseClose,
	curlyBracesOpen,
	curlyBracesClose,
	arithmeticOperator,
	logicalOperator,
	identifier,
	semicolon,
	singleLineComment,
	mulitLineComment,
};

// Token struct
// represents a token created by the lexer
struct Token {
public:

private:
	Tokentype type;
	std::string value;
};