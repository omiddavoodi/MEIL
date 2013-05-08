#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#ifndef _VECTOR_H_
#include <vector>
#endif

#ifndef _STRING_H_
#include <string>
#endif

#ifndef _VARTABLE_H_
#define _VARTABLE_H_ 0

class VarTable
{
	private:
		long long var_count;
		std::vector<InternalVariable> var_table;
		std::vector<std::string> var_name_table;
	public:
		VarTable::VarTable(){var_count = 0;};
		void add_var(std::string name);
		InternalVariable get_var(std::string name);
		void change_var(std::string name, InternalVariable val);
		void add_to_var(std::string name, int val);
};

#endif