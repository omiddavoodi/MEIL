#ifndef _STRING_H_
#include <string>
#endif

#ifndef _ARITMATHIC_H_
#define _ARITMATHIC_H_ 0

class Aritmathic
{
	private:
		int number_of_char(std::string base, char token);
		int find_index(std::string base, int current, bool next = 1);
		char order_of_operands(int a1, int a2);
		char order_of_operands(int a1, int a2, int a3);
		int aritmathic_no_parantheses_int(std::string arit);

	public:
		Aritmathic::Aritmathic()
		{
		};
		int parse_aritmathic(std::string arit);
};
#endif