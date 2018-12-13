// Compiler.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include "stdafx.h"
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "SemanticAnalyser.h"
#include "IdentifierTree.h"
#include "ExpressionTree.h"
#include "ProgramTree.h"

int main(int numberArgs, const char ** arguments) {
	std::cout << "Starting Compiler" << std::endl;


	//Lexer lexer = Lexer("exprtest.z");
	Lexer lexer = Lexer("main.z");
	std::list<Token> testlist = lexer.getTokenList();


	Parser parser = Parser();
	parser.setTokenList(&testlist);
	parser.startParsing();

	if (true) {
		ProgramTree * p = parser.parseProgram();
		SemanticAnalyser s = SemanticAnalyser(p);
		s.checkForErrors();
		p->output();
		if (s.hasMain(p)) std::cout << "has main\n";
	}
	else {
		ExpressionTree * e = parser.parseExpression();
		e->output();
		//SemanticAnalyser s = SemanticAnalyser(nullptr);
		//std::cout << e->checkDatatype();
	}

	system("pause"); // FOR TESTING
	return 0; // FOR TESTING
}

