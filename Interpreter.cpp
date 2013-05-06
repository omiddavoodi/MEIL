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

// global helper
std::string g_previous_statement("");

//checks that if the character is in a string in the code.
//base: base string
//pos: position of the character in base
//sample:
//base:var a = "salam"
//in_string(base, 2):false
//in_string(base, 10):true
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

// checks if the character "c" is a whitespace ("space", "tab" or "enter")
bool is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
	{
		return true;
	}
	return false;
}

//removes the whitespaces from the given string
//only_left: if true, the function only removes the first group of whitespeces. look at example
//sample:
//base:"  var a = 5 + 3 / 4"
//remove_whitespaces(base):"var a = 5 + 3 / 4"
//remove_whitespaces(base, false):"vara=5+3/4"
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

// checks if charachter "c" is inside the string "it"
// sample:
// base:"salam"
// is_in_string('a', base):true
// is_in_string('g', base):false
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

// returns the next Token (definition in Interpreter.h) that is 
// the next required string "chunk" we need and its location in the base string
// the chunks are separated by charachters defined in "it". see the examples
// samples:
// base = "		var a;\n	 get a;\n	 	print a"
// get_next_token(base, " \t\n;", 0): Token{str="var", pos=2}
// get_next_token(base, " \t\n;", 5): Token{str="a", pos=6}
// get_next_token(base, " \t\n;", 7): Token{str="get", pos=11}
// get_next_token(base, ";", 0): Token{str="		var a", pos=0}
// get_next_token(base, ";", 7): Token{str="\n	 get a", pos=8}
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

// determines if the string base is a true variable name. --doesn't-- determine if we have
// a variable with this name in our table. just if what we have here has the potential to be
// a proper name for a variable.
// variable names don't start with numbers, cotation marks or have a length of zero.
// is_var("a") = true;
// is_var("a5") = true;
// is_var("1g") = false;
bool is_var(std::string base)
{
	if (base.size() == 0 || base[0] == '"' || is_in_string(base[0], "0123456789"))
	{
		return false;
	}
	return true;
}

// finds the next or previous "++" or "--" in our string from our "location"
// if next is true, it searches after the location. if it is false, it searches before the location
// if plusplus is true, it searches for "++", if it is false, it searches for "--"
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

// in this function, we replace the variable names with their values, 
// remove the whitespace, and send the result to aritmethic unit for computation
InternalVariable Interpreter::do_arit(std::string statement)
{
	//helper variables
	unsigned int size = statement.size();
	std::string level3 = statement;
	Token temp;
	temp.str = std::string("");
	temp.pos = 0;
	//do this until we have reached the end of the statement
	while (temp.pos < size)
	{
		//it is better to read the comments on "get_next_token()" to better understand this
		//find the next token. with "it" at this value, the only things we'll find as tokens are variable names,
		//strings and numbers which are the ones we need
		//each time we want the next token, we should pass the previous one. so we set the new "location" to 
		//"temp.pos + temp.str.size()" so we are starting right after the older token.
		temp = get_next_token(level3, "!%&*()/|-+<>= \n\t" ,temp.pos + temp.str.size());
		
		//what we want to do is to replace the variable names with their values.
		//so. after we found the next token, we should see if it is a variable or not
		//at first, we should see if it has a proper variable name at all, or is a 
		//number or string. so we use is_var() first.
		if (is_var(temp.str))
		{
			// now that we are sure that this is a proper variable name, we are going to search the variable table
			// because of the mechanism of the vartable class, we always end up with a variable. even if it isn't defined before
			// in fact, it will define it in this case.
			InternalVariable tempvar = this->variable_table.get_var(temp.str);
			
			//handle the "++" or "--" --before-- the variable, which changes the value --before-- replacing its name
			//with its value. so in "b = 1; a = ++b;", a is "2" and b is "2"; 			
            // "++"
			int prevpp = get_plusplus_argument(level3, temp.pos - 1, false);
            if (prevpp >= 0)
            {
				//we have a "++" before the variable name. so add to its value 
                this->variable_table.change_var(temp.str, (tempvar + (long long)1));
				
                //change the value of the tempvar, so the change is also mirrored in the base string
				tempvar = this->variable_table.get_var(temp.str);
				
				//remove the "++"
                level3 = level3.substr(0, prevpp).append(level3.substr(prevpp+2,size));
				
				//we remove the "++". so our string is 2 bytes shorter. change the position of temp accordingly
  			    temp.pos -= 2;
            }
            else
            {
				//we didn't have a "++" before our variable. so chack for "--"
                int prevmm = get_plusplus_argument(level3, temp.pos - 1, false, false);
                if (prevmm >= 0)
                {
					//we have a "--" before the variable name. so remove from its value 
                    this->variable_table.change_var(temp.str, (tempvar - (long long)1));
					
					//change the value of the tempvar, so the change is also mirrored in the base string
                    tempvar = this->variable_table.get_var(temp.str);
					
					//remove the "--"
                    level3 = level3.substr(0, prevmm).append(level3.substr(prevmm+2,size));
					
					//we remove the "--". so our string is 2 bytes shorter. change the position of temp accordingly
                    temp.pos -= 2;
                }
            }
			
			//we have handled "++"s and "--"s. now we have to replace the variable names with their values.
			//chaneg the size to correspond with the new one
  			size = level3.size();
			
			//replace the names with values
			level3 = level3.substr(0, temp.pos).append(var_to_str(tempvar)).append(level3.substr(temp.pos + temp.str.size(),size));
            
			//now we should handle the "++" and "--" after the variables. they are changed --after-- we replace the names with values.
			//it works similar to the code above
			int nextpp = get_plusplus_argument(level3, temp.pos + temp.str.size());
            if (nextpp >= 0)
            {
                this->variable_table.change_var(temp.str, (tempvar + (long long)1));

				//we don't need to change tempvar so just remove the "++"
				level3 = level3.substr(0, nextpp).append(level3.substr(nextpp+2,size));
				//as this time "++" is "after" the variable name, our location doesn't change
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
			///////////////////////////////////////////////////////////////////////////////////////////
			// TODO: I think we should reposition the "temp" token after this. it may cause problems //
			///////////////////////////////////////////////////////////////////////////////////////////
			//again change the size
  			size = level3.size();
		}
	}
	
	//now that we have replaced the variable names with their values, we have a string with only values,
	//operators and whitespaces. we should remove them now as parse_aritmathic() doesn't support whitespaces
	level3 = remove_whitespaces(level3);
	
	//now, send the result to aritmethic unit for final computation
	Aritmathic s;
	return s.parse_aritmathic(level3);
}

//handling "var" statement.
//input:a valid "var" statement e.g. "var s = 7;" or "var fal;"
//adds the variable to our vartable
//changes it if needed
///////////////////////////////////////////////////////////////////////////
//                                                                       //
// TODO:add multi-definition. like: "var s = 5, g = 7, ham, str_salam;"  //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
void Interpreter::var_statement(std::string statement)
{
	//remove "var" itself
	std::string level2 = statement.substr(4, statement.size());
	
	//find the "=" charachter.
	int equal = find_in_str(level2, '=');
	
	//find the semicolon which is the end of the statement
	int end = find_in_str(level2, ';');
	
	//if we don't have an "=" charachter, we should just add the variable
	if (equal < 0)
	{
		//add the variable to our var_table. all variables are global regardless of our position
		this->variable_table.add_var(remove_whitespaces(level2.substr(0,level2.size()-1)));
	}
	//if we are going to set the value as well.
	else
	{
		//from the beginning to equal is the name of our variable. we should remove the whitespaces though
		std::string name = remove_whitespaces(level2.substr(0,equal));
		
		//add the variable
		this->variable_table.add_var(name);
		
		//change its value
		this->variable_table.change_var(name, do_arit(level2.substr(equal+1,end-equal-1)));
	}
}

//print statement.
//////////////////////////////////////////////////////////
//                                                      //
// TODO: find a faster way to do the printing (printf?) //
//                                                      //
//////////////////////////////////////////////////////////
void Interpreter::print_statement(std::string statement)
{
	//remove the "print" itself
	std::string level2 = statement.substr(6, statement.size());
	
	//find the semicolon and thus the end of the statement
	int end = find_in_str(level2, ';');
	
	//find what we are going to print. as we should be able to do something like
	//"print (s+5)/2&&m", we should use "do_arit" on the remaining phrase
	InternalVariable output = do_arit(level2.substr(0,end));
	
	//now we should print the "result" depending on the type of the variable
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

//"get" statement
//input: a valid "get" statement. "get variable_name;"
void Interpreter::get_statement(std::string statement)
{
	//remove the "get" itself
	std::string level2 = statement.substr(4, statement.size());
	
	//find the semicolon (the end of the statement)
	int end = find_in_str(level2, ';');
	
	//find the name. it is now more efficient to use get_next token as it only needs to check up to the first whitespace
	std::string name = get_next_token(level2.substr(0,end), " \t\n").str;
	
	//get the result
	//////////////////////////////////////////////
	//TODO: use a faster function other than cin//
	//////////////////////////////////////////////
	//TODO: handle string input better than this//
	//////////////////////////////////////////////
	char* input = new char[64];
	std::cin >> input;
	
	//change the value of variable
	this->variable_table.change_var(name, str_to_var(std::string(input)));
}

//if statement
void Interpreter::if_statement(std::string statement)
{
	//do we have an "else"?
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// VERY IMPORTANT                                                                                                               //
	// TODO: this is buggy. if we have a variable that has the string "else" somewhere in its name the whole thing will collapse    //
	// also, if we have two "if" block inside each other, the else for the one inside will cause major problems for the one outside //
	// VERY IMPORTANT                                                                                                               //
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int else_loc = find_in_str(statement, "else");
	if (else_loc == -1)
	{
		//no else, dive directly into the if itself
		//remove the "if"
		std::string level2 = statement.substr(2, statement.size());
		
		//begin and end are the brace {} boundries of the if block
		int begin = find_in_str(level2, '{');
		int end = find_last_of_in_str(level2, '}');
		
		//get a substring for the condition and use do_arit to find the result
		InternalVariable condition = do_arit(level2.substr(0,begin));
		
		//check for the condition. see InternalVariable.condition()
		if (condition.condition())
		{
			//if the condition was true, act as if the whole codes in the if block are a new program. give them to code_analyzer()
			this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
		}
	}
	else
	{
		//we have an else. we should first check the main if. so remove it.
		std::string level2 = statement.substr(2, else_loc - 2);
		
		//begin is again the first "{"
		int begin = find_in_str(level2, '{');
		
		//but the end if not the same as above.
		///////////////////////////////////////////////////////////////////////////////////////
		// VERY IMPORTANT                                                                    //
		// TODO:the result will be horrible if we have another {} block inside the other one //
		// instead, use the last "}" before the next "else" instead. "else" should be        //
		// debugged first                                                                    //
		// VERY IMPORTANT                                                                    //
		///////////////////////////////////////////////////////////////////////////////////////
		int end = find_in_str(level2.substr(begin, level2.size()), '}')+begin;
		
		//get a substring for the condition and use do_arit to find the result
		InternalVariable condition = do_arit(level2.substr(0,begin));
		
		//check for the condition. see InternalVariable.condition()
		if (condition.condition())
		{
			//if the condition was true, act as if the whole codes in the if block are a new program. give them to code_analyzer()
			this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
			
			//get out of the whole function.
			return;
		}
		else
		{
			//create a variable so that we are not going to call "size" function every time we need it
			int size = statement.size();
			
			//copy the whole string
			level2 = std::string(statement.data());
			
			//do this while we have an "else" statement
			while (else_loc != -1)
			{
				//remove the "else"
				level2 = level2.substr(else_loc + 4, size);
				
				//find the location of the next "else"
				int next_else = find_in_str(level2, "else");
				
				//find the start of our code block
				int begin = find_in_str(level2, '{');
				
				//a string to save the current block
				std::string current_block;
				
				//if we don't have another else,  current block is from the start to the end of the string
				if (next_else == -1)
				{
					current_block = level2.substr(0, size);
				}
				//if not, it is to the location of the next_else
				else
				{
					current_block = level2.substr(0, next_else);
				}
				
				//find the end of the block
				//////////////////////////////////////////////////////////////////////////////
				//                                                                          //
				// TODO: probably we can use find_last_of_in_str() to get the "}" this time //
				//                                                                          //
				//////////////////////////////////////////////////////////////////////////////
				int end = find_in_str(current_block.substr(begin, current_block.size()), '}')+begin;

				//defind the "condition" variable with the value of true as default
				InternalVariable condition = true;
				
				//if we have an "if" before "{", it means that this is an "else if". so, try to find it. 
				int if_loc = find_in_str(current_block.substr(0,begin) , "if");
				
				//else if
				if (if_loc != -1)
				{
					//check for the condition. see InternalVariable.condition()
					condition = do_arit(current_block.substr(2+if_loc,begin-2-if_loc));
				}
				
				//get a substring for the condition and use do_arit to find the result
				if (condition.condition())
				{
					//if the condition was true, act as if the whole codes in the if block are a new program. give them to code_analyzer()
					this->code_analyzer(current_block.substr(begin + 1, end - begin - 1), true);
					
					//get out of the whole function
					return;
				}
				
				//after all these, else_location should change
				else_loc = next_else;
			}
		}
	}
}

//while
void Interpreter::while_statement(std::string statement)
{
	//remove the "while" itself
	std::string level2 = statement.substr(5, statement.size());
	
	//find the beginning and the end of the block
	int begin = find_in_str(level2, '{');
	int end = find_last_of_in_str(level2, '}');
	
	//the condition is everything before "{" (begin) as we have removed the "while" itself
	std::string str_condition = level2.substr(0,begin);
	
	//use do_arit to find the result
	InternalVariable condition = do_arit(str_condition);
	
	//while condition is true, run the code insisde the block
	while (condition.condition())
	{
		//run the code
		this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
		
		//re-calculate the condition as it may have changed after running the code
		condition = do_arit(str_condition);
	}
}

//for
void Interpreter::for_statement(std::string statement)
{
	//remove the "for" itself
	std::string level2 = statement.substr(4, statement.size());
	
	//beggining and end of the block
	int begin = find_in_str(level2, '{');
	int end = find_last_of_in_str(level2, '}');
	
	//find the first semicolon
	int scl1 = find_in_str(level2, ';');
	
	//find the second semicolon
	int scl2 = find_in_str(level2.substr(scl1+1, level2.size()), ';')+scl1+1;
	
	//find the location of the parantheses
	int par1 = find_in_str(level2, '(');
	int par2 = find_in_str(level2.substr(par1+1, level2.size()), ')')+par1+1;
	
	//the statement that is to be done only once
	std::string str_one_time = level2.substr(par1+1,scl1);
	
	//the part that is going to serve as the condition
	std::string str_condition = level2.substr(scl1+1,scl2-scl1-1);
	
	//the statement that is going to be done each time we reach the end of the loop
	std::string str_always = level2.substr(scl2+1,par2-scl2-1).append(";");
	
	//run the statement that is to be done once
	statement_analyzer(str_one_time);
	
	//se do_arit to find the result for condition
	InternalVariable condition = do_arit(str_condition);
	
	//while condition is true...
	while (condition.condition())
	{
		//run the whole code insisde the block
		this->code_analyzer(level2.substr(begin + 1, end - begin - 1), true);
		
		//run the statement that is to be done each time we reach the end of the block
		statement_analyzer(str_always);
		
		//re-calculate the condition as it may have changed after running the codes
		condition = do_arit(str_condition);
	}
}

//analyzes a single statement and calls the proper function for it
void Interpreter::statement_analyzer(std::string statement)
{
	//if we have and statement at all
	if (remove_whitespaces(statement).size() > 0)
	{
		//remove the whitespeaces to the left so that the main keyword is now located in the start
		std::string level1 = remove_whitespaces(statement, true);
		
		//if it was "var"
		if (level1.find("var ") == 0)
		{
			var_statement(level1);
		}
		//if it was print
		//we should be able to handle print("salam"); too. so the next characte is not necessarily a space
		/////////////////////////////////////////////////
		//TODO: do this for all of the other statements//
		/////////////////////////////////////////////////
		else if (level1.find("print") == 0 && is_in_string(level1[5], "\t\n ("))
		{
			print_statement(level1);
		}
		//if it was get
		else if (level1.find("get ") == 0)
		{
			get_statement(level1);
		}
		//if it was if
		else if (level1.find("if") == 0 && is_in_string(level1[2], "\t\n ("))
		{
			if_statement(level1);
		}
		//if it was while
		else if (level1.find("while") == 0 && is_in_string(level1[5], "\t\n ("))
		{
			while_statement(level1);
		}
		//if it was for
		else if (level1.find("for") == 0 && is_in_string(level1[3], "\t\n ("))
		{
			for_statement(level1);
		}
		//if it was pause
		else if (level1.find("pause") == 0)
		{
			//as it is just one line of code, there is no need to create a separate function 
			system("PAUSE");
		}
		
		//change the global:"g_previous_statement". we need it for other functions
		g_previous_statement = statement;
	}
}

//returns if the position is outside a pair of bracers and that if it is either the "}" or ";"
//sample
//base: "asf{ad;g}fa ;"
//is_outside_cr(base, 2):0
//is_outside_cr(base, 6):0
//is_outside_cr(base, 8):1
//is_outside_cr(base, 12):1
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

//gets the next statement. similar to get_next_token but with the difference
//that it tries to find the statement up to the end of it. if it is a bracer blocked
//statement, it gets to the end of the bracers, not the next semicolon. this is here
//as we can't simply use "find_in_str" for both ";" and "}". as we don't want to get
//something like: "while (a > 5){a = a + 1;", but the whole while statement, for the example bellow:
//samples:
//base = "var a;while (a > 5){a = a + 1; print a;}print a;"
//get_next_statement(base,0) = Token {str = "var a;", pos = 0}
//get_next_statement(base,6) = Token {str = "while (a > 5){a = a + 1; print a;}", pos = 6}
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

//we should check if the source code has "\n" in its strings and replace it with proper charachters
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

//returns if the current statement is an if
bool is_if(std::string statement)
{
     std::string level1 = remove_whitespaces(statement, true);
     if (level1.find("if") == 0 && is_in_string(level1[2], "\t\n ("))
     {
        return true;                      
     }
     return false;
}

//returns if the current statement is an else
bool is_else(std::string statement)
{
     std::string level1 = remove_whitespaces(statement, true);
     if (level1.find("else") == 0 && is_in_string(level1[4], "\t\n ("))
     {
        return true;                      
     }
     return false;
}

//returns if the current statement is a for
bool is_for(std::string statement)
{
     std::string level1 = remove_whitespaces(statement, true);
     if (level1.find("for") == 0 && is_in_string(level1[3], "\t\n ("))
     {
        return true;                      
     }
     return false;
}

//main function of the interpreter. gets the code, and runs it statement by statement
void Interpreter::code_analyzer(std::string code, bool checked)
{
	//define a helper variable for when we remove extra backslashes
	std::string refined_code;
	
	//if "checked" is true (which is the case when we are calling this function from if-for-while statements)
	//do not attempt to call check_for_backslashes() so as not to do unnecessary checks
	//if not, remove the extra backslashes
	if (checked)
		refined_code = code;
	else
		refined_code = check_for_backslashes(code);
		
	//define this so that we won't need to call the "size" function every time we need it
	unsigned long long size = refined_code.size();
	
	//create a temporary Token and initialize it
	Token temp;
	temp.str = std::string("");
	temp.pos = 0;
	
	//do this while we have not reached the end of the code
	while (temp.pos + temp.str.size() < size)
	{
		//get the next statement. either it is a simple one like "var s;" or it is a 
		//bracer blocked one like "while(true){print "infinite loop :D";++i;}"
		temp = get_next_statement(refined_code, temp.pos + temp.str.size());
		
		//if the statement is an "if", we should check if it has "else" keywords and add it to the statement
		if (is_if(temp.str))
		{
			//again get the next statement.
            Token temp2 = get_next_statement(refined_code, temp.pos + temp.str.size());
			
			//have a copy of main temp
            std::string temp3(temp.str);
			
			//if the new statement is an else...
            if (is_else(temp2.str))
            {
				//do this while we have an "else" statment...
                while (is_else(temp2.str))
                {
					//add the "else" statement to the end of the temp3.
                    temp3.append(temp2.str);
					
					//get the next statement
                    temp2 = get_next_statement(refined_code, temp2.pos + temp2.str.size());
                }
				
				//now that we are sure we have no "else" left, analyze the whole statement
                statement_analyzer(temp3);
				
				//and temp should become exactly like temp2
                temp = temp2;
            }
			
			/////////////////////////////////////////////////////////////////////////
			//VERY IMPORTANT                                                       //
			//TODO: i think this is an extra analyzement. check if we can remove it//
			//VERY IMPORTANT                                                       //
			/////////////////////////////////////////////////////////////////////////
            statement_analyzer(temp.str);
        }
		//it was not an "if"
        else
        {
			//if it is a for
			if (is_for(temp.str))
			{
				//as get_next_statement cannot determine if the phrases separated by semicolons in "for"
				//are related to it, we should handle this manually
				
				//currently, temp only contains up to the end of the "do_once" statement.
				
				//get the next statement (for_condition)
				Token temp2 = get_next_statement(refined_code, temp.pos + temp.str.size());
				
				//add it to the end of the code
				temp.str.append(temp2.str);
				
				//get the next statement (the rest of the for statement)
				temp2 = get_next_statement(refined_code, temp2.pos + temp2.str.size());
				
				//add it to the code
				temp.str.append(temp2.str);
				
				//we can analyze the statement properly now
				statement_analyzer(temp.str);
			}
			else
			{
				//if it was not either a for, or an if, we don't need to do anything special but to send it directly to statement analyzer
				statement_analyzer(temp.str);
			}
        }
	}
}
