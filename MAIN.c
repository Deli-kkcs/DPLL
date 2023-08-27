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
p cnf 10 6
1 2 3 0
-1 -2 0
-1 -3 0
-2 -3 0
1 2 0
1 3 0
2 3 0

1 -2 -3 0
-1 2 -3 0
3 4 0
-4 0
0

*/
/*


*/