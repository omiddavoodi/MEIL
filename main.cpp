#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "interpreter.h"

int main(int argc, char* argv[])
{
	//if we have an argument, it is the adderess of the file we need to interpret
	if (argc > 1)
	{
		//load the contents of the file
		std::ifstream ifs(argv[1]);
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		std::string file = buffer.str();
		
		//create an instance of the interpreter class
		Interpreter inter;
		
		//make it run the code
		inter.code_analyzer (file);
	}
	
	//end of the program
	return 0;
}
