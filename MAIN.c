#include"Definition.h"
#include"CNF_Reader.h"
#include"Solver.h"
#include"Stack.h"
//extern int count_value, count_clause;
int main()
{

	ReadCNF(GetLine_Exclude_C());
	DPLL();
	return 0;
}
/*
c qw q
c wawa
p cnf 4 2
1 1 2 3 0
2 2 4 4 0

3 0
-3 2 -1 0
*/