# Compiler

## TODO (new features):
- add typedef + dynamic memory allocation
- seperate value tree into literal and variable tree
- get variable type in getelementree and value tree
- better error handling (jump to next statement)
- leave scope when encountering erros
- add references to functions (in c++ not in z code)
- implement double, byte, short type in lexer + code generator (valueTree + globaltree)
- distinguish between global and local var in code gen + global vars in vm
- float variables dont work (should be removed, needs testing)
- increment support
- type conversion
- array out of bounds checking
## TODO (bug fixes):
- check parse function
- check if void function works
- printing arrays
## TODO (code cleanup):
- when giving a type size, always give sizeof()
- add documentation for callFunction
- use memcpy directly without getBytes
- checkforerrors: inclusive typechecking or < operator
- (remove pointer in scope->variables->pair)
- check for variable redefinitions
- remove unused classes in lexer
- remove redundant data in allVariables (maybe use pointer to declaration instead of tuples)
- restructure allVariables (maybe use already existing namespace)
- improve ScopeHelper::addVariable integration with dynamic types (arrays and typedefs)
- improve array typecheck performance by subtracting its type

## Known Errors:
- std::list<ExpressionTree*>() threw a fast fail exception, fixed by using dynamic allocation instead???, error turned up without changing any code near it, fixed by using release mode
```c++
std::cout << "1";
std::list<ExpressionTree*> * dimensionSizes = new std::list<ExpressionTree*>();
std::cout << "2";
```
- when Stack is composed of an 8 byte array pointer + 4 byte int --> popInt() causes an exception when accessing array values; to fix place integer after array
```c++
// Doesnt work
VmArray<int> * arrayPointer = (VmArray<int>*)this->stack->loadPointer(position);
arrayPointer->setAllValues(indices, this->stack->popInt());
// Works
this->stack->pushInt(21);
VmArray<int> * arrayPointer = (VmArray<int>*)this->stack->loadPointer(position);
arrayPointer->setAllValues(indices, this->stack->popInt());
// Fix, is called each function call + at main function startup
this->stack->pushInt(-1111111); // fixes reference error (if array is on top of stack)
```
- an array function named test will crash the following code (a==null):
```c++
void DeleteStmt::writeCode(CodeGenerator * c){
	auto a = c->scopeHelper->getVarInformation(this->reference->getValue());
	int position = std::get<1>(*(c->scopeHelper->getVarInformation(this->reference->getValue())));
	c->writeByte(OpCode::DEL_ARRAY);
	c->writeInteger(position);
}
```