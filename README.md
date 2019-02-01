# Compiler

## TODO

- allow declaration and expression in first part of for-loop
- add array access in expression
- seperate value tree into literal and variable tree
- get variable type in getelementree and value tree
- better error handling (jump to next statement)
- (remove pointer in scope->variables->pair)
- leave scope when encountering erros
- save datatype of expression in Expression::type
- add references to functions
- check for variable redefinitions
- implement byte type in lexer + code generator (valueTree + globaltree)
- add list for function calls with unknown positions
- add current function in code generator
- delete top of stack if not needed (for example in function calls)
- distinguish between global and local var in code gen
- check type in return statement + code generation
- when giving a type size, always give sizeof()
- check parse function
- add documentation for callFunction
- add checkForError and writecode in namespacefunction
- use memcpy directly without getBytes
- float variables dont work (should be removed, needs testing)
- checkforerrors: inclusive typechecking