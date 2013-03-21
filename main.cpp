// ARIT.cpp : Testing the aritmathic operation codes
// As of now, it doesn't support parantheses, spaces, tabs and lot of operands.

#include "Interpreter.h"


int main()
{
	while (true) {
		Interpreter testInterpreter ;
		std::string inputString = "" ;
		std::cout << ">>" ;
		testInterpreter.doInterpretion(inputString); // the parser shuld be called in this function
		//Aritmathic b;
		//std::cout << b.parse_aritmathic("2+5*3/2*6-3%2");
		//system("PAUSE");

		if (inputString == "exit" or inputString == "exit()" ) break;
	}
	return 0 ;
}

