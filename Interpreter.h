#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "aritmathic.h"
#include "Variable.h"

class Interpreter {

	std::string baseString ;
	Variable    defVar ;
	public :
		interpreter () ;
		void doInterpretion (std::string & ) ;
		bool hasIf ( std::string & ) ;
		bool hasDefVar ( std::string & ) ;

};

#endif
