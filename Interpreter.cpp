#ifndef _INTERPRETER_H_
#include "interpreter.h"
#endif

#ifndef _STRING_H_
#include <string>
#endif

#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#ifndef _ARITMATHIC_H_
#include "aritmathic.h"
#endif

#ifndef _VARTABLE_H_
#include "vartable.h"
#endif

#ifndef _IOSTREAM_H_
#include <iostream>
#endif

bool inside_string(std::string base, unsigned int pos)
{
	bool is = false;
	for (unsigned int i = 0; i < pos; ++i)
	{
		if (base[i] == '"')
			is = !is;
	}
	return is;
}

bool is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
	{
		return true;
	}
	return false;
}

std::string remove_whitespaces(std::string statement, bool only_left = false)
{
	int size = statement.size();
	if (only_left)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!is_whitespace(statement[i]))
			{
				return statement.substr(i,size);
			}
		}
	}
	else
	{
		std::string temp("");
		for (int i = 0; i < size; ++i)
		{
			if (!is_whitespace(statement[i]) || inside_string(statement, i))
			{
				temp.push_back(statement[i]);
			}
		}
		return temp;
	}
}

bool is_in_string(char c, char* it)
{
	unsigned int size = std::string(it).size();
	for (unsigned int i = 0; i < size; ++i)
	{
		if (c == it[i])
			return true;
	}
	return false;
}

Token get_next_token(std::string base, char* it, unsigned int pos = 0)
{
	int size = base.size(), start;
	bool found = false;
	for (int i = pos; i < size; ++i)
	{
		if (!found)
		{
			if (!is_in_string(base[i], it))
			{
				start = i;
				found = true;
				if (i+1 == size)
				{
					Token ret;
					ret.str = base.substr(start, size - start);
					ret.pos = start;
					return ret;
				}
			}
		}
		else
		{
			if (is_in_string(base[i], it))
			{
				Token ret;
				ret.str = base.substr(start, i - start);
				ret.pos = start;
				return ret;
			}
		}
	}
	Token ret;
	ret.str = std::string("");
	ret.pos = base.size();
	return ret;
}

bool is_var(std::string base)
{
	if (base.size() == 0 || base[0] == '"' || is_in_string(base[0], "0123456789"))
	{
		return false;
	}
	return true;
}

InternalVariable Interpreter::do_arit(std::string statement)
{
	// TODO: Reza: this function returns the result of an operation. For example:
	// if we have two variables x=4 , y =3.7
	// do_arit("5-x*(y+1)") returns the variable:
	// InternalVariable(-13.7);
	// you must use it for the calculation in your work. e.g. "m = 5-x*(y+1)" must change the value of m 
	//(using this->variable_table.change_var()) to -13.7  
	unsigned int size = statement.size();
	std::string level3 = statement;
	Token temp;
	temp.str = std::string("");
	temp.pos = 0;
	while (temp.pos < size)
	{
		temp = get_next_token(level3, "!%&*()/|-= \n\t" ,temp.pos + temp.str.size());
		if (is_var(temp.str))
		{
			InternalVariable tempvar = this->variable_table.get_var(temp.str);
			level3 = level3.substr(0, temp.pos).append(var_to_str(tempvar)).append(level3.substr(temp.pos + temp.str.size(),size));
			size = level3.size();
		}
	}
	level3 = remove_whitespaces(level3);
	Aritmathic s;
	return s.parse_aritmathic(level3);
}

void Interpreter::var_statement(std::string statement)
{
	std::string level2 = statement.substr(4, statement.size());
	int equal = level2.find('=');
	int end = level2.find(';');
	if (equal < 0)
	{
		this->variable_table.add_var(remove_whitespaces(level2.substr(0,level2.size()-1)));
	}
	else
	{
		std::string name = remove_whitespaces(level2.substr(0,equal));
		this->variable_table.add_var(name);
		this->variable_table.change_var(name, do_arit(level2.substr(equal+1,end-equal-1)));
	}
}

void Interpreter::print_statement(std::string statement)
{
	std::string level2 = statement.substr(6, statement.size());
	int end = level2.find(';');
	InternalVariable output = do_arit(level2.substr(0,end));
	if (output.get_type() == Boolean)
	{
		std::cout << output.get_bool_value();
	}
	else if (output.get_type() == Integer)
	{
		std::cout << output.get_int_value();
	}
	else if (output.get_type() == Float)
	{
		std::cout << output.get_float_value();
	}
	else if (output.get_type() == String)
	{
		std::cout << output.get_string_value();
	}
}

void Interpreter::statement_analyzer(std::string statement)
{
	std::string level1 = remove_whitespaces(statement, true);
	if (level1.find("var ") == 0)
	{
		var_statement(level1);
	}
	else if (level1.find("print ") == 0)
	{
		print_statement(level1);
	}
	else if (level1.find("pause") == 0)
	{
		system("PAUSE");
	}
}