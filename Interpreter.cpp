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
bool Interpreter::hasIf ( std::string & inString ) {}
bool Interpreter::hasDefVar ( std::string & inString ) {
	int counter = 0 ;
	while ( counter < defVar.getTypeNum () ) {
		int tempFound = inString.find (defVar.type(counter)) ;
		if (tempFound != std::string::npos){
			std::string procString = "\0";
			int i = tempFound ;
			while ( inString[i] != ';' ) {
				std::string tempString = "a\0";
				tempString[0] = inString[i] ;
				procString.append ( tempString ) ;
				i++ ;
			}
			//return (bool) doVrDefine ( procString ) ; (must be defined ! ) (if can define return true ! esle false !
		}
		counter++ ;
	}
	return false ;
}
