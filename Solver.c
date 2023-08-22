#include"Definition.h"
void/* struct ClauseHeadNode* */ GetSingleValue_in_clause(int * f_index_value , bool* f_isTrue)
{
	//TODO 1
}
void /* struct ValueHeadNode* */ GetSingleValue_in_value(int* f_index_value, bool* f_isTrue)
{
	//TODO 1
}
void ChooseValue(int* f_index_value)
{
	*f_index_value = valuesHeadHead.nextValueHead->m_value;
}
void SetValue(int* f_index_value, bool* f_isTrue , struct Stack_Value* f_stack_RemovedValue)
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
void RevertChange(struct Stack_Value* f_stack_RemovedValue)
{
	//TODO 1
}
bool DPLL()
{
	struct Stack_Value* stack_RemovedValue = malloc(sizeof(struct Stack_Value));
	int* index_value_p = malloc(sizeof(int));
	bool* isTrue = malloc(sizeof(bool));
	while (1)
	{
		GetSingleValue_in_clause(index_value_p, isTrue);
		if (!isTrue)break;
		SetValue(index_value_p, isTrue, stack_RemovedValue);
	}
	if(!isTrue)
		isTrue = malloc(sizeof(bool));
	while (1)
	{
		GetSingleValue_in_value(index_value_p, isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, stack_RemovedValue);
	}
	if (!isTrue)
		isTrue = malloc(sizeof(bool));

	if (CheckEmptyCNF())
	{
		RevertChange(stack_RemovedValue);
		return true;
	}
		
	if (CheckEmptyClause())
	{
		RevertChange(stack_RemovedValue);
		return false;
	}
		

	bool state = false;
	ChooseValue(index_value_p);
	*isTrue = true;
	SetValue(index_value_p, isTrue, stack_RemovedValue);
	state = DPLL();
	if (state)
	{
		RevertChange(stack_RemovedValue);
		return state;
	}
	*isTrue = false;
	SetValue(index_value_p, isTrue, stack_RemovedValue);
	state = DPLL();
	RevertChange(stack_RemovedValue);
	return state;
}