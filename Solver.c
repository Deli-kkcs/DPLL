#include"Definition.h"
#include"Solver.h"
#include"Stack.h"
//extern int count_value, count_clause;
bool XOR(bool A, int B)
{
	if (A && B == 1 || !A && B == -1)
		return false;
	return true;
}
void GetSingleValue_in_clause(int * f_index_value , int** f_isTrue)
{
	struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
	if (!this_clauseHead)
	{
		*f_isTrue = NULL;
		return;
	}
	while (this_clauseHead)
	{
		if (!this_clauseHead->nextValue_in_clause)//�пվ���
		{
			*f_isTrue = NULL;
			return;
			/*this_clauseHead = this_clauseHead->nextClauseHead;
			continue;*/
		}
		if (this_clauseHead->nextValue_in_clause == this_clauseHead->latestValue_in_clause)		//�ҵ�ֻ��һ�������ľ���
		{
			*f_index_value = this_clauseHead->latestValue_in_clause->m_value;
			if (this_clauseHead->latestValue_in_clause->isNegative)
			{
				**f_isTrue = -1;
			}
			else
			{
				**f_isTrue = 1;
			}
			return;
		}
		this_clauseHead = this_clauseHead->nextClauseHead;
	}
	*f_isTrue = NULL;
	return;
}
void GetSingleValue_in_value(int* f_index_value, int** f_isTrue)
{
	struct ValueHeadNode* this_ValueHead = valuesHeadHead.nextValueHead;
	if (!this_ValueHead)
	{
		*f_isTrue = NULL;
		return;
	}
	while (this_ValueHead)
	{
		if (!this_ValueHead->nextValue_in_value)//�б���û���ֹ�
		{
			*f_index_value = this_ValueHead->m_value;
			**f_isTrue = 0;
			return;
			/*this_ValueHead = this_ValueHead->nextValueHead;
			continue;*/
		}
		if (this_ValueHead->nextValue_in_value == this_ValueHead->latestValue_in_value)		//�ҵ�ֻ���ֹ�һ�εı���
		{
			*f_index_value = this_ValueHead->m_value;
			if (this_ValueHead->latestValue_in_value->isNegative)
			{
				**f_isTrue = -1;
			}
			else
			{
				**f_isTrue = 1;
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
void RemoveValue_in_clause(struct Stack_Value** f_stack_RemovedValue, struct ValueNode* removed_value)
{
	struct ClauseHeadNode* clauseHead_here = &clausesHead[removed_value->index_clause];
	if (clauseHead_here->latestValue_in_clause == removed_value)
		clauseHead_here->latestValue_in_clause = removed_value->preValue_in_clause;
	if (clauseHead_here->nextValue_in_clause == removed_value)
		clauseHead_here->nextValue_in_clause = clauseHead_here->nextValue_in_clause->nextValue_in_clause;
	if (removed_value->preValue_in_clause)
		removed_value->preValue_in_clause->nextValue_in_clause = removed_value->nextValue_in_clause;
	if (removed_value->nextValue_in_clause)
		removed_value->nextValue_in_clause->preValue_in_clause = removed_value->preValue_in_clause;
	//��ɾ������ͷ���
	/*removedClauseHead->nextValue_in_clause = removedClauseHead->nextValue_in_clause->nextValue_in_clause;
	if (removedClauseHead->nextValue_in_clause)
		removedClauseHead->nextValue_in_clause->preValue_in_clause = NULL;*/
	MyPush(f_stack_RemovedValue, removed_value);
	//return f_stack_RemovedValue;
}
void RemoveValue_in_value(struct Stack_ValueHead** f_stack_RemovedValueHead, struct ValueNode* removed_value)
{
	struct ValueHeadNode* may_removedValueHead = &valuesHead[removed_value->m_value];
	if (may_removedValueHead->latestValue_in_value == removed_value)
		may_removedValueHead->latestValue_in_value = removed_value->preValue_in_value;
	if (may_removedValueHead->nextValue_in_value == removed_value)
		may_removedValueHead->nextValue_in_value = may_removedValueHead->nextValue_in_value->nextValue_in_value;
;	if (removed_value->preValue_in_value)
		removed_value->preValue_in_value->nextValue_in_value = removed_value->nextValue_in_value;
	if (removed_value->nextValue_in_value)
		removed_value->nextValue_in_value->preValue_in_value = removed_value->preValue_in_value;
	//ɾ������ͷ���
	if (!may_removedValueHead->latestValue_in_value)//����������ڵ��Ǳ�����Ψһһ�γ���
	{
		if (may_removedValueHead->preValueHead)
			may_removedValueHead->preValueHead->nextValueHead = may_removedValueHead->nextValueHead;
		if (may_removedValueHead->nextValueHead)
			may_removedValueHead->nextValueHead->preValueHead = may_removedValueHead->preValueHead;
		MyPush_3(f_stack_RemovedValueHead, may_removedValueHead);
	}
}
void RemoveClauseHead(struct Stack_ClauseHead** f_stack_RemovedClauseHead, struct ClauseHeadNode* removed_clauseHead)
{
	if (removed_clauseHead->preClauseHead)
		removed_clauseHead->preClauseHead->nextClauseHead = removed_clauseHead->nextClauseHead;
	if (removed_clauseHead->nextClauseHead)
		removed_clauseHead->nextClauseHead->preClauseHead = removed_clauseHead->preClauseHead;
	MyPush_2(f_stack_RemovedClauseHead,removed_clauseHead);
}
void RemoveValueHead(struct Stack_ValueHead** f_stack_RemovedValueHead, struct ValueHeadNode* removed_valueHead)
{
	if (removed_valueHead->preValueHead)
	{
		removed_valueHead->preValueHead->nextValueHead = removed_valueHead->nextValueHead;
	}
	if (removed_valueHead->nextValueHead)
	{
		removed_valueHead->nextValueHead->preValueHead = removed_valueHead->preValueHead;
	}
	MyPush_3(f_stack_RemovedValueHead,removed_valueHead);
}
void SetValue
(
	int* f_index_value,
	int* f_isTrue,
	struct Stack_Value** f_stack_RemovedValue,
	struct Stack_ClauseHead** f_stack_RemovedClauseHead,
	struct Stack_ValueHead** f_stack_RemovedValueHead
)
{
	if (!f_index_value)
	{
		return;
	}
	struct ValueNode* this_value = valuesHead[*f_index_value].nextValue_in_value;
	valuesHead[*f_index_value].m_truth = *f_isTrue;
	if (*f_isTrue == 0)//����һ�ζ�û�г��ֹ�������
	{
		RemoveValueHead(f_stack_RemovedValueHead, &valuesHead[*f_index_value]);
		return;
	}
	while (this_value)//��������������ֵ�ÿһ��λ��
	{
		bool is_true_here = XOR(this_value->isNegative, *f_isTrue);
		struct ClauseHeadNode* removedClauseHead = &clausesHead[this_value->index_clause];
		struct ValueNode* removedValue_in_clause = clausesHead[this_value->index_clause].nextValue_in_clause;
		if (is_true_here)//�����ֵΪ�棬ɾ������ͷ�������нڵ�
		{
			while (removedValue_in_clause)//ɾ�����������нڵ�
			{
				RemoveValue_in_value(f_stack_RemovedValueHead, removedValue_in_clause);
				RemoveValue_in_clause(f_stack_RemovedValue, removedValue_in_clause);
				removedValue_in_clause = removedValue_in_clause->nextValue_in_clause;
			}
			RemoveClauseHead(f_stack_RemovedClauseHead,removedClauseHead);
		}
		else//�����ֵΪ�٣�ɾ������������ڵ�
		{
			RemoveValue_in_value(f_stack_RemovedValueHead, this_value);
			RemoveValue_in_clause(f_stack_RemovedValue, this_value);
		}
		this_value = this_value->nextValue_in_value;
	}
}
bool CheckEmptyCNF()
{
	if (clausesHeadHead.nextClauseHead)
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
		//�ҵ�û�б����ľ���
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
	struct Stack_Value** f_stack_RemovedValue, 
	struct Stack_ClauseHead** f_stack_RemovedClauseHead,
	struct Stack_ValueHead** f_stack_RemovedValueHead
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
	int* isTrue = (int*)malloc(sizeof(int));
	while (1)
	{
		GetSingleValue_in_clause(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, &stack_RemovedValue , &stack_RemovedClauseHead, &stack_RemovedValueHead);
	}
	{
		if (CheckEmptyCNF())//û�о���
		{
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return true;
		}
		if (CheckEmptyClause())//�пվ���
		{
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return false;
		}
	}
	if (!isTrue)
	{
		isTrue = (int*)malloc(sizeof(int));
	}	
	while (1)
	{
		GetSingleValue_in_value(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, &stack_RemovedValue , &stack_RemovedClauseHead, &stack_RemovedValueHead);
	}
	{
		if (CheckEmptyCNF())//û�о���
		{
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return true;
		}
		if (CheckEmptyClause())//�пվ���
		{
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return false;
		}
	}
	if (!isTrue)
	{
		isTrue = (int*)malloc(sizeof(int));
	}

	bool state = false;
	ChooseValue(index_value_p);

	*isTrue = 1;
	SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
	state = DPLL();
	if (state)
	{
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		return state;
	}

	*isTrue = -1;
	SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
	state = DPLL();
	RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
	return state;
}