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
#include "CodeGenerator.h"
#include "VirtualMachine.h"

#include "VmStack.h"
int main(int numberArgs, const char ** arguments) {
	std::string name = "main.z";
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
		{
			
			CodeGenerator c = CodeGenerator("main.zc", p, s.scopeHelper);
			c.writeProgram(p);
		}
		VirtualMachine vm = VirtualMachine("main.zcc");
		vm.output();
		vm.executeProgram();
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

