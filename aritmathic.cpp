#ifndef _STRING_H_
#include <string>
#endif

#ifndef _ARITMATHIC_H_
#include "aritmathic.h"
#endif

int Aritmathic::number_of_char(std::string base, char token)
{
	unsigned int number = 0, length = base.length();
	for (unsigned int i = 0; i < length; ++i)
	{
		if (base[i] == token)
			++number;
	}
	return number;
}

int Aritmathic::find_index(std::string base, int current, bool next)
{
	if (next)
	{
		int size = base.size();
		int temp_index = current + 1;
		if (temp_index >= size)
			return size;
		char temp_char = base[temp_index];
		while (temp_char != '*' && temp_char != '/' && temp_char != '+' && temp_char != '-' && temp_char != '%')
		{
			++temp_index;
			if (temp_index >= size)
				return size;
			temp_char = base[temp_index];
		}
		return temp_index;
	}
	else
	{
		int temp_index = current - 1;
		if (temp_index <= 0)
			return 0;
		char temp_char = base[temp_index];
		while (temp_char != '*' && temp_char != '/' && temp_char != '+' && temp_char != '-' && temp_char != '%')
		{
			--temp_index;
			if (temp_index <= 0)
				return 0;
			temp_char = base[temp_index];
		}
		return temp_index;
	}
}

char Aritmathic::order_of_operands(int a1, int a2)
{
	if (a1 < 0) return 2;
	else if (a2 < 0 || a2 > a1) return 1;
	else if (a2 < a1) return 2;
	else return 1;
}

char Aritmathic::order_of_operands(int a1, int a2, int a3)
{
	if (a1 < 0)
	{
		if (a2 < 0) return 3;
		else if (a3 < 0 || a3 > a2) return 2;
		else if (a3 < a2) return 3;
	}
	else
	{
		if (a2 < 0 && a3 < 0) return 1;
		else if (a2 < 0)
		{
			if (a1 < a3) return 1;
			else return 3;
		}
		else if (a3 < 0)
		{
			if (a1 < a2) return 1;
			else return 2;
		}
		else
		{
			if (a1 < a2 && a1 < a3) return 1;
			else if (a2 < a3 && a2 < a1) return 2;
			else if (a3 < a2 && a3 < a1) return 3;
		}
	}
	return 1;
}

int Aritmathic::aritmathic_no_parantheses_int(std::string arit)
{
	std::string temp(arit.data());
	while (number_of_char(temp, '*') > 0 || number_of_char(temp, '/') > 0 || number_of_char(temp, '%') > 0)
	{
		int currentstar = temp.find('*'), currentslash = temp.find('/'), currentpercent = temp.find('%'), current;
		int order = order_of_operands(currentstar, currentslash, currentpercent);
		if (order == 1) current = currentstar;
		else if (order == 2) current = currentslash;
		else current = currentpercent;

		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		int next = atoi(temp.substr(current + 1, next_index - current - 1).data());
		int previous = atoi(temp.substr(pre_index, current).data());
		std::string temp_result;
		if (order == 1)
		{
			char* s = new char[64];
			temp_result = _itoa(next * previous, s, 10);
			delete s;
		}
		else if (order == 2)
		{
			char* s = new char[64];
			temp_result = _itoa(previous / next, s, 10);
			delete s;
		}
		else
		{
			char* s = new char[64];
			temp_result = _itoa(previous % next, s, 10);
			delete s;
		}

		std::string temp2("");
		temp2.append(temp.substr(0,pre_index+1)).append(temp_result).append(temp.substr(next_index,temp.size()));
		temp = std::string(temp2.data());
	}

	while (number_of_char(temp, '+') > 0 || number_of_char(temp, '-') > 0)
	{
		int currentcross = temp.find('+'), currentdash = temp.find('-'), current;
		int order = order_of_operands(currentcross, currentdash);
		if (order == 1) current = currentcross;
		else current = currentdash;

		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		int next = atoi(temp.substr(current + 1, next_index - current - 1).data());
		int previous = atoi(temp.substr(pre_index, current).data());
		std::string temp_result;
		if (order == 1)
		{
			char* s = new char[64];
			temp_result = _itoa(next + previous, s, 10);
			delete s;
		}
		else if (order == 2)
		{
			char* s = new char[64];
			temp_result = _itoa(previous - next, s, 10);
			delete s;
		}

		std::string temp2("");
		if (!pre_index) --pre_index;
		temp2.append(temp.substr(0,pre_index + 1)).append(temp_result).append(temp.substr(next_index,temp.size()));
		temp = std::string(temp2.data());
	}

	return atoi(temp.data());
}

int Aritmathic::parse_aritmathic(std::string arit)
{
	//still WIP (work in progress).
	//TODO: add support for other operands: &&, ||, <, >, ^, ==, etc.
	//TODO: add support for parantheses and remove spaces/tabs/enters before starting the real operation
	//TODO: bbetter to create our own functions when dealing with string<->int conversations.
	//TODO: add support for float operations. "Variable" class is needed for this.
	int temp_par = 0;
	bool has_par = false;
	for (unsigned int i = 0; i < arit.size(); ++i)
	{
		if (arit[i] == '(')
		{
			temp_par++;
			has_par = true;
		}
		else if (arit[i] == ')')
			temp_par--;
	}
	if (temp_par != 0)
		return 0;
	else
		if (!has_par)
			return aritmathic_no_parantheses_int(arit);
	return 0;
}