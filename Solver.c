#include"Definition.h"
void/* struct ClauseHeadNode* */ GetSingleValue_in_clause(int * f_index_value , bool* f_isTrue)
{
	//TODO 1
}
void /* struct ValueHeadNode* */ GetSingleValue_in_value(int* f_index_value, bool* f_isTrue)
{
	//TODO 1
}
int ChooseValue()
{
	//TODO 2
	return valuesHeadHead.nextValueHead->m_value;
}
void SetValue(int* f_index_value, bool* f_isTrue)
{
	if (!f_index_value)
	{
		return;
	}
	//TODO 1
}
bool CheckEmptyCNF()
{
	//TODO 1
	return false;
}
bool CheckEmptyClause()
{
	//TODO 1
	return true;
}
bool DPLL()
{
	int* index_value_p = malloc(sizeof(int));
	bool* isTrue = malloc(sizeof(bool));

	GetSingleValue_in_clause(index_value_p,isTrue);
	SetValue(index_value_p, isTrue);

	GetSingleValue_in_value(index_value_p, isTrue);
	SetValue(index_value_p, isTrue);

	if (CheckEmptyCNF())
		return true;
	if (CheckEmptyClause())
		return false;

	bool state = false;
	int index_value = 0;
	index_value = ChooseValue();

	SetValue(index_value, true);
	state = DPLL();
	if (state)
		return state;

	SetValue(index_value, false);
	state = DPLL();
	return state;
}