#include "stdafx.h"
#include "RootTree.h"
//#include "LexerUtils.h"

LexerTree*  RootTree::processChar(char & nextChar) {
	return this->nextTrees[nextChar];
}

RootTree::RootTree() {
	this->idTree = new IdentifierTree();

	// Invalid chars
	for (int i = 0; i <= 47; i++) {
		this->nextTrees[i] = nullptr;
	}
	// Numbers
	for (int i = 48; i <= 57; i++) {
		this->nextTrees[i] = this->idTree; //TODO change to integer-tree
	}
	// Invalid chars
	for (int i = 58; i <= 67; i++) {
		this->nextTrees[i] = nullptr;
	}
	// Capital letters
	for (int i = 65; i <= 90; i++) {
		this->nextTrees[i] = this->idTree;
	}
	// Lowercase letters
	for (int i = 97; i <= 122; i++) {
		this->nextTrees[i] = this->idTree;
	}
	// Invalid chars
	for (int i = 123; i <= 127; i++) {
		this->nextTrees[i] = nullptr;
	}
}

RootTree::~RootTree() {
	delete idTree;
}