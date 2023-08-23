#include"Definition.h"


int main()
{
	int* p = malloc(sizeof(int));
	if (!p)printf("null");
	ReadCNF(GetLine_Exclude_C());
	DPLL();
	return 0;
}
/*
c qw q
c wawa
p cnf 20 0
1 -2 3 0
-3 2 -1 0
*/