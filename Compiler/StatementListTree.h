#pragma once

#include <list>
#include "StatementTree.h"

class StatementListTree : public StatementTree {
public:
	StatementListTree(std::list<StatementTree*> * statements) {
		this->statements = statements;
	}
	std::list<StatementTree*> * statements;
	
	bool checkForErrors(ScopeHelper * s) override {
		s->enterScope();
		for (StatementTree * & st : *statements) {
			if (!st->checkForErrors(s)) {
				return false;
			}
		}
		s->leaveScope();
		return true;
	}

	void writeCode(CodeGenerator * c) override;
};