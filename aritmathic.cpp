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

bool in_string(std::string base, unsigned int pos)
{
	bool inside = false;
	for (unsigned int i = 0; i < pos; ++i)
	{
		if (base[i] == '"')
			inside = !inside;
	}
	return inside;
}

int Aritmathic::number_of_char(std::string base, char token)
{
	unsigned int number = 0, length = base.length();
	for (unsigned int i = 0; i < length; ++i)
	{
		if (base[i] == token && !in_string(base, i))
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
	while (temp_char != '+' && temp_char != '-' && !in_string(base, temp_index))
	{
		--temp_index;
		if (temp_index <= 0)
			return -1;
		temp_char = base[temp_index];
	}
	return temp_index;
}

int Aritmathic::find_index(std::string base, int current, bool next, int tokensize)
{
	if (next)
	{
		int size = base.size();
		int temp_index = current + tokensize;
		if (temp_index >= size)
			return size;
		char temp_char = base[temp_index];
		while (temp_char != '*' && temp_char != '/' && temp_char != '+' && temp_char != '-' && temp_char != '%' && temp_char != '<' && temp_char != '=' && temp_char != '>' && temp_char != '!' && !in_string(base, temp_index))
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
		int temp_index = current - tokensize;
		if (temp_index <= 0)
			return 0;
		char temp_char = base[temp_index];
		while (temp_char != '*' && temp_char != '/' && temp_char != '+' && temp_char != '-' && temp_char != '%' && temp_char != '<' && temp_char != '=' && temp_char != '>' && temp_char != '!' && !in_string(base, temp_index))
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

int number_of_nots(std::string base)
{
	unsigned int number = 0, length = base.length();
	for (unsigned int i = 0; i < length; ++i)
	{
		if (base[i] == '!'  && !in_string(base, i))
			if ((i == (length - 1)) || base[i+1] != '=')
			++number;
	}
	return number;
}

unsigned int find_last_of_in_str(std::string str, char c)
{
	unsigned int size = str.size();
	for (int i = size - 1; i >= 0; --i)
	{
		if (str[i] == c && !in_string(str, i))
		{
			return i;
		}
	}
	return -1;
}

unsigned int find_in_str(std::string str, char c)
{
	unsigned int size = str.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		if (str[i] == c && !in_string(str, i))
		{
			return i;
		}
	}
	return -1;
}

unsigned int find_in_str(std::string str, char* c)
{
	std::string cs(c);
	unsigned int size = str.size();
	unsigned int csize = cs.size(); 
	if (size >= csize)
	{
		for (unsigned int i = 0; i < size - csize + 1; ++i)
		{
			for (unsigned int j = 0; j < csize; ++j)
			{
				if (str[i+j] != cs[j] || in_string(str, i))
				{
					break;
				}
				if (j == csize - 1)
					return i;
			}
		}
	}
	return -1;
}

std::string Aritmathic::aritmathic_no_parantheses_int(std::string arit)
{
	std::string temp(arit.data());

	while (number_of_nots(temp) > 0)
	{
		int current = find_in_str(temp, '!');
		if (temp[current+1] != '=')
		{
			int next_index = find_index(temp, current ,1);
			InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
			std::string temp_result;
			InternalVariable t_res;

			t_res = next.nots();

			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());


			std::string temp2("");
			if (current > 0)
				temp2.append(temp.substr(0,current-1)).append(temp_result).append(temp.substr(next_index,temp.size()));
			else
				temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
			temp = std::string(temp2.data());
		}
		//std::cout << temp << "\n";
	}

	int currentand = find_in_str(temp, "&&"), currentor = find_in_str(temp, "||"), currentnotequal = find_in_str(temp ,"!=");
	while (currentand >= 0 || currentor >= 0 || currentnotequal >= 0)
	{
		int current;
		int order = order_of_operands(currentand, currentor, currentnotequal);
		if (order == 1) current = currentand;
		else if (order == 2) current = currentor;
		else current = currentnotequal;

		int pre_index = find_index(temp, current ,0, 2), next_index = find_index(temp, current ,1, 2);
		InternalVariable next = str_to_var(temp.substr(current + 2, next_index - current - 2).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
		std::string temp_result;
		InternalVariable t_res;
		if (order == 1)
		{
			t_res = next && previous;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else if (order == 2)
		{
			t_res = previous || next;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else
		{
			t_res = (previous == next).nots();
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
		currentand = find_in_str(temp ,"&&");
		currentor = find_in_str(temp ,"||");
		currentnotequal = find_in_str(temp ,"!=");
	}

	int currentequal = find_in_str(temp, "=="), currentmore = find_in_str(temp, ">="), currentless = find_in_str(temp ,"<=");
	while (currentequal >= 0 || currentmore >= 0 || currentless >= 0)
	{
		int current;
		int order = order_of_operands(currentequal, currentmore, currentless);
		if (order == 1) current = currentequal;
		else if (order == 2) current = currentmore;
		else current = currentless;

		int pre_index = find_index(temp, current ,0, 2), next_index = find_index(temp, current ,1, 2);
		InternalVariable next = str_to_var(temp.substr(current + 2, next_index - current - 2).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
		std::string temp_result;
		InternalVariable t_res;
		if (order == 1)
		{
			t_res = next == previous;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else if (order == 2)
		{
			t_res = previous >= next;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else
		{
			t_res = previous <= next;
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
		currentequal = find_in_str(temp, "==");
		currentmore = find_in_str(temp, ">=");
		currentless = find_in_str(temp, "<=");
	}

	while (number_of_char(temp, '>') > 0 || number_of_char(temp, '<') > 0)
	{
		int currentmore = find_in_str(temp, '>'), currentless = find_in_str(temp, '<'), current;
		int order = order_of_operands(currentmore, currentless);
		if (order == 1) current = currentmore;
		else current = currentless;

		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
		std::string temp_result;
		InternalVariable t_res;
		if (order == 1)
		{
			t_res = previous > next;
			temp_result = var_to_str(t_res);
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());
		}
		else
		{
			t_res = previous < next;
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

	while (number_of_char(temp, '*') > 0 || number_of_char(temp, '/') > 0 || number_of_char(temp, '%') > 0)
	{
		int currentstar = find_in_str(temp, '*'), currentslash = find_in_str(temp, '/'), currentpercent = find_in_str(temp, '%'), current;
		int order = order_of_operands(currentstar, currentslash, currentpercent);
		if (order == 1) current = currentstar;
		else if (order == 2) current = currentslash;
		else current = currentpercent;

		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
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
		int currentcross = find_last_of_in_str(temp ,'+'), currentdash = find_last_of_in_str(temp ,'-'), current;
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
		if ((num_operands == 1) && ((number_of_char(temp, '-') == 1) && (temp[0] == '-')) || ((number_of_char(temp, '+') == 1) && (temp[0] == '+')))
			return temp;

		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());

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
		int m1 = lower(find_in_str(temp ,"--"), find_in_str(temp ,"++")), m2 = lower(find_in_str(temp ,"*+"), lower(find_in_str(temp ,"/+"), lower(find_in_str(temp ,"%+"), lower(find_in_str(temp ,"<+") , lower(find_in_str(temp ,">+"), lower(find_in_str(temp ,"!+"), lower(find_in_str(temp ,"=+"), lower(find_in_str(temp ,"&+"), find_in_str(temp ,"|+")))))))))
			,  m3 = lower(find_in_str(temp ,"*-"), lower(find_in_str(temp ,"/-"), lower(find_in_str(temp ,"%-"), lower(find_in_str(temp ,"<-") , lower(find_in_str(temp ,">-"), lower(find_in_str(temp ,"!-"), lower(find_in_str(temp ,"=-"), lower(find_in_str(temp ,"&-"), find_in_str(temp ,"|-")))))))))
			,  m4 = lower(find_in_str(temp ,"<=+"), lower(find_in_str(temp ,">=+"), lower(find_in_str(temp ,"==+"), lower(find_in_str(temp ,"&&+"), find_in_str(temp ,"||+")))))
			,  m5 = lower(find_in_str(temp ,"<=-"), lower(find_in_str(temp ,">=-"), lower(find_in_str(temp ,"==-"), lower(find_in_str(temp ,"&&-"), find_in_str(temp ,"||-")))));
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

		if (m4 >= 0)
		{
			temp = temp.substr(0, m4+1).append(temp.substr(m4+3, size));
			continue;
		}

		if (m5 >= 0)
		{
			int last = find_index_minus(temp, m5);
			if (last <= 0)
			{
				temp = std::string("-").append(temp.substr(0, m5+1)).append(temp.substr(m5+3, size));
			}
			else
			{
				temp = temp.substr(0, m5+1).append(temp.substr(m5+3, size));
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

InternalVariable Aritmathic::parse_aritmathic(std::string arit)
{
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
		return (bool)0;
	else
	{
		if (!has_par)
		{
			return str_to_var(aritmathic_no_parantheses_int(distribute_low_operands(arit)).data());
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
			return str_to_var(aritmathic_no_parantheses_int(distribute_low_operands(temp)).data());
		}
	}
	return (bool)0;
}
