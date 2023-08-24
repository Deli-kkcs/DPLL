#include"Definition.h"
extern int count_value, count_clause;
void F1()
{
	printf("F1");
}
void F1(int i)
{
	printf("F2");
}
int main()
{
	F1(1);
	ReadCNF(GetLine_Exclude_C());
	DPLL();
	return 0;
}
/*
c qw q
c wawa
p cnf 3 1
1 1 2 2 3 0
3 0
-3 2 -1 0
*/