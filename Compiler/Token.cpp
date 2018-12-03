#include "stdafx.h"

#include "Token.h"

Token::Token(Tokentype t, std::string v) {
	this->type = t;
	this->value = v;
}

std::string Token::getValue() {
	return this->value;
}

// TODO: more types
std::string Token::getTypeString() {
	switch (this->type) {
	case identifier:
		return "Identifier";
	case integerNumber:
		return "Integer";
	case floatNumber:
		return "Float";
	case typeName:
		return "Typename";
	case importStmt:
		return "Import";
	case whileStmt:
		return "While";
	case TokenFor:
		return "For";
	case ifToken:
		return "If";
	case TokenElse:
		return "Else";
	case TokenReturn:
		return "Return";
	case semicolon:
		return "Semicolon";
	case curlyBracesOpen:
		return "CurlyBraceOpen";
	case curlyBracesClose:
		return "CurlyBraceClose";
	case parentheseOpen:
		return "ParentheseOpen";
	case parentheseClose:
		return "ParentheseClose";
	case assignOperator:
		return "AssignmentOperator";
	case TokenPlus:
		return "Plus";
	case TokenMinus:
		return "Minus";
	case TokenMultiply:
		return "Multiply";
	case TokenDivide:
		return "Divide";
	case logicalEqual:
		return "LogicalOperator";
	case logicalAndOr:
		return "LogicalAndOr";
	case logicalComparison:
		return "LogicalComparison";
	case TokenNegate:
		return "Negate";
	case increment:
		return "Increment";
	case TokenComma:
		return "TokenComma";
	case endOfFile:
		return "EndOfFile";
	default:
		return "Unknown Type";
	}
}

std::string Token::getDescription() {
	return "<" + this->getTypeString() + ", " + this->getValue() + ">";
}

Tokentype Token::getType() {
	return this->type;
}