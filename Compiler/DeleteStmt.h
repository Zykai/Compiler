#pragma once

#include "StatementTree.h"
#include "Expressions.h"

class DeleteStmt : public StatementTree {
public:
	DeleteStmt(Token * ref) {
		this->reference = ref;
	}
	Token * reference;

	bool checkForErrors(ScopeHelper * s) override {
		auto varInfo = s->getVarInformation(this->reference->getValue());
		if (varInfo == nullptr) {
			std::cout << "Reference to " << this->reference->getValue() << " does not exist" << std::endl;
			return false;
		}
		int dimensions = std::get<2>(*varInfo);
		return dimensions > 0;
	}

	void writeCode(CodeGenerator * c) override;
};