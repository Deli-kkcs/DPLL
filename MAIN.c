#include"Definition.h"
#include"CNF_Reader.h"
#include"Solver.h"
#include"Stack.h"
//extern int count_value, count_clause;
int main()
{
	bool isCheckValue = false;
	//bool isCheckValue = true;

	clock_t start, end;
	ReadCNF(GetLine_Exclude_C());
	
	start = clock();
	
	if (isCheckValue)
	{
		ReadValue();
		CheckValue();
	}
	else
	{
		count_solution = 0;
		DPLL();
		if (count_solution == 0)
			printf("��ɱ�����!\n");
	}
	end = clock();
	printf("time=%f\n", (double)(end - start) / CLK_TCK);
	return 0;
}
/*
c qw q
c wawa
p cnf 4 6
1 2 3 0
-1 -2 0
-1 -3 0
-2 -3 0
1 2 0
1 3 0
1 -1 -1 1
2 3 0

1 -2 -3 0
-1 2 -3 0
3 4 0
-4 0
0

*/
/*


*/