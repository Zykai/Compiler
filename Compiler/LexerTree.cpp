#include "stdafx.h"
#include "LexerTree.h"

Tokentype LexerTree::getType() {
	return this->currentToken;
}