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

std::string g_previous_statement("");

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

/*unsigned int find_last_of_in_str(std::string str, char c)
{
	unsigned int size = str.size();
	for (int i = size - 1; i >= 0; --i)
	{
		if (str[i] == c && !inside_string(str, i))
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
		if (str[i] == c && !inside_string(str, i))
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
				if (str[i+j] != cs[j] || inside_string(str, i))
				{
					break;
				}
				if (j == csize - 1)
					return i;
			}
		}
	}
	return -1;
}*/

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
	return std::string("");
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
			if (i == size-1)
			{
				Token ret;
				ret.str = base.substr(start, i - start + 1);
				ret.pos = start;
				return ret;
			}
			else if (is_in_string(base[i], it) && !inside_string(base, i))
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

int get_plusplus_argument(std::string base, int location, bool next = true, bool plusplus = true)
{
    int size = base.size();
    if (location < 0)
       return -1;
    if (next)
    {
        if (plusplus)
        {
           for (int i = location; i < size; ++i)
           {
               if (!is_whitespace(base[i]))
               {
                   if (i < (size-1) && (base[i] == '+' && base[i+1] == '+'))
                   {
                      return i;
                   }
                   else
                   {
                      return -1; 
                   } 
               }
               else
               {
                   return -1;
               }
           } 
        }
        else
        {
           for (int i = location; i < size; ++i)
           {
               if (!is_whitespace(base[i]))
               {
                   if (i < (size-1) && (base[i] == '-' && base[i+1] == '-'))
                   {
                      return i;
                   }
                   else
                   {
                      return -1; 
                   } 
               }
               else
               {
                   return -1;
               }
           } 
        }
    }
    else
    {
        if (plusplus)
        {
           for (int i = location; i >= 0; --i)
           {
               if (!is_whitespace(base[i]))
               {
                   if (i > 1 && (base[i] == '+' && base[i-1] == '+'))
                   {
                      return i-1;
                   }
                   else
                   {
                      return -1; 
                   } 
               }
               else
               {
                   return -1;
               }
           } 
        }
        else
        {
           for (int i = location; i >= 0; --i)
           {
               if (!is_whitespace(base[i]))
               {
                   if (i > 1 && (base[i] == '-' && base[i-1] == '-'))
                   {
                      return i-1;
                   }
                   else
                   {
                      return -1; 
                   } 
               }
               else
               {
                   return -1;
               }
           } 
        }
    }
    return -1;
}

InternalVariable Interpreter::do_arit(std::string statement)
{
	// TODO: Reza: this function returns the result of an operation. For example:
	// if we have two variables x=4 , y =3.7
	// do_arit("5-x*(y+1)") returns the variable:
	// InternalVariable(-13.7);
	// you must use it for the calculation in your work. e.g. "m = 5-x*(y+1)" must change the value of m 
	//(using this->variable_table.change_var()) to -13.7  
	// see var_statement() for something very similar
	unsigned int size = statement.size();
	std::string level3 = statement;
	Token temp;
	temp.str = std::string("");
	temp.pos = 0;
	while (temp.pos < size)
	{
		temp = get_next_token(level3, "!%&*()/|-+<>= \n\t" ,temp.pos + temp.str.size());
		if (is_var(temp.str))
		{
			InternalVariable tempvar = this->variable_table.get_var(temp.str);
            int prevpp = get_plusplus_argument(level3, temp.pos - 1, false);
            if (prevpp >= 0)
            {
                 this->variable_table.change_var(temp.str, (tempvar + (long long)1));
                 tempvar = this->variable_table.get_var(temp.str);
                 level3 = level3.substr(0, prevpp).append(level3.substr(prevpp+2,size));
  			     temp.pos -= 2;
            }
            else
            {
                 int prevmm = get_plusplus_argument(level3, temp.pos - 1, false, false);
                 if (prevmm >= 0)
                 {
                     this->variable_table.change_var(temp.str, (tempvar - (long long)1));
                     tempvar = this->variable_table.get_var(temp.str);
                     level3 = level3.substr(0, prevmm).append(level3.substr(prevmm+2,size));
                     temp.pos -= 2;
                 }
            }
  			size = level3.size();
			level3 = level3.substr(0, temp.pos).append(var_to_str(tempvar)).append(level3.substr(temp.pos + temp.str.size(),size));
            int nextpp = get_plusplus_argument(level3, temp.pos + temp.str.size());
            if (nextpp >= 0)
            {
                 this->variable_table.change_var(temp.str, (tempvar + (long long)1));
                 level3 = level3.substr(0, nextpp).append(level3.substr(nextpp+2,size));
            }
            else
            {
                 int nextmm = get_plusplus_argument(level3, temp.pos + temp.str.size(), true, false);
                 if (nextmm >= 0)
                 {
                     this->variable_table.change_var(temp.str, (tempvar - (long long)1));
                     level3 = level3.substr(0, nextmm).append(level3.substr(nextmm+2,size));
                 }
            }
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
	int equal = find_in_str(level2, '=');
	int end = find_in_str(level2, ';');
	if (equal < 0)
	{
		this->variable_table.add_var(remove_whitespaces(level2.substr(0,level2.size()-1)));
	}
	else
	{	//if we are going to set the value as well.
		std::string name = remove_whitespaces(level2.substr(0,equal));
		this->variable_table.add_var(name);
		this->variable_table.change_var(name, do_arit(level2.substr(equal+1,end-equal-1)));
	}
}

void Interpreter::print_statement(std::string statement)
{
	std::string level2 = statement.substr(6, statement.size());
	int end = find_in_str(level2, ';');
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

void Interpreter::get_statement(std::string statement)
{
	std::string level2 = statement.substr(4, statement.size());
	int end = find_in_str(level2, ';');
	std::string name = get_next_token(level2.substr(0,end), " \t\n").str;
	char* input = new char[64];
	std::cin >> input;
	this->variable_table.change_var(name, str_to_var(std::string(input)));
}

void Interpreter::if_statement(std::string statement)
{
	std::string level2 = statement.substr(2, statement.size());
	int begin = find_in_str(level2, '{');
	int end = find_last_of_in_str(level2, '}');
	InternalVariable condition = do_arit(level2.substr(0,begin));
	if (condition.condition())
	{
		this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
	}
}

void Interpreter::while_statement(std::string statement)
{
	std::string level2 = statement.substr(5, statement.size());
	int begin = find_in_str(level2, '{');
	int end = find_last_of_in_str(level2, '}');
	std::string str_condition = level2.substr(0,begin);
	InternalVariable condition = do_arit(str_condition);
	while (condition.condition())
	{
		this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
		condition = do_arit(str_condition);
	}
}

void Interpreter::for_statement(std::string statement)
{
	std::string level2 = statement.substr(4, statement.size());
	int begin = find_in_str(level2, '{');
	int end = find_last_of_in_str(level2, '}');
	int scl1 = find_in_str(level2, ',');
	int scl2 = find_last_of_in_str(level2, ',');
	int par1 = find_in_str(level2, '(');
	int par2 = find_last_of_in_str(level2, ')');
	std::string str_one_time = level2.substr(par1+1,scl1);
	std::string str_condition = level2.substr(scl1+1,scl2-scl1-1);
	std::string str_always = level2.substr(scl2+1,par2-scl2-1);
	statement_analyzer(str_one_time);
	InternalVariable condition = do_arit(str_condition);
	while (condition.condition())
	{
		statement_analyzer(str_always);
		this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
		condition = do_arit(str_condition);
	}
}

void Interpreter::statement_analyzer(std::string statement)
{
	if (statement.size() > 0)
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
		else if (level1.find("get ") == 0)
		{
			get_statement(level1);
		}
		else if (level1.find("if") == 0 && is_in_string(level1[2], "\t\n ("))
		{
			if_statement(level1);
		}
		else if (level1.find("while") == 0 && is_in_string(level1[5], "\t\n ("))
		{
			while_statement(level1);
		}
		else if (level1.find("for") == 0 && is_in_string(level1[3], "\t\n ("))
		{
			for_statement(level1);
		}
		else if (level1.find("pause") == 0)
		{
			system("PAUSE");
		}

		g_previous_statement = statement;
	}
}

bool is_outside_cr(std::string base, unsigned long long pos)
{
	int number = 0; 
	if ((base[pos] == '}' || base[pos] == ';') && (!inside_string(base, pos)))
	{
		for (unsigned long long i = 0; i <= pos; ++i)
		{
			if (base[i] == '{')
				++number;
			else if (base[i] == '}')
				--number;
		}
		return (number == 0 ? true : false);
	}
	return false;
}

Token get_next_statement(std::string base, unsigned long long pos = 0)
{
	int size = base.size(), start = 0;
	bool found = false;
	for (int i = pos; i < size; ++i)
	{
		if (!found)
		{
			if (!is_outside_cr(base, i))
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
			if (i == size-1)
			{
				Token ret;
				ret.str = base.substr(start, i - start + 1);
				ret.pos = start;
				return ret;
			}
			else if (is_outside_cr(base, i))
			{
				Token ret;
				ret.str = base.substr(start, i - start + 1);
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

std::string check_for_backslashes(std::string base)
{
	unsigned long long size = base.size();
	std::string temp = "";
	for (unsigned int i = 0; i < size; ++i)
	{
		if (base[i] == '\\' && inside_string(base, i))
		{
			if (i < size-1)
			{
				if (base[i+1] == '\\')
				{
					temp.push_back('\\');
					++i;
				}
				else if (base[i+1] == 'n')
				{
					temp.push_back('\n');
					++i;
				}
				else if (base[i+1] == 't')
				{
					temp.push_back('\t');
					++i;
				}
			}
		}
		else
		{
			temp.push_back(base[i]);
		}
	}
	return temp;
}

bool is_if(std::string statement)
{
     std::string level1 = remove_whitespaces(statement, true);
     if (level1.find("if") == 0 && is_in_string(level1[2], "\t\n ("))
     {
        return true;                      
     }
     return false;
}

bool is_else(std::string statement)
{
     std::string level1 = remove_whitespaces(statement, true);
     if (level1.find("else") == 0 && is_in_string(level1[5], "\t\n ("))
     {
        return true;                      
     }
     return false;
}

void Interpreter::code_analyzer(std::string code, bool checked)
{
	std::string refined_code;
	if (checked)
		refined_code = code;
	else
		refined_code = check_for_backslashes(code);
	unsigned long long size = refined_code.size();
	Token temp;
	temp.str = std::string("");
	temp.pos = 0;
	while (temp.pos + temp.str.size() < size)
	{
		temp = get_next_statement(refined_code, temp.pos + temp.str.size());
		if (is_if(temp.str))
		{
           Token temp2 = get_next_statement(refined_code, temp.pos + temp.str.size());
           std::string temp3("");
           if (is_else(temp2.str))
           {
               while (is_else(temp2.str))
               {
                   temp3.append(temp2.str);
                   temp2 = get_next_statement(refined_code, temp2.pos + temp2.str.size());
               }
               statement_analyzer(temp3);
               temp = temp2;
           }
           statement_analyzer(temp.str);
        }
        else
        {
             statement_analyzer(temp.str);
        }
	}
}
