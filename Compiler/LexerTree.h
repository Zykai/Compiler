#include <list>
#include "Token.h"

class LexerTree {
public:
	std::list<LexerTree> nextTree;
	char required;
private:
	Tokentype currentToken;
};