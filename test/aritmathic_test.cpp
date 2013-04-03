#include <iostream>
#include "aritmathic.h"

int main()
{
	Aritmathic b;
	std::cout << b.parse_aritmathic("2.4+5*3/2*(6-3)%2").get_float_value();
	system("PAUSE");
}