#include <list>
#include "Token.h"

class LexerTree {
public:
	std::list<LexerTree*> nextTree;
	char required;
	virtual LexerTree processChar(char & nextChar);
private:
	Tokentype currentToken;
};