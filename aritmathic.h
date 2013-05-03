#ifndef _STRING_H_
#include <string>
#endif

#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#ifndef _ARITMATHIC_H_
#define _ARITMATHIC_H_ 0

struct operator_order
{
	int pos;
	int order;
};

class Aritmathic
{
	private:
		int number_of_char(std::string base, char token);
		int find_index_minus(std::string base, int current);
		int find_index(std::string base, int current, bool next = 1, int tokensize = 1);
		int* find_parantheses(std::string arit);
		std::string handle_minuses_and_pluses(std::string arit);
		std::string aritmathic_no_parantheses_int(std::string arit);

	public:
		Aritmathic::Aritmathic()
		{
		};
		InternalVariable parse_aritmathic(std::string arit);
};

unsigned int find_last_of_in_str(std::string str, char c);
unsigned int find_in_str(std::string str, char c);
unsigned int find_in_str(std::string str, char* c);

#endif