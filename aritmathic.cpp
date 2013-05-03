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

///////////////////////////////////////////////////////////////////
//                                                               //
// IMPORTANT                                                     //
// TODO: We have enough memory leaks to cause a flood. Fix them. //
// IMPORTANT                                                     //
//                                                               //
///////////////////////////////////////////////////////////////////

//checks that if the character is in a string in the code.
//base: base string
//pos: position of the character in base
//sample:
//base:var a = "salam"
//in_string(base, 2):false
//in_string(base, 10):true
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

//returns the number of the character "token" in base if it is not in a string
//sample:
//base:var a = "salam"
//number_of_char(base, 'a') = 2;
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

//finds the location of the first "+" or "-" before location current in string "base"
//sample:
//base:a+3-5*64&&2
//find_index_minus(base, 6):3
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

//finds the location of the first token(non-operator) depending on:
//current:current location
//next: default true, if false, it will find the first token "before" the current
//tokensize: size of the current token (not the one we are looking for). default 1.
//sample:
//base:3*x + 12 - 5
//find_index(base,0):0
//find_index(base,2):6
//find_index(base,2,false):2
//find_index(base,6,true,2):11
int Aritmathic::find_index(std::string base, int current, bool next, int tokensize)
{
	if (next)
	{
		int size = base.size();
		int temp_index = current + tokensize;
		if (temp_index >= size)
			return size;
		char temp_char = base[temp_index];
		while (!((temp_char == '*' || temp_char == '/' || temp_char == '+' || temp_char == '%' || temp_char == '<' || temp_char == '=' || temp_char == '>' || temp_char == '!' || temp_char == '&' || temp_char == '|') && !in_string(base, temp_index)))
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
		while (!((temp_char == '*' || temp_char == '/' || temp_char == '+' || temp_char == '%' || temp_char == '<' || temp_char == '=' || temp_char == '>' || temp_char == '!' || temp_char == '&' || temp_char == '|') && !in_string(base, temp_index)))
		{
			--temp_index;
			if (temp_index <= 0)
				return 0;
			temp_char = base[temp_index];
		}
		return temp_index;
	}
}

//returns the number of "!" characters in "base". doesn't count "!="
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

//finds the last instance of "c" in the given string. doesn't count the ones between two semicolons
//sample:
//base:var a = "salam"
//find_last_of_in_str(base, 'a'):4
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

//finds the first instance of "c" in the given string. doesn't count the ones between two semicolons 
//sample:
//base:var a = "salam"
//find_in_str(base, 'a'):1
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

//finds the first instance of string in the given string. doesn't count the ones between two semicolons 
//sample:
//base:var a = "var"; var b = 3;
//find_in_str(base, 'var'):0
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

//finds the first operator from the ones in "operators" we encounter in the string "arit"
//returns an "operator_order" struct. "pos" will be the postion of the operator and
//order will be the -order- of the operator in the definition
//sample:
//arit:"2/4%5*6"
//find_operator(arit,"*","/","%"):operator_order{pos = 1, order = 2}
//arit2:"2*4%5*6"
//find_operator(arit2,"*","/","%"):operator_order{pos = 1, order = 1}
//arit3:"2%4%5*6"
//find_operator(arit3,"*","/","%"):operator_order{pos = 1, order = 3}
operator_order find_operator(std::string arit, std::string operator1, std::string operator2, std::string operator3)
{
	int size = arit.size();
	int operator1_size = operator1.size();
	int operator2_size = operator2.size();
	int operator3_size = operator3.size();
	operator_order ret;
	for (int i = 0; i < size; ++i)
	{
		if ((i + operator1_size < size) && (!in_string(arit, i)) && (arit.substr(i, operator1_size) == operator1))
		{
			ret.pos = i;
			ret.order = 1;
			return ret;
		}
		if ((i + operator2_size < size) && (!in_string(arit, i)) && (arit.substr(i, operator2_size) == operator2))
		{
			ret.pos = i;
			ret.order = 2;
			return ret;
		}
		if ((i + operator3_size < size) && (!in_string(arit, i)) && (arit.substr(i, operator3_size) == operator3))
		{
			ret.pos = i;
			ret.order = 3;
			return ret;
		}
	}
	ret.pos = -1;
	return ret;
}

operator_order find_operator(std::string arit, std::string operator1, std::string operator2)
{
	int size = arit.size();
	int operator1_size = operator1.size();
	int operator2_size = operator2.size();
	operator_order ret;
	for (int i = 0; i < size; ++i)
	{
		if ((i + operator1_size < size) && (!in_string(arit, i)) && (arit.substr(i, operator1_size) == operator1))
		{
			ret.pos = i;
			ret.order = 1;
			return ret;
		}
		if ((i + operator2_size < size) && (!in_string(arit, i)) && (arit.substr(i, operator2_size) == operator2))
		{
			ret.pos = i;
			ret.order = 2;
			return ret;
		}
	}
	ret.pos = -1;
	return ret;
}

//the heart of the whole program
//input:a string of arithmetic operation without parantheses or spaces:"2*4/2==6"
//output:the result:0 (false)
/////////////////////////////
// TODO: add "^" operator  //
/////////////////////////////
std::string Aritmathic::aritmathic_no_parantheses_int(std::string arit)
{
	//operator priority
	// !
	// *    /     %
	// +    -
	// &&   ||    !=
	// ==   >=    <=
	// <    >
	
	//copy the main data into temp
	std::string temp(arit.data());

	//handle the nots ("!")
	//it doesn't count the nots in "!=" so we don't need to worry about it
	while (number_of_nots(temp) > 0)
	{
		//find the first "not"
		int current = find_in_str(temp, '!');

		//as find_in_str() doesn't check, we have to make sure that this is not a "!=", but a real not.
		if ((temp.size() != current+1) && (temp[current+1] != '='))
		{
			//find the next token (in this case: variable or number)
			int next_index = find_index(temp, current ,1);
			// now that we know the position of the next variable, we should turn it into an InternalVariable so we can do the operaions on it
			// so we use str_to_var() to do the conversation
			InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
			
			//resaults
			std::string temp_result;
			InternalVariable t_res;
			
			//do the "not" operation
			t_res = next.nots();

			//save the result in a string
			temp_result = var_to_str(t_res);
			
			//very important: needed for "+" and "-"'s proper work
			if ((t_res.positive()) && (t_res.get_type() != String)) temp_result = std::string("+").append(temp_result.data());

			//replace the older operation with the result
			std::string temp2("");
			if (current > 0)
				temp2.append(temp.substr(0,current-1)).append(temp_result).append(temp.substr(next_index,temp.size()));
			else
				temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
			
			//change the temp
			temp = std::string(temp2.data());
		}
	}
	
	//handle the "*, /, %" operators
	while (number_of_char(temp, '*') > 0 || number_of_char(temp, '/') > 0 || number_of_char(temp, '%') > 0)
	{
		//we should calculate the operators from left to right. so we use this function
		operator_order ord = find_operator(temp, "*", "/", "%");
		int order = ord.order;
		int current = ord.pos;

		// now that we know which operator to calculate first, we should find the variables to do the operation on
		//find the location of those variables in the string
		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		
		//create InternalVariables from them
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
		
		//result
		std::string temp_result;
		InternalVariable t_res;
		
	
		if (order == 1) // it means "*"
		{
			//do the calculation
			t_res = next * previous;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else if (order == 2) // it means "/"
		{
			//do the calculation
			t_res = previous / next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else // it means "%"
		{
			//do the calculation
			t_res = previous % next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}

		//replace the older operation with the result
		std::string temp2("");
		if (pre_index > 0)
			temp2.append(temp.substr(0,pre_index+1)).append(temp_result).append(temp.substr(next_index,temp.size()));
		else
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
			
		//change the temp
		temp = handle_minuses_and_pluses(temp2.data());
	}

	//handle the "+" operator
	while (number_of_char(temp, '+') > 0)
	{
		//finding the first "+"
		int	current = find_last_of_in_str(temp ,'+');

		//now that we know which operator to calculate first, we should find the variables to do the operation on
		//find the location of those variables in the string
		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);
		
		//create InternalVariables from them
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());

		//result
		std::string temp_result;
		InternalVariable t_res;
		
		//do the calculation
		t_res =  previous + next;
		
		//create a string out of it
		temp_result = var_to_str(t_res);

		//create a clean string
		std::string temp2("");
		
		//replace the older operation with the result
		if (pre_index > 0)
		{
			temp2.append(temp.substr(0,pre_index+1)).append(temp_result).append(temp.substr(next_index,temp.size()));
		}
		else
		{
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
		}
		
		//distribute_low_operands() is to avoid and handle something like "2&&+3" which will certainly cause some major 
		//problems for this very loop (and the whole operation)
		temp = handle_minuses_and_pluses(std::string(temp2.data()));
	}

	//handle "&&", "||" and "!="
	//as we have declared find_in_str() as an unsigned int, we should turn these into ints before doing anything else or they'll always be positive
	int currentand = find_in_str(temp, "&&"), currentor = find_in_str(temp, "||"), currentnotequal = find_in_str(temp ,"!=");
	while (currentand >= 0 || currentor >= 0 || currentnotequal >= 0)
	{
		//we should calculate the operators from left to right. so we use this function
		operator_order ord = find_operator(temp, "&&", "||", "!=");
		int order = ord.order;
		int current = ord.pos;

		// now that we know which operator to calculate first, we should find the variables to do the operation on
		//find the location of those variables in the string
		int pre_index = find_index(temp, current ,0, 2), next_index = find_index(temp, current ,1, 2);
		
		//create InternalVariables from them
		InternalVariable next = str_to_var(temp.substr(current + 2, next_index - current - 2).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
		
		//result
		std::string temp_result;
		InternalVariable t_res;
		
		
		if (order == 1) // it means "&&"
		{
			//do the calculation
			t_res = next && previous;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else if (order == 2) // it means "||"
		{
			//do the calculation
			t_res = previous || next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else // it means "!="
		{
			//do the calculation
			t_res = (previous == next).nots();
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}

		//replace the older operation with the result
		std::string temp2("");
		if (pre_index > 0)
			temp2.append(temp.substr(0,pre_index)).append(temp_result).append(temp.substr(next_index,temp.size()));
		else
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
			
		//change the temp
		temp = handle_minuses_and_pluses(temp2.data());

		//search for the operations again
		currentand = find_in_str(temp ,"&&");
		currentor = find_in_str(temp ,"||");
		currentnotequal = find_in_str(temp ,"!=");
	}

	//handle "==", ">=" and "<="
	//as we have declared find_in_str() as an unsigned int, we should turn these into ints before doing anything else or they'll always be positive
	int currentequal = find_in_str(temp, "=="), currentmore = find_in_str(temp, ">="), currentless = find_in_str(temp ,"<=");
	while (currentequal >= 0 || currentmore >= 0 || currentless >= 0)
	{
		//we should calculate the operators from left to right. so we use this function
		operator_order ord = find_operator(temp, "==", ">=", "<=");
		int order = ord.order;
		int current = ord.pos;

		// now that we know which operator to calculate first, we should find the variables to do the operation on
		//find the location of those variables in the string
		int pre_index = find_index(temp, current ,0, 2), next_index = find_index(temp, current ,1, 2);

		//create InternalVariables from them
		InternalVariable next = str_to_var(temp.substr(current + 2, next_index - current - 2).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
	
		//result
		std::string temp_result;
		InternalVariable t_res;
		
		
		if (order == 1) // it means "=="
		{
			//do the calculation
			t_res = next == previous;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else if (order == 2) // it means ">="
		{
			//do the calculation
			t_res = previous >= next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else // it means "<="
		{
			//do the calculation
			t_res = previous <= next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}

		//replace the older operation with the result
		std::string temp2("");
		if (pre_index > 0)
			temp2.append(temp.substr(0,pre_index)).append(temp_result).append(temp.substr(next_index,temp.size()));
		else
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
		
		//change the temp
		temp = handle_minuses_and_pluses(temp2.data());

		//search for the operations again
		currentequal = find_in_str(temp, "==");
		currentmore = find_in_str(temp, ">=");
		currentless = find_in_str(temp, "<=");
	}

	//handle ">" and "<"
	while (number_of_char(temp, '>') > 0 || number_of_char(temp, '<') > 0)
	{
		//we should calculate the operators from left to right. so we use this function
		operator_order ord = find_operator(temp, ">", "<");
		int order = ord.order;
		int current = ord.pos;

		// now that we know which operator to calculate first, we should find the variables to do the operation on
		//find the location of those variables in the string
		int pre_index = find_index(temp, current ,0), next_index = find_index(temp, current ,1);

		//create InternalVariables from them
		InternalVariable next = str_to_var(temp.substr(current + 1, next_index - current - 1).data());
		InternalVariable previous = str_to_var(temp.substr(pre_index, current - pre_index).data());
		
		//result
		std::string temp_result;
		InternalVariable t_res;
		
		
		
		if (order == 1) // it means ">"
		{
			//do the calculation
			t_res = previous > next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		else // it means "<"
		{
			//do the calculation
			t_res = previous < next;
			
			//create a string out of it
			temp_result = var_to_str(t_res);
		}
		
		//replace the older operation with the result
		std::string temp2("");
		if (pre_index > 0)
			temp2.append(temp.substr(0,pre_index)).append(temp_result).append(temp.substr(next_index,temp.size()));
		else
			temp2.append(temp_result).append(temp.substr(next_index,temp.size()));
			
		//change the temp
		temp = handle_minuses_and_pluses(temp2.data());
	}

	//after we calculated all of the operations, we have only one variable (string) left. return it.
	return temp.data();
}

// finds which one of the two is lower than the other. if one of them is negative, returns the other one instead.
int lower(int a , int b)
{
	if (a < 0) return b;
	else if (b < 0) return a;
	else if (a < b) return a;
	else if (b < a) return b;
	else return a;
}

//adds a "+" before "lone" minuses. changes "--" to "+" or removes them
//a lone minus is one where the charachter before it is a number
//removes non-lone pluses
std::string Aritmathic::handle_minuses_and_pluses(std::string arit)
{
	std::string temp(arit.data());
	int i = 1, size = temp.size();

	if ((size >= 2) && (temp[0] == '-') && (temp[1] == '-'))
	{
		temp = temp.substr(2,size);
		size -= 2;
	}

	while (true)
	{
		if (i >= size)
			break;

		char s = temp[i-1];

		if (temp[i] == '-')
		{
			if (i+1 < size)
			{
				char t = temp[i+1];
				if (t == '-')
				{
					if ((s != '=') && (s != '<') && (s != '>') && (s != '/') && (s != '+') && (s != '&') && (s != '|') && (s != '%') && (s != '*'))
					{
						temp = std::string(temp.substr(0, i).data()).append("+").append(temp.substr(i+2, size));
						--size;
						s = temp[i];
					}
					else
					{
						temp = std::string(temp.substr(0, i).data()).append(temp.substr(i+2, size));
						size -= 2;
						i -= 1;
						s = temp[i];
					}
				}
			}

			if ((s != '=') && (s != '<') && (s != '>') && (s != '/') && (s != '+') && (s != '&') && (s != '|') && (s != '%') && (s != '*'))
			{
				temp = std::string(temp.substr(0, i).data()).append("+").append(temp.substr(i, size));
				++size;
				++i;
			}

		}
		else if (temp[i] == '+')
		{
			if ((s == '=') || (s == '<') || (s == '>') || (s == '/') || (s == '+') || (s == '&') || (s == '|') || (s == '%') || (s == '*') || (s == '-'))
			{
				temp = std::string(temp.substr(0, i).data()).append(temp.substr(i+1, size));
				--size;
				--i;
			}
		}
		++i;
	}
	return temp;
}

// returns the start and end of the innermost parantheses it can find as an array of int[2]
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

//a level higher than aritmathic_no_parantheses_int().
//input:a string of arithmetic operation --with-- parantheses --without-- spaces:"(2+3)/5"
//output:the result:1
InternalVariable Aritmathic::parse_aritmathic(std::string arit)
{
	//some helpers
	int temp_par = 0;
	bool has_par = false;
	
	//check if the number of openings and closings are equal
	for (unsigned int i = 0; i < arit.size(); ++i)
	{
		if (arit[i] == '(')
		{
			temp_par++;
			has_par = true;
		}
		else if (arit[i] == ')')
			temp_par--;

		//if we have mismatching parantheses
		if (temp_par < 0)
			return (bool)0;
	}

	//if we don't have any parantheses, go on and just calculate the whole thing
	if (!has_par)
	{
		return str_to_var(aritmathic_no_parantheses_int(handle_minuses_and_pluses(arit)).data());
	}
	else
	{
		//now we should handle the parantheses. copy the insides of arit
		std::string temp(arit.data());
		
		//we will replace the parantheses with their arithmetic equivalant until there isn't any remaining
		while (number_of_char(temp, '('))
		{
			//we need a clear string first
			std::string temp2("");
			
			//find the beginning and ending of the first innermost parantheses
			int* pos = find_parantheses(temp);
			
			//create a variable to store the size so we don't need to call the function 4-5 times.
			int size = temp.size();
			
			//find the arithmetic equivalant of the parantheses.
			std::string temp_result = aritmathic_no_parantheses_int(handle_minuses_and_pluses(temp.substr(pos[0]+1, pos[1]-pos[0]-1))), last_par = (pos[1]+1 > size? std::string("") : temp.substr(pos[1]+1,size));
			
			//and put it in their place
			if (pos[0] > 0)
				temp2.append(temp.substr(0,pos[0])).append(temp_result).append(last_par);
			else
				temp2.append(temp_result).append(last_par);
				
			//now change the "temp"
			temp = std::string(temp2.data());
		}
		
		//we don't have any paranthese left. so try the calculate the arithmetic result one more time and return the result as an InternalVariable.
		return str_to_var(aritmathic_no_parantheses_int(handle_minuses_and_pluses(temp)).data());
	}
	
	//something went wrong. return false.
	return (bool)0;
}
