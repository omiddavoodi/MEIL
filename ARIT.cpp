// ARIT.cpp : Testing the aritmathic operation codes
// As of now, it doesn't support parantheses, spaces, tabs and lot of operands.

#include <iostream>
#include "aritmathic.h"

int main()
{
	Aritmathic b;
	std::cout << b.parse_aritmathic("2+5*3/2*6-3%2");
	system("PAUSE");
}

