#ifndef _VARTABLE_H_
#include "vartable.h"
#endif

#ifndef _VECTOR_H_
#include <vector>
#endif

#ifndef _INTERNALVARIABLE_H_
#include "internalvariable.h"
#endif

#ifndef _STRING_H_
#include <string>
#endif

void VarTable::add_var(std::string name)
{
	for (unsigned int i = 0; i < this->var_name_table.size(); ++i)
	{
		if (this->var_name_table[i].compare(name) == 0)
		{
			return;
		}
	}
	++(this->var_count);
	this->var_name_table.push_back(name);
	this->var_table.push_back(InternalVariable((long long)0));
}

InternalVariable VarTable::get_var(std::string name)
{
	for (int i = 0; i < this->var_count; ++i)
	{
		if (this->var_name_table[i].compare(name) == 0)
		{
			return this->var_table[i];
		}
	}
	add_var(name);
	return this->get_var(name);
}

void VarTable::change_var(std::string name, InternalVariable val)
{
	for (int i = 0; i < this->var_count; ++i)
	{
		if (this->var_name_table[i].compare(name) == 0)
		{
			this->var_table[i] = val;
			return;
		}
	}
}