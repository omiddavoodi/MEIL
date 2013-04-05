#include "interpreter.h"
int main()
{
	Interpreter inter;
	inter.statement_analyzer ("var s=4;");
	inter.statement_analyzer ("var g=5-2*s;");
	inter.statement_analyzer ("print g;");
	inter.statement_analyzer ("print \"\n\";");
	inter.statement_analyzer ("pause;");
}