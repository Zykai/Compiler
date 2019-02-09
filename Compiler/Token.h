#pragma once
#include <string>

// enumerator for each differen type of token
enum Tokentype {
	parentheseOpen,
	parentheseClose,
	curlyBracesOpen,
	curlyBracesClose,
	TokenSquareBracketOpen,
	TokenSquareBracketClose,
	logicalEqual,
	logicalAndOr,
	logicalComparison,
	TokenNegate,
	TokenPlus,
	TokenMultiply,
	assignOperator,
	identifier,
	semicolon,
	TokenDot,
	singleLineComment,
	mulitLineComment,
	integerNumber,
	floatNumber,
	TokenBool,
	TokenString,
	errorToken,
	typeName,
	importStmt,
	whileStmt,
	TokenFor,
	ifToken,
	TokenElse,
	TokenReturn,
	increment,
	TokenComma,
	endOfFile
};

// Token struct
// represents a token created by the lexer
struct Token {
public:
	Token(Tokentype t, std::string v);
	std::string getValue();
	std::string getTypeString();
	std::string getDescription();
	Tokentype getType();
private:
	Tokentype type;
	std::string value;
};