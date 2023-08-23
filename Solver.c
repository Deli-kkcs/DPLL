#include"Definition.h"
void/* struct ClauseHeadNode* */ GetSingleValue_in_clause(int * f_index_value , bool** f_isTrue)
{
	if (!clausesHeadHead.nextClauseHead)
	{
		*f_isTrue = NULL;
		return;
	}
	struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
	while (this_clauseHead)
	{
		if (this_clauseHead->nextValue_in_clause == this_clauseHead->latestValue_in_clause)		//找到只有一个变量的句子
		{
			*f_index_value = this_clauseHead->latestValue_in_clause->m_value;
			return;
		}
		this_clauseHead = this_clauseHead->nextClauseHead;
	}
	f_isTrue = NULL;
	return;
}
void /* struct ValueHeadNode* */ GetSingleValue_in_value(int* f_index_value, bool* f_isTrue)
{
	if (!valuesHeadHead.nextValueHead)
	{
		f_isTrue = NULL;
		return;
	}
	struct ValueHeadNode* this_ValueHead = valuesHeadHead.nextValueHead;
	while (this_ValueHead)
	{
		if (this_ValueHead->nextValue_in_value == this_ValueHead->latestValue_in_value)		//找到只出现过一次的变量
		{
			*f_index_value = this_ValueHead->latestValue_in_value->m_value;
			return;
		}
		this_ValueHead = this_ValueHead->nextValueHead;
	}
	f_isTrue = NULL;
	return;
}
void ChooseValue(int* f_index_value)
{
	*f_index_value = valuesHeadHead.nextValueHead->m_value;
	//TODO_2
}
void SetValue
(
	int* f_index_value,
	bool* f_isTrue,
	struct Stack_Value* f_stack_RemovedValue,
	struct Stack_ClauseHead* f_stack_RemovedClauseHead,
	struct Stack_ValueHasBeenSet* f_stack_SetValue
)
{
	if (!f_index_value)
	{
		return;
	}
	//TODO_1
}
bool CheckEmptyCNF()
{
	if (!clausesHeadHead.nextClauseHead)
	{
		return false;
	}
	return true;
}
bool CheckEmptyClause()
{
	struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
	while (this_clauseHead)
	{
		//找到没有变量的句子
		if (!this_clauseHead->nextValue_in_clause)							
		{
			return true;
		}
		this_clauseHead = this_clauseHead->nextClauseHead;
	}
	return false;
}
void RevertChange
(
	struct Stack_Value* f_stack_RemovedValue, 
	struct Stack_ClauseHead* f_stack_RemovedClauseHead, 
	struct Stack_ValueHasBeenSet* f_stack_SetValue
)
{
	//TODO_1
}
bool DPLL()
{
	struct Stack_Value* stack_RemovedValue = malloc(sizeof(struct Stack_Value));
	struct Stack_ClauseHead* stack_RemovedClauseHead = malloc(sizeof(struct Stack_ClauseHead));
	struct Stack_ValueHasBeenSet* stack_SetValue = malloc(sizeof(struct Stack_ValueHasBeenSet));
	int* index_value_p = malloc(sizeof(int));
	bool* isTrue = (bool*)malloc(sizeof(bool));
	while (1)
	{
		GetSingleValue_in_clause(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, stack_RemovedValue , stack_RemovedClauseHead, stack_SetValue);
	}
	if(!isTrue)
		isTrue = malloc(sizeof(bool));
	while (1)
	{
		GetSingleValue_in_value(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, stack_RemovedValue ,stack_RemovedClauseHead, stack_SetValue);
	}
	if (!isTrue)
		isTrue = malloc(sizeof(bool));

	if (CheckEmptyCNF())//没有句子
	{
		RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_SetValue);
		return true;
	}
		
	if (CheckEmptyClause())//有空句子
	{
		RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_SetValue);
		return false;
	}
		

	bool state = false;
	ChooseValue(index_value_p);
	*isTrue = true;
	SetValue(index_value_p, isTrue, stack_RemovedValue, stack_RemovedClauseHead, stack_SetValue);
	state = DPLL();
	if (state)
	{
		RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_SetValue);
		return state;
	}
	*isTrue = false;
	SetValue(index_value_p, isTrue, stack_RemovedValue, stack_RemovedClauseHead, stack_SetValue);
	state = DPLL();
	RevertChange(stack_RemovedValue, stack_RemovedClauseHead,stack_SetValue);
	return state;
}