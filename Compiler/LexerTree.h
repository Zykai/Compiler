#include <list>
#include "Token.h"

class LexerTree {
public:
	LexerTree * nextTrees[128];
	char required;
	virtual LexerTree* processChar(char & nextChar);
private:

protected:
	Tokentype currentToken;
};