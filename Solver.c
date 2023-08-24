#include"Definition.h"
#include"Solver.h"
#include"Stack.h"
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
		struct ClauseHeadNode* removedClauseHead = &clausesHead[this_value->index_clause];
		struct ValueNode* removedValue = clausesHead[this_value->index_clause].nextValue_in_clause;
		if (is_true_here)//删除句子头及其所有节点
		{
			//删除所有节点
			while (removedValue)
			{
				removedClauseHead->nextValue_in_clause = removedClauseHead->nextValue_in_clause->nextValue_in_clause;
				if(removedClauseHead->nextValue_in_clause)
					removedClauseHead->nextValue_in_clause->preValue_in_clause = NULL;
				f_stack_RemovedValue = MyPush(f_stack_RemovedValue, *removedValue);
				removedValue = removedValue->nextValue_in_clause;
			}
			//删除句子头
			if (removedClauseHead->preClauseHead)
			{
				removedClauseHead->preClauseHead->nextClauseHead = removedClauseHead->nextClauseHead;
			}
			if (removedClauseHead->nextClauseHead)
			{
				removedClauseHead->nextClauseHead->preClauseHead = removedClauseHead->preClauseHead;
			}
			f_stack_RemovedClauseHead = MyPush_2(f_stack_RemovedClauseHead, *removedClauseHead);
		}
		else//删除句子中这个节点（横向指针）
		{
			if (this_value->preValue_in_clause)
			{
				this_value->preValue_in_clause->nextValue_in_clause = this_value->nextValue_in_clause;
			}
			if (this_value->nextValue_in_clause)
			{
				this_value->nextValue_in_clause->preValue_in_clause = this_value->preValue_in_clause;
			}
			f_stack_RemovedValue = MyPush(f_stack_RemovedValue, *this_value);
		}
		this_value = this_value->nextValue_in_value;
	}
	//竖向
	//删除这个变量头
	struct ValueHeadNode* removedValueHead = &valuesHead[*f_index_value];
	if (removedValueHead->preValueHead)
	{
		removedValueHead->preValueHead->nextValueHead = removedValueHead->nextValueHead;
	}
	if (removedValueHead->nextValueHead)
	{
		removedValueHead->nextValueHead->preValueHead = removedValueHead->preValueHead;
	}
	f_stack_RemovedValueHead = MyPush_3(f_stack_RemovedValueHead, *removedValueHead);
	
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
	struct Stack_Value* stack_RemovedValue = NULL/*(struct Stack_Value*)malloc(sizeof(struct Stack_Value))*/;
	struct Stack_ClauseHead* stack_RemovedClauseHead = NULL/*(struct Stack_ClauseHead*)malloc(sizeof(struct Stack_ClauseHead))*/;
	struct Stack_ValueHead* stack_RemovedValueHead = NULL/*(struct Stack_ValueHead*)malloc(sizeof(struct Stack_ValueHead))*/;
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