#include "Interpreter.h"

Interpreter::Interpreter () {
	mainString = ";" ;
}
void Interpreter::doInterpretion ( std::string & inString ) {
	inputString ( inString ) ;
	// call the function that should do the interpretion ...
}
bool Interpreter::inputString ( std::string & inString ) {
	char inChar = '\0';
	std::string temp = "0\0";
	while (inChar != ';' ) { // end of each sentence in this interpreter is ';' character 
		cin >> temp [0];
		inString.append(temp);
	}
}
