//get methods
#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#ifndef _STRING_H_
#include <string>
#endif

#ifndef _IOSTREAM_H_
#include <iostream>
#endif

#include <sstream>

InternalVariable::InternalVariable(bool value)
{
	this->value_type = Boolean;
	this->bool_value = value;
}

InternalVariable::InternalVariable(long long value)
{
	this->value_type = Integer;
	this->int_value = value;
}

InternalVariable::InternalVariable(long double value)
{
	this->value_type = Float;
	this->float_value = value;
}

InternalVariable::InternalVariable(std::string value)
{
	this->value_type = String;
	this->string_value = value;
}

InternalVariable::InternalVariable(char* value)
{
	this->value_type = String;
	this->string_value = std::string(value);
}

bool InternalVariable::get_bool_value()
{
	return this->bool_value;
}

long long InternalVariable::get_int_value()
{
	return this->int_value;
}

long double InternalVariable::get_float_value()
{
	return this->float_value;
}

std::string InternalVariable::get_string_value()
{
	return this->string_value;
}

VariableType InternalVariable::get_type()
{
	return this->value_type;
}

void InternalVariable::set_bool_value(bool value)
{
	this->bool_value = value;
}

void InternalVariable::set_int_value(long long value)
{
	this->int_value = value;
}

void InternalVariable::set_float_value(long double value)
{
	this->float_value = value;
}

void InternalVariable::set_string_value(std::string value)
{
	this->string_value = value;
}

void InternalVariable::set_string_value(char* value)
{
	this->string_value = std::string(value);
}

void InternalVariable::set_type(VariableType value)
{
	this->value_type = value;
}

InternalVariable& InternalVariable::operator=(long long value)
{
	this->value_type = Integer;
	this->int_value = value;
	return *this;
}

InternalVariable& InternalVariable::operator=(long double value)
{
	this->value_type = Float;
	this->float_value = value;
	return *this;
}

InternalVariable& InternalVariable::operator=(bool value)
{
	this->value_type = Boolean;
	this->bool_value = value;
	return *this;
}

InternalVariable& InternalVariable::operator=(std::string value)
{
	this->value_type = String;
	this->string_value = value;
	return *this;
}

InternalVariable& InternalVariable::operator=(char* value)
{
	this->value_type = String;
	this->string_value = std::string(value);
	return *this;
}

InternalVariable& InternalVariable::operator=(InternalVariable other)
{
	this->value_type = other.get_type();
	switch (this->value_type)
	{
		case Boolean:
			this->bool_value = other.get_bool_value();
			return *this;

		case Integer:
			this->int_value = other.get_int_value();
			return *this;

		case Float:
			this->float_value = other.get_float_value();
			return *this;

		case String:
			this->string_value = other.get_string_value();
			return *this;
	}
	return (*this); 
}

InternalVariable InternalVariable::operator+(bool value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value + value));

		case Integer:
			return InternalVariable(this->int_value + (long long)(value));

		case Float:
			return InternalVariable(this->float_value + (long double)(value));

		case String:
			std::ostringstream temp;
			temp << this->string_value.data() << value;
			std::string temp2(temp.str());
			return InternalVariable(temp2);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator+(long long value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value) + value);

		case Integer:
			return InternalVariable(this->int_value + value);

		case Float:
			return InternalVariable(this->float_value + (long double)(value));

		case String:
			std::ostringstream temp;
			temp << this->string_value.data() << value;
			std::string temp2(temp.str());
			return InternalVariable(temp2);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator+(long double value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long double)(this->bool_value) + value);

		case Integer:
			return InternalVariable((long double)(this->int_value) + value);

		case Float:
			return InternalVariable(this->float_value + value);

		case String:
			std::ostringstream temp;
			temp << this->string_value.data() << value;
			std::string temp2(temp.str());
			return InternalVariable(temp2);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator+(std::string value)
{
	std::ostringstream temp;
	std::string temp2;
	switch (this->value_type)
	{
		case Boolean:
			temp.clear();
			temp << this->bool_value << value;
			temp2 = std::string(temp.str());
			return InternalVariable(temp2);

		case Integer:
			temp.clear();
			temp << this->int_value << value;
			temp2 = std::string(temp.str());
			return InternalVariable(temp2);

		case Float:
			temp.clear();
			temp << this->float_value << value;
			temp2 = std::string(temp.str());
			return InternalVariable(temp2);

		case String:
			temp2 = std::string(this->string_value.data()).append(value);
			return InternalVariable(temp2);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator+(char* value)
{
	std::ostringstream temp;
	std::string temp2;
	switch (this->value_type)
	{
		case Boolean:
			temp.clear();
			temp << this->bool_value << value;
			temp2 = std::string(temp.str());
			return InternalVariable(temp2);

		case Integer:
			temp.clear();
			temp << this->int_value << value;
			temp2 = std::string(temp.str());
			return InternalVariable(temp2);

		case Float:
			temp.clear();
			temp << this->float_value << value;
			temp2 = std::string(temp.str());
			return InternalVariable(temp2);

		case String:
			temp2 = std::string(this->string_value.data()).append(std::string(value));
			return InternalVariable(temp2);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator+(InternalVariable other)
{
	switch (other.value_type)
	{
		case Boolean:
			return (*this) + other.get_bool_value(); 

		case Integer:
			return (*this) + other.get_int_value(); 

		case Float:
			return (*this) + other.get_float_value(); 

		case String:
			return (*this) + other.get_string_value(); 
	}
	return (*this); 
}

InternalVariable InternalVariable::operator-(bool value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value - value));

		case Integer:
			return InternalVariable(this->int_value - (long long)(value));

		case Float:
			return InternalVariable(this->float_value - (long double)(value));

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator-(long long value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value) - value);

		case Integer:
			return InternalVariable(this->int_value - value);

		case Float:
			return InternalVariable(this->float_value - (long double)(value));

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator-(long double value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long double)(this->bool_value) - value);

		case Integer:
			return InternalVariable((long double)(this->int_value) - value);

		case Float:
			return InternalVariable(this->float_value - value);

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator-(InternalVariable other)
{
	switch (other.value_type)
	{
		case Boolean:
			return (*this) - other.get_bool_value(); 

		case Integer:
			return (*this) - other.get_int_value(); 

		case Float:
			return (*this) - other.get_float_value(); 

		case String:
			return (*this); 
	}
	return (*this); 
}

InternalVariable InternalVariable::operator*(bool value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value * value));

		case Integer:
			return InternalVariable(this->int_value * (long long)(value));

		case Float:
			return InternalVariable(this->float_value * (long double)(value));

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator*(long long value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value) * value);

		case Integer:
			return InternalVariable(this->int_value * value);

		case Float:
			return InternalVariable(this->float_value * (long double)(value));

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator*(long double value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long double)(this->bool_value) * value);

		case Integer:
			return InternalVariable((long double)(this->int_value) * value);

		case Float:
			return InternalVariable(this->float_value * value);

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator*(InternalVariable other)
{
	switch (other.value_type)
	{
		case Boolean:
			return (*this) * other.get_bool_value(); 

		case Integer:
			return (*this) * other.get_int_value(); 

		case Float:
			return (*this) * other.get_float_value(); 

		case String:
			return (*this); 
	}
	return (*this); 
}

InternalVariable InternalVariable::operator/(bool value)
{
	switch (this->value_type)
	{
		case Boolean:
			return (*this);

		case Integer:
			return InternalVariable(this->int_value / (long long)(value));

		case Float:
			return InternalVariable(this->float_value / (long double)(value));

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator/(long long value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value) / value);

		case Integer:
			return InternalVariable(this->int_value / value);

		case Float:
			return InternalVariable(this->float_value / (long double)(value));

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator/(long double value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long double)(this->bool_value) / value);

		case Integer:
			return InternalVariable((long double)(this->int_value) / value);

		case Float:
			return InternalVariable(this->float_value / value);

		case String:
			return (*this);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator/(InternalVariable other)
{
	switch (other.value_type)
	{
		case Boolean:
			return (*this) / other.get_bool_value(); 

		case Integer:
			return (*this) / other.get_int_value(); 

		case Float:
			return (*this) / other.get_float_value(); 

		case String:
			return (*this); 
	}
	return (*this); 
}

InternalVariable InternalVariable::operator%(long long value)
{
	switch (this->value_type)
	{
		case Boolean:
			return InternalVariable((long long)(this->bool_value) % value);

		case Integer:
			return InternalVariable(this->int_value % value);

		case Float:
			return InternalVariable(this->float_value);

		case String:
			return InternalVariable(this->string_value);
	}
	return (*this); 
}

InternalVariable InternalVariable::operator%(InternalVariable other)
{
	switch (other.value_type)
	{
		case Boolean:
			return (*this) / other.get_bool_value(); 

		case Integer:
			return (*this) / other.get_int_value(); 

		case Float:
			return (*this); 

		case String:
			return (*this); 
	}
	return (*this); 
}

long double double_pow(int a, int b)
{
	long double res = 1.0;
	if (b >= 0)
	{
		for (int i = 0; i < b - 1; ++i)
		{
			res *= a;
		}
	}
	else
	{
		for (int i = 0; i > b; --i)
		{
			res /= a;
		}
	}
	return res;
}

long long simple_pow (int a, int b)
{
	long long res = 1;
	for (int i = 0; i < b; ++i)
	{
		res *= a;
	}
	return res;
}

bool has_char(std::string str, char ch)
{
	int size = str.size();
	for (int i = 0; i < size; ++i)
	{
		if (str[i] == ch)
			return true;
	}
	return false;
}

InternalVariable str_to_var(std::string str)
{
	if (has_char(str,'"'))
	{
		return InternalVariable(str.substr(1,str.size()-2));
	}
	else
	{
		int size = str.size(), dot = str.find('.');
		if (dot >= 0)
		{
			long double res = 0.0;
			for (int i = 0; i < size; ++i)
			{
				if (str[i] == '1')
					res += (double_pow(10,(dot - i)));
				else if (str[i] == '2')
					res += (2.0 * double_pow(10,(dot - i)));
				else if (str[i] == '3')
					res += (3.0 * double_pow(10,(dot - i)));
				else if (str[i] == '4')
					res += (4.0 * double_pow(10,(dot - i)));
				else if (str[i] == '5')
					res += (5.0 * double_pow(10,(dot - i)));
				else if (str[i] == '6')
					res += (6.0 * double_pow(10,(dot - i)));
				else if (str[i] == '7')
					res += (7.0 * double_pow(10,(dot - i)));
				else if (str[i] == '8')
					res += (8.0 * double_pow(10,(dot - i)));
				else if (str[i] == '9')
					res += (9.0 * double_pow(10,(dot - i)));
			}
			return InternalVariable(res);
		}
		else
		{
			long long res = 0;
			for (int i = 0; i < size; ++i)
			{
				if (str[i] == '1')
					res += (simple_pow(10,(size - i - 1)));
				else if (str[i] == '2')
					res += (2 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '3')
					res += (3 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '4')
					res += (4 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '5')
					res += (5 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '6')
					res += (6 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '7')
					res += (7 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '8')
					res += (8 * simple_pow(10,(size - i - 1)));
				else if (str[i] == '9')
					res += (9 * simple_pow(10,(size - i - 1)));
			}
			return InternalVariable(res);
		}
	}
}