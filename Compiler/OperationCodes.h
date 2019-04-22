#pragma once

namespace OpCode {
	enum  OpCode : char {
		// Control-Flow operations (jmpifequal etc)
		JMP,
		JMP_TRUE,
		JMP_FALSE,
		CALL_FUNCTION,
		RETURN, // void functions
		RETURN_8, // byte, bool
		RETURN_16, // short
		RETURN_32, // integer, float functions
		RETURN_64, // pointer + doubles
		FUNCTION_END, // to stop functions with no return statement
		ERROR, // should never be called in a compiled program
		LOAD_GLOBAL_32,
		LOAD_CONSTANT_32,
		LOAD_CONSTANT_8,
		// Standard library
		I_PRINT,
		F_PRINT,
		BY_PRINT,
		BO_PRINT,
		STR_PRINT,
		// Reference operations
		REF_LOAD,
		REF_STORE,
		DEL_ARRAY,
		LEN_ARRAY,
		// Integer memory operations
		I_LOAD,
		I_STORE,
		I_POP,
		I_CREATE_ARRAY,
		I_LOAD_ARRAY_ELEMENT,
		I_STORE_ARRAY_ELEMENT,
		// Integer arithmetic operations
		I_ADD,
		I_SUB,
		I_MUL,
		I_DIV,
		I_MOD,
		I_INC,
		// Integer logical operations
		I_LESS_THAN,
		I_LESS_EQUAL,
		I_BIGGER_THAN,
		I_Bigger_EQUAL,
		I_EQUAL,
		I_NOT_EQUAL,
		// Integer type conversion
		I_FROM_F,

		// Float memory operations
		F_LOAD, // I_LOAD because of same size
		F_STORE,
		F_POP,
		F_CREATE_ARRAY,
		F_LOAD_ARRAY_ELEMENT,
		F_STORE_ARRAY_ELEMENT,
		// Float arithmetic operations
		F_ADD,
		F_SUB,
		F_MUL,
		F_DIV,
		F_MOD,
		F_INC,
		// Integer logical operations
		F_LESS_THAN,
		F_LESS_EQUAL,
		F_BIGGER_THAN,
		F_Bigger_EQUAL,
		F_EQUAL,
		F_NOT_EQUAL,
		// Float type conversion
		F_FROM_I,

		// Byte-Operations..
		BY_LOAD,
		BY_STORE,
		BY_POP,
		BY_CREATE_ARRAY,
		BY_LOAD_ARRAY_ELEMENT,
		BY_STORE_ARRAY_ELEMENT,
		// Byte arithmetic operations
		BY_ADD,
		BY_SUB,
		BY_MUL,
		BY_DIV,
		BY_MOD,
		BY_INC,
		// Byte logical operations
		BY_LESS_THAN,
		BY_LESS_EQUAL,
		BY_BIGGER_THAN,
		BY_Bigger_EQUAL,
		BY_EQUAL,
		BY_NOT_EQUAL,

		// Bool memory operations
		BO_LOAD,
		BO_STORE,
		BO_POP,
		BO_CREATE_ARRAY,
		BO_LOAD_ARRAY_ELEMENT,
		BO_STORE_ARRAY_ELEMENT,
		// Bool logical operations
		BO_EQUAL,
		BO_NOT_EQUAL,
		BO_AND,
		BO_OR,
		BO_XOR,
		BO_NEGATE,
		// Bool  type conversion
		BO_FROM_I,
		BO_FROM_F,
	};
}
