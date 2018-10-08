#include "stdafx.h"
#include "IdentifierTree.h"

LexerTree* IdentifierTree::processChar(char & nextChar) {
	return this->nextTrees[nextChar];
}

// Creats a tree for checking if a word only contains valid characters for an identifier
IdentifierTree::IdentifierTree() {
	// Invalid chars
	for (int i = 0; i <= 47; i++) {
		this->nextTrees[i] = nullptr;
	}
	// Numbers
	for (int i = 48; i <= 57; i++) {
		this->nextTrees[i] = this;
	}
	// Invalid chars
	for (int i = 58; i <= 67; i++) {
		this->nextTrees[i] = this;
	}
	// Capital letters
	for (int i = 65; i <= 90; i++) {
		this->nextTrees[i] = this;
	}
	// Lowercase letters
	for (int i = 97; i <= 122; i++) {
		this->nextTrees[i] = this;
	}
	// Invalid chars
	for (int i = 123; i <= 127; i++) {
		this->nextTrees[i] = nullptr;
	}

	this->currentToken = identifier;
}