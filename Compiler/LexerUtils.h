#pragma once
#include "stdafx.h"
#include "LexerTree.h"

namespace LexerUtils {
	void copyIdTree(LexerTree **  trees, LexerTree* caller) {
		// Invalid chars
		for (int i = 0; i <= 47; i++) {
			trees[i] = nullptr;
		}
		// Numbers
		for (int i = 48; i <= 57; i++) {
			trees[i] = caller;
		}
		// Invalid chars
		for (int i = 58; i <= 67; i++) {
			trees[i] = caller;
		}
		// Capital letters
		for (int i = 65; i <= 90; i++) {
			trees[i] = caller;
		}
		// Lowercase letters
		for (int i = 97; i <= 122; i++) {
			trees[i] = caller;
		}
		// Invalid chars
		for (int i = 123; i <= 127; i++) {
			trees[i] = nullptr;
		}
	}
}

