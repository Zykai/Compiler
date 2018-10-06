#include "LexerTree.h"

class IdentifierTree : public LexerTree {
	LexerTree processChar(char & nextChar) override;
};