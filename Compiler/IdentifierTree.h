#include "LexerTree.h"

class IdentifierTree : public LexerTree {
public:
	LexerTree* processChar(char & nextChar) override;
	IdentifierTree();
};