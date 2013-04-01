#ifndef _STRING_H_
#include <string>
#endif

#ifndef _ARITMATHIC_H_
#include "aritmathic.h"
#endif

#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#include <iostream>

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

int Aritmathic::find_index_minus(std::string base, int current)
{
	int temp_index = current - 1;
	if (temp_index <= 0)
		return -1;
	char temp_char = base[temp_index];
	while (temp_char != '+' && temp_char != '-')
	{
		--temp_index;
		if (temp_index <= 0)
			return -1;
		temp_char = base[temp_index];
	}
	return temp_index;
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

std::string Aritmathic::aritmathic_no_parantheses_int(std::string arit)
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
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - 1).data());
		std::string temp_result;
		InternalVariable t_res;
		if (order == 1)
		{
			t_res = next * previous;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else if (order == 2)
		{
			t_res = previous / next;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else
		{
			t_res = previous % next;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}

		std::string temp2("");
		if (pre_index > 0)
			temp2.append(temp.substr(0,pre_index)).append(temp_result).append(temp.substr(next_index,temp.size()));
		else
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
		temp = std::string(temp2.data());
		//std::cout << temp << "\n";
	}

	while (number_of_char(temp, '+') > 0 || number_of_char(temp, '-') > 0)
	{
		int currentcross = temp.find_last_of('+'), currentdash = temp.find_last_of('-'), current;
		int order = order_of_operands(currentdash, currentcross);
		if ((currentcross >= 0) && (order == 1 || currentdash < 0)) 
		{
			current = currentcross;
			order = 1;
		}
		else
		{
			current = currentdash;
			order = 2;
		}
		
		int num_operands = number_of_char(temp, '/') + number_of_char(temp, '-') + number_of_char(temp, '+') + number_of_char(temp, '*') + number_of_char(temp, '%');
		if (((number_of_char(temp, '-') == 1) && (temp[0] == '-')) || ((number_of_char(temp, '+') == 1) && (temp[0] == '+')) && (num_operands == 1))
			return temp;

		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current).data());

		std::string temp_result;
		InternalVariable t_res;
		if (order == 1)
		{
			t_res = next + previous;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else if (order == 2)
		{
			t_res = previous - next;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}

		std::string temp2("");
		if (pre_index > 0)
			temp2.append(temp.substr(0,pre_index)).append(temp_result).append(temp.substr(next_index,temp.size()));
		else
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
		temp = std::string(temp2.data());
		//std::cout << temp << "\n";
	}

	return temp.data();
}

int lower(int a , int b)
{
	if (a < 0) return b;
	else if (b < 0) return a;
	else if (a < b) return a;
	else if (b < a) return b;
	else return a;
}

std::string Aritmathic::distribute_low_operands(std::string arit)
{
	std::string temp(arit.data());
	while (true)
	{
		int size = temp.size();
		int m1 = lower(temp.find("--"), temp.find("++")), m2 = lower(temp.find("*+"), lower(temp.find("/+"), temp.find("%+")))
			,  m3 = lower(temp.find("*-"), lower(temp.find("/-"), temp.find("%-")));
		if (m1 == 0)
		{
			temp = temp.substr (2, size);
			continue;
		}
		else if (m1 >= 0)
		{
			temp = temp.substr(0, m1).append(std::string("+")).append(temp.substr(m1+2, size));
			continue;
		}

		if (m2 >= 0)
		{
			temp = temp.substr(0, m2+1).append(temp.substr(m2+2, size));
			continue;
		}

		if (m3 >= 0)
		{
			int last = find_index_minus(temp, m3);
			if (last <= 0)
			{
				temp = std::string("-").append(temp.substr(0, m3+1)).append(temp.substr(m3+2, size));
			}
			else
			{
				temp = temp.substr(0, m3+1).append(temp.substr(m3+2, size));
				if (temp[last] == '-') temp[last] = '+';
				else temp[last] = '-';
			}
			continue;
		}
		break;
	}
	return temp;
}

int* Aritmathic::find_parantheses(std::string arit)
{
	int* res = new int[2];
	int size = arit.size();
	for (int n = 0; n < size; ++n)
	{
		if (arit[n] == '(')
		{
			res[0] = n;
		}
		else if (arit[n] == ')')
		{
			res[1] = n;
			break;
		}
	}
	return res;
}

int Aritmathic::parse_aritmathic(std::string arit)
{
	//still WIP (work in progress).
	//TODO: add support for other operands: &&, ||, <, >, ^, ==, etc.
	//TODO: remove spaces/tabs/enters before starting the real operation
	//TODO: better to create our own functions when dealing with string<->int conversations.
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
	{
		if (!has_par)
		{
			return atoi(aritmathic_no_parantheses_int(distribute_low_operands(arit)).data());
		}
		else
		{
			std::string temp(arit.data());
			while (number_of_char(temp, '('))
			{
				std::string temp2("");
				int* pos = find_parantheses(temp);
				int size = temp.size();
				std::string temp_result = aritmathic_no_parantheses_int(distribute_low_operands(temp.substr(pos[0]+1, pos[1]-pos[0]-1))), last_par = (pos[1]+1 > size? std::string("") : temp.substr(pos[1]+1,size));
				if (pos[0] > 0)
					temp2.append(temp.substr(0,pos[0])).append(temp_result).append(last_par);
				else
					temp2.append(temp_result).append(last_par);
				temp = std::string(temp2.data());
			}
			return atoi(aritmathic_no_parantheses_int(distribute_low_operands(temp)).data());
		}
	}
	return 0;
}