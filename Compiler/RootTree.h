#pragma once
#include "LexerTree.h"
#include "IdentifierTree.h"

class RootTree : public LexerTree {
public:
	LexerTree* processChar(char & nextChar) override;
	RootTree();
	~RootTree();
private:
	IdentifierTree * idTree;
};