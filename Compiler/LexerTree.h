#pragma once
#include <list>
#include "Token.h"

// TODO:
//	-create root-tree class
//  -create string class
//	-create number class
//	-create constant class (while, +,  etc.)


class LexerTree {
public:
	LexerTree * nextTrees[128];
	virtual LexerTree* processChar(char & nextChar) = 0;
	Tokentype getType();
private:

protected:
	Tokentype currentToken;
};