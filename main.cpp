#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "interpreter.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::ifstream ifs(argv[1]);
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		std::string file = buffer.str();
		Interpreter inter;
		inter.code_analyzer (file);
	}
	else
	{
		std::ifstream ifs("C:/Users/user/Documents/Visual Studio 2008/Projects/ARIT/Debug/code1.mil");
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		std::string file = buffer.str();
		Interpreter inter;
		inter.code_analyzer (file);
	}
	return 0;
}
