#pragma once

#include <list>
#include "StatementTree.h"

class StatementListTree : public StatementTree {
public:
	StatementListTree(std::list<StatementTree*> * statements) {
		this->statements = statements;
	}
	std::list<StatementTree*> * statements;
};