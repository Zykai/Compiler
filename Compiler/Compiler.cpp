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
	bool writeToFile = false;
	long long int maxOperations = 0;
	std::string name;
	if (numberArgs > 1) {
		//name = arguments[1];
		for (int i = 0; i < numberArgs; i++) {
			if ((*arguments[i]) == '-') {
				switch (*(arguments[i]+1)) {
				case 'f':
					writeToFile = true;
					break;
				case 'n':
					i++;
					maxOperations = std::stoll(arguments[i]);
					break;
				case 's':
					i++;
					name = arguments[i];
					break;
				default:
					std::cout << "Unknown Compiler setting" << std::endl;
					break;
				}
			}
		}
	}
	else {
		name = "main.z";
	}
	std::cout << "Starting Compiler" << std::endl;


	//Lexer lexer = Lexer("exprtest.z");
	Lexer lexer = Lexer(name);
	std::list<Token> testlist = lexer.getTokenList();


	Parser parser = Parser();
	parser.setTokenList(&testlist);

	ProgramTree * p = parser.parseProgram();
	SemanticAnalyser s = SemanticAnalyser(p);
	s.checkForErrors();
	{
		CodeGenerator c = CodeGenerator(name, p, s.scopeHelper);
		c.writeProgram(p);
	}
	VirtualMachine vm = VirtualMachine(name, maxOperations, writeToFile);
	//vm.output();
	vm.executeProgram();
	
#ifdef _DEBUG
	system("pause");
#endif // DEBUG
	return 0;
}

