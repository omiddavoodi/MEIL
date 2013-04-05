#ifndef _STRING_H_
#include <string>
#endif

#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#ifndef _VARTABLE_H_
#include "vartable.h"
#endif

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_ 0

struct Token
{
	std::string str;
	unsigned int pos;
};

class Interpreter
{
	private:
		VarTable variable_table;
		std::string code;
		InternalVariable do_arit(std::string statement);

		void var_statement(std::string statement);
		void print_statement(std::string statement);
	public:
		Interpreter::Interpreter(){};
		void statement_analyzer(std::string statement);
};

#endif