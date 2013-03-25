#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "aritmathic.h"

class Interpreter {

	std::string baseString ;
	
	public :
		interpreter () ;
		void doInterpretion (std::string & ) ;
		bool hasIf ( std::string & ) ;

};

#endif
