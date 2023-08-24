#include"Definition.h"
#include"Solver.h"
//extern int count_value, count_clause;
bool XOR(bool A, bool B)
{
	if (A && B || !A && !B)
		return false;
	return true;
}
void/* struct ClauseHeadNode* */ GetSingleValue_in_clause(int * f_index_value , bool** f_isTrue)
{
	struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
	if (!this_clauseHead)
	{
		*f_isTrue = NULL;
		return;
	}
	while (this_clauseHead)
	{
		if (!this_clauseHead->nextValue_in_clause)
		{
			this_clauseHead = this_clauseHead->nextClauseHead;
			continue;
		}
		if (this_clauseHead->nextValue_in_clause == this_clauseHead->latestValue_in_clause)		//找到只有一个变量的句子
		{
			*f_index_value = this_clauseHead->latestValue_in_clause->m_value;
			if (this_clauseHead->latestValue_in_clause->isNegative)
			{
				**f_isTrue = false;
			}
			else
			{
				**f_isTrue = true;
			}
			return;
		}
		this_clauseHead = this_clauseHead->nextClauseHead;
	}
	*f_isTrue = NULL;
	return;
}
void /* struct ValueHeadNode* */ GetSingleValue_in_value(int* f_index_value, bool** f_isTrue)
{
	struct ValueHeadNode* this_ValueHead = valuesHeadHead.nextValueHead;
	if (!this_ValueHead)
	{
		*f_isTrue = NULL;
		return;
	}
	while (this_ValueHead)
	{
		if (!this_ValueHead->nextValue_in_value)
		{
			this_ValueHead = this_ValueHead->nextValueHead;
			continue;
		}
		if (this_ValueHead->nextValue_in_value == this_ValueHead->latestValue_in_value)		//找到只出现过一次的变量
		{
			*f_index_value = this_ValueHead->latestValue_in_value->m_value;
			if (this_ValueHead->latestValue_in_value->isNegative)
			{
				**f_isTrue = false;
			}
			else
			{
				**f_isTrue = true;
			}
			return;
		}
		this_ValueHead = this_ValueHead->nextValueHead;
	}
	*f_isTrue = NULL;
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
	struct Stack_ValueHead* f_stack_RemovedValueHead
)
{
	if (!f_index_value)
	{
		return;
	}
	struct ValueNode* this_value = valuesHead[*f_index_value].nextValue_in_value;
	valuesHead[*f_index_value].m_truth = (f_isTrue ? 1 : -1);
	//横向
	while (this_value)
	{
		bool is_true_here = XOR(this_value->isNegative, *f_isTrue);
		if (is_true_here)
		{
			//删除句子头及其所有节点
		}
		else
		{
			//删除句子中这个节点（横向指针）
		}
		this_value = this_value->nextValue_in_value;
	}
	//竖向
	struct ValueHeadNode* this_valueHead = &valuesHead[*f_index_value];
	//删除这个变量头
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
	struct Stack_ValueHead* f_stack_RemovedValueHead
)
{
	//TODO_1
}
bool DPLL()
{
	struct Stack_Value* stack_RemovedValue = (struct Stack_Value*)malloc(sizeof(struct Stack_Value));
	struct Stack_ClauseHead* stack_RemovedClauseHead = (struct Stack_ClauseHead*)malloc(sizeof(struct Stack_ClauseHead));
	struct Stack_ValueHead* stack_RemovedValueHead = (struct Stack_ValueHead*)malloc(sizeof(struct Stack_ValueHead));
	int* index_value_p = (int*)malloc(sizeof(int));
	bool* isTrue = (bool*)malloc(sizeof(bool));
	while (1)
	{
		GetSingleValue_in_clause(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, stack_RemovedValue , stack_RemovedClauseHead, stack_RemovedValueHead);
	}
	if(!isTrue)
		isTrue = (bool*)malloc(sizeof(bool));
	while (1)
	{
		GetSingleValue_in_value(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, stack_RemovedValue ,stack_RemovedClauseHead, stack_RemovedValueHead);
	}
	if (!isTrue)
		isTrue = (bool*)malloc(sizeof(bool));

	if (CheckEmptyCNF())//没有句子
	{
		RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_RemovedValueHead);
		return true;
	}
		
	if (CheckEmptyClause())//有空句子
	{
		RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_RemovedValueHead);
		return false;
	}
		

	bool state = false;
	ChooseValue(index_value_p);
	if (isTrue)
		*isTrue = true;
	SetValue(index_value_p, isTrue, stack_RemovedValue, stack_RemovedClauseHead, stack_RemovedValueHead);
	state = DPLL();
	if (state)
	{
		RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_RemovedValueHead);
		return state;
	}
	if (isTrue)
		*isTrue = false;
	SetValue(index_value_p, isTrue, stack_RemovedValue, stack_RemovedClauseHead, stack_RemovedValueHead);
	state = DPLL();
	RevertChange(stack_RemovedValue, stack_RemovedClauseHead, stack_RemovedValueHead);
	return state;
}