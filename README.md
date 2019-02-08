# Compiler

## TODO (new features):
- add arrays
- add typedef + dynamic memory allocation
- seperate value tree into literal and variable tree
- get variable type in getelementree and value tree
- better error handling (jump to next statement)
- leave scope when encountering erros
- add references to functions (?)
- implement byte + bool type in lexer + code generator (valueTree + globaltree)
- distinguish between global and local var in code gen + global vars in vm
- float variables dont work (should be removed, needs testing)
- increment support
- type conversion
## TODO (bug fixes):
- delete top of stack if not needed (for example in function calls)
- check parse function
- check if void function works
## TODO (code cleanup):
- when giving a type size, always give sizeof()
- add documentation for callFunction
- use memcpy directly without getBytes
- checkforerrors: inclusive typechecking
- (remove pointer in scope->variables->pair)
- check for variable redefinitions
- remove unused classes in lexer