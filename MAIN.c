#include"Definition.h"
#include"CNF_Reader.h"
#include"Solver.h"
#include"Stack.h"
//extern int count_value, count_clause;
int main()
{
	ReadCNF(GetLine_Exclude_C());
	count_solution = 0;
	DPLL();
	if (count_solution == 0)
		printf("¾øÉ±£¬Îâ½ã!\n");
	return 0;
}
/*
c qw q
c wawa
p cnf 5 4
1 2 0
-1 -2 0
1 -2 0
-1 2 0

*/
/*


*/