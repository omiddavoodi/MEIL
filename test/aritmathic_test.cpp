#include <iostream>
#include "aritmathic.h"

int main()
{
	Aritmathic b;
	std::cout << b.parse_aritmathic("2+5*3/2*(6-3)%2");
	system("PAUSE");
}