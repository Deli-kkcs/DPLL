#include"Definition.h"
#include"Solver.h"
#include"Stack.h"
#include"CNF_Reader.h"
//extern int count_value, count_clause;
bool XOR(bool A, int B)
{
	if ((A && (B == 1)) || (!A && (B == -1)))
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
		if (!this_clauseHead->nextValue_in_clause)//有空句子
		{
			*f_isTrue = NULL;
			return;
			/*this_clauseHead = this_clauseHead->nextClauseHead;
			continue;*/
		}
		if (this_clauseHead->nextValue_in_clause == this_clauseHead->latestValue_in_clause)		//找到只有一个变量的句子
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
		if (!this_ValueHead->nextValue_in_value)//有变量没出现过
		{
			*f_index_value = this_ValueHead->m_value;
			**f_isTrue = 0;
			return;
			/*this_ValueHead = this_ValueHead->nextValueHead;
			continue;*/
		}
		if (this_ValueHead->nextValue_in_value == this_ValueHead->latestValue_in_value)		//找到只出现过一次的变量
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

void ChooseValue(int* f_index_value,int* f_isTrue)
{
	//first in valuesHead
	/*
	*f_index_value = valuesHeadHead.nextValueHead->m_value;
	*f_isTrue = 0;
	*/
	//randomly in sorted_valueAppear
	
	int a;
	srand((unsigned)time(NULL));
	int init_divided = count_clause / count_value;
	//int mod = count_active_Value;
	int mod = count_active_Value / init_divided;
	while (mod == 0)
	{
		init_divided /= 2;
		if (init_divided == 0)
		{
			mod = count_active_Value;
			break;
		}
		mod = count_active_Value / init_divided;
	}
	a = rand() % (mod);
	*f_index_value = sorted_count_valueAppear[count_value - a].m_index_value;
	
	*f_isTrue = 0;
	
	//in clause that has a length of 2
	/*
	int max_value_appear_2 = -1;
	int max_index_value = -1;
	for (int i = 1; i <= count_value; i++)
	{
		count_valueAppear_2[i] = 0;
	}
	struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
	while (this_clauseHead)
	{
		if (this_clauseHead->count_activeValue == 2)
		{
			count_valueAppear_2[this_clauseHead->nextValue_in_clause->m_value]++;
			if (count_valueAppear_2[this_clauseHead->nextValue_in_clause->m_value] > max_value_appear_2)
			{
				max_value_appear_2 = count_valueAppear_2[this_clauseHead->nextValue_in_clause->m_value];
				max_index_value = this_clauseHead->nextValue_in_clause->m_value;
			}
			count_valueAppear_2[this_clauseHead->nextValue_in_clause->nextValue_in_clause->m_value]++;
			if (count_valueAppear_2[this_clauseHead->nextValue_in_clause->nextValue_in_clause->m_value] > max_value_appear_2)
			{
				max_value_appear_2 = count_valueAppear_2[this_clauseHead->nextValue_in_clause->nextValue_in_clause->m_value];
				max_index_value = this_clauseHead->nextValue_in_clause->nextValue_in_clause->m_value;
			}
		}
		this_clauseHead = this_clauseHead->nextClauseHead;
	}
	if (max_index_value == -1)
	{
		*f_index_value = valuesHeadHead.nextValueHead->m_value;
	}
	else
	{
		*f_index_value = max_index_value;
	}*/
	//in sorted_count_valuePoN
	/*
	if (sorted_count_N[count_value].m_count_nega >= sorted_count_P[count_value].m_count_posi)
	{
		*f_isTrue = -1;
		*f_index_value = sorted_count_N[count_value].m_index_value;
	}
	else
	{
		*f_isTrue = 1;
		*f_index_value = sorted_count_P[count_value].m_index_value;
	}
	*/
	
	
	
	

	// to set f_isTrue !!
	
	
	/*struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
	while (this_clauseHead)
	{
		struct ValueNode* this_value = this_clauseHead->nextValue_in_clause;
		while (this_value)
		{
			this_value->isNegative ? count_P[this_value->m_value].count_nega++ : count_P[this_value->m_value].count_posi++;
			if (count_P[this_value->m_value].count_nega > max_nega_appear)
			{
				max_nega_appear = count_P[this_value->m_value].count_nega;
				index_max_nega_appear = this_value->m_value;
			}
			if (count_P[this_value->m_value].count_posi > max_posi_appear)
			{
				max_posi_appear = count_P[this_value->m_value].count_posi;
				index_max_posi_appear = this_value->m_value;
			}
			this_value = this_value->nextValue_in_clause;
		}
		this_clauseHead = this_clauseHead->nextClauseHead;
	}
	if (max_nega_appear >= max_posi_appear)
	{
		*f_index_value = index_max_nega_appear;
		*f_isTrue = -1;
	}
	else
	{
		*f_index_value = index_max_posi_appear;
		*f_isTrue = 1;
	}*/
	if (!fp)
	{
		fp = fopen("E:\\U\\DPLL\\OutPut.txt", "w");
	}
	fprintf(fp, "**** %d-", *f_index_value);
	if (*f_isTrue == 1)
		fprintf(fp, "TRUE");
	if (*f_isTrue == -1)
		fprintf(fp, "FALSE");
	fprintf(fp, "\n");
	
	if (index_lastSelected == *f_index_value)
	{
		//if (*f_index_value == 12)
		{
			printf(".");
		}
		/*
		ChooseValue(f_index_value, f_isTrue);
		return;*/
	}
	index_lastSelected = *f_index_value;
	
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
	//不删除句子头结点
	/*removedClauseHead->nextValue_in_clause = removedClauseHead->nextValue_in_clause->nextValue_in_clause;
	if (removedClauseHead->nextValue_in_clause)
		removedClauseHead->nextValue_in_clause->preValue_in_clause = NULL;*/
	MyPush(f_stack_RemovedValue, removed_value);
	clausesHead[removed_value->index_clause].count_activeValue--;
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
	//删除变量头结点
	if (!may_removedValueHead->latestValue_in_value)//句子中这个节点是变量的唯一一次出现
	{
		RemoveValueHead(f_stack_RemovedValueHead, may_removedValueHead);
		/*if (may_removedValueHead->preValueHead)
			may_removedValueHead->preValueHead->nextValueHead = may_removedValueHead->nextValueHead;
		if (may_removedValueHead->nextValueHead)
			may_removedValueHead->nextValueHead->preValueHead = may_removedValueHead->preValueHead;
		MyPush_3(f_stack_RemovedValueHead, may_removedValueHead);*/
	}
	MinusCountAppear(removed_value->m_value);
	MinusCountPoN(removed_value->m_value, removed_value->isNegative);
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
	count_active_Value--;
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
	if (*f_isTrue == 0)//变量一次都没有出现过的特判
	{
		RemoveValueHead(f_stack_RemovedValueHead, &valuesHead[*f_index_value]);
		return;
	}
	
	while (this_value)//遍历这个参数出现的每一个位置
	{
		bool is_true_here = XOR(this_value->isNegative, *f_isTrue);
		struct ClauseHeadNode* removedClauseHead = &clausesHead[this_value->index_clause];
		struct ValueNode* removedValue_in_clause = clausesHead[this_value->index_clause].nextValue_in_clause;
		if (is_true_here)//这个点值为真，删除句子头及其所有节点
		{
			while (removedValue_in_clause)//删除句子中所有节点
			{
				RemoveValue_in_value(f_stack_RemovedValueHead, removedValue_in_clause);
				RemoveValue_in_clause(f_stack_RemovedValue, removedValue_in_clause);
				removedValue_in_clause = removedValue_in_clause->nextValue_in_clause;
			}
			RemoveClauseHead(f_stack_RemovedClauseHead,removedClauseHead);
		}
		else//这个点值为假，删除句子中这个节点
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
	struct Stack_Value** f_stack_RemovedValue, 
	struct Stack_ClauseHead** f_stack_RemovedClauseHead,
	struct Stack_ValueHead** f_stack_RemovedValueHead
)
{
	struct ClauseHeadNode* back_clauseHead = MyPop_2(f_stack_RemovedClauseHead);
	while (back_clauseHead)
	{
		if (back_clauseHead->preClauseHead)
			back_clauseHead->preClauseHead->nextClauseHead = back_clauseHead;
		if (back_clauseHead->nextClauseHead)
			back_clauseHead->nextClauseHead->preClauseHead = back_clauseHead;
		back_clauseHead = MyPop_2(f_stack_RemovedClauseHead);
	}
	struct ValueHeadNode* back_valueHead = MyPop_3(f_stack_RemovedValueHead);
	while (back_valueHead)
	{
		if (back_valueHead->preValueHead)
			back_valueHead->preValueHead->nextValueHead = back_valueHead;
		if (back_valueHead->nextValueHead)
			back_valueHead->nextValueHead->preValueHead = back_valueHead;
		back_valueHead->m_truth = 0;
		count_active_Value++;

		back_valueHead = MyPop_3(f_stack_RemovedValueHead);
	}
	struct ValueNode* back_value = MyPop(f_stack_RemovedValue);
	while (back_value)
	{
		if (back_value->preValue_in_clause)
			back_value->preValue_in_clause->nextValue_in_clause = back_value;
		else
			clausesHead[back_value->index_clause].nextValue_in_clause = back_value;
		if (back_value->nextValue_in_clause)
			back_value->nextValue_in_clause->preValue_in_clause = back_value;
		if (clausesHead[back_value->index_clause].latestValue_in_clause == back_value->preValue_in_clause)
			clausesHead[back_value->index_clause].latestValue_in_clause = back_value;
		/*if (!clausesHead[back_value->index_clause].nextValue_in_clause)
		{
			clausesHead[back_value->index_clause].nextValue_in_clause = back_value;
			back_value->preValue_in_clause = NULL;
		}*/

		if (back_value->preValue_in_value)
			back_value->preValue_in_value->nextValue_in_value = back_value;
		else
			valuesHead[back_value->m_value].nextValue_in_value = back_value;
		if (back_value->nextValue_in_value)
			back_value->nextValue_in_value->preValue_in_value = back_value;
		if (valuesHead[back_value->m_value].latestValue_in_value == back_value->preValue_in_value)
			valuesHead[back_value->m_value].latestValue_in_value = back_value;

		AddCountAppear(back_value->m_value);
		AddCountPoN(back_value->m_value, back_value->isNegative);
		clausesHead[back_value->index_clause].count_activeValue++;
		/*if (!valuesHead[back_value->m_value].nextValue_in_value)
		{
			valuesHead[back_value->m_value].nextValue_in_value = back_value;
			back_value->preValue_in_value = NULL;
		}*/
		back_value = MyPop(f_stack_RemovedValue);
	}
}
void MyPrintResult()
{
	count_solution++;
	printf("第%d个解: ",count_solution);
	for (int i = 1; i <= count_value; i++)
	{
		printf("%d ", valuesHead[i].m_truth);
	}
	printf("\n");
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
	//{
		//if (CheckEmptyCNF())//没有句子
		//{
		//	MyPrintResult();
		//	RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		//	return true;
		//}
		//if (CheckEmptyClause())//有空句子
		//{
		//	RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		//	return false;
		//}
	//}
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
		if (CheckEmptyCNF())//没有句子
		{
			MyPrintResult();
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return true;
		}
		if (CheckEmptyClause())//有空句子
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
	ChooseValue(index_value_p, isTrue);
	if (*isTrue == -1)
	{
		*isTrue = -1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		if (state)
		{
			return true;
		}
		*isTrue = 1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		return state;
	}
	else
	{
		*isTrue = 1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		if (state)
		{
			return true;
		}
		*isTrue = -1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		return state;
	}
	
}