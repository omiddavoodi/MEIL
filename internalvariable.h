#ifndef _STRING_H_
#include <string>
#endif

#ifndef _INTERNALVARIABLE_H
#define _INTERNALVARIABLE_H 0

enum VariableType
{
	Boolean,
	Integer,
	Float,
	String
};

class InternalVariable {

	private :
		bool bool_value;
		long long int_value;
		long double float_value;
		std::string string_value;
		VariableType value_type;

	public :

		//constructors
		InternalVariable(){}
		InternalVariable(bool);
		InternalVariable(long long);
		InternalVariable(long double);
		InternalVariable(std::string);
		InternalVariable(char*);

		//get methods
		bool get_bool_value();
		long long get_int_value();
		long double get_float_value();
		std::string  get_string_value();
		VariableType get_type();

		//set methods
		void set_bool_value(bool);
		void set_int_value(long long);
		void set_float_value(long double);
		void set_string_value(std::string);
		void set_string_value(char*);
		void set_type(VariableType);

		//others
		void deep_copy(InternalVariable);
		bool positive();
		InternalVariable not();

		InternalVariable& operator=(long long);
		InternalVariable& operator=(long double);
		InternalVariable& operator=(bool);
		InternalVariable& operator=(std::string);
		InternalVariable& operator=(char*);
		InternalVariable& operator=(InternalVariable);
		InternalVariable operator+(bool);
		InternalVariable operator+(long long);
		InternalVariable operator+(long double);
		InternalVariable operator+(std::string);
		InternalVariable operator+(char*);
		InternalVariable operator+(InternalVariable);
		InternalVariable operator-(bool);
		InternalVariable operator-(long long);
		InternalVariable operator-(long double);
		InternalVariable operator-(InternalVariable);
		InternalVariable operator*(bool);
		InternalVariable operator*(long long);
		InternalVariable operator*(long double);
		InternalVariable operator*(InternalVariable);
		InternalVariable operator/(bool);
		InternalVariable operator/(long long);
		InternalVariable operator/(long double);
		InternalVariable operator/(InternalVariable);
		InternalVariable operator%(long long);
		InternalVariable operator%(InternalVariable);
		InternalVariable operator>(InternalVariable);
		InternalVariable operator<(InternalVariable);
		InternalVariable operator==(InternalVariable);
		InternalVariable operator<=(InternalVariable);
		InternalVariable operator>=(InternalVariable);
		InternalVariable operator&&(InternalVariable);
		InternalVariable operator||(InternalVariable);
};

InternalVariable str_to_var(std::string);
std::string var_to_str(InternalVariable);

#endif
