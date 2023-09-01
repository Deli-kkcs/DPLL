#include"Definition.h"
#include"Solver.h"
#include"Stack.h"
#include"CNF_Reader.h"
#include"HaniddokuC.h"
//���:�����и��� �� ������ֵΪ��  ֻ��һ��Ϊ��ʱ���ؼ�
bool XOR(bool A, int B)
{
	if ((A && (B == 1)) || (!A && (B == -1)))
		return false;
	return true;
}
//��ȡֻ��һ���������Ӿ�
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
//��ȡֻ���ֹ�һ�εı���
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
//��ȡ����ʱȫ��Ϊ���򸺵Ĵ�����
void GetPureValue(int* f_index_value, int** f_isTrue)
{
	struct ValueHeadNode* this_valueHead = valuesHeadHead.nextValueHead;
	while (this_valueHead)
	{
		int truth_first = 0;
		bool isPure = false;
		struct ValueNode* this_value = this_valueHead->nextValue_in_value;
		while (this_value)//����ÿһ���������ֵ�λ��
		{
			if (truth_first == 0)//�״γ���ʱ�����״γ��ֵ�ֵ
			{
				isPure = true;
				truth_first = this_value->isNegative ? 1 : -1;
			}
			else if (truth_first != this_value->isNegative)//���Ǵ�����������ѭ��,������һ������
			{
				isPure = false;
				break;
			}
			this_value = this_value->nextValue_in_value;
		}
		if (isPure)
		{
			**f_isTrue = truth_first;
			*f_index_value =  this_valueHead->m_value;
			return;
		}
		this_valueHead = this_valueHead->nextValueHead;
	}
	*f_isTrue = NULL;
}
//�Ȳ����ѵ�ѡ����һ������ 9�ֲ���
void ChooseValue(int* f_index_value,int* f_isTrue)
{
	switch (selection_strategy)
	{
		case 0://first in valuesHead
		{
			*f_index_value = valuesHeadHead.nextValueHead->m_value;
			*f_isTrue = 0;
			break;
		}
		case 1://random in most common value
		{
			int a = 0;
			srand((unsigned)time(NULL));
			int init_divided = /*count_clause / count_value*/8;
			//int mod = count_active_Value;
			int mod = count_active_Value / init_divided;
			if (count_active_Value < 8)
				mod = count_active_Value;
			/*while (mod == 0)
			{
				init_divided /= 2;
				if (init_divided == 0)
				{
					mod = count_active_Value;
					break;
				}
				mod = count_active_Value / init_divided;
			}*/
			a = rand() % (mod);
			* f_index_value = sorted_count_valueAppear[count_value - a].m_index_value;
			*f_isTrue = 0;
			break;
		}
		case 2://most common value
		{
			*f_index_value = sorted_count_valueAppear[count_value].m_index_value;
			*f_isTrue = 0;
			break;
		}
		case 3://most common posi|nega
		{
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
			break;
		}
		case 4 :case 5://largest weight : +=3|*0.9 after revert
		{
			double max_weight = -2100000000;
			int index_max_weight = 0;
			int count_posi = 0, count_nega = 0;
			struct ValueHeadNode* this_valueHead = valuesHeadHead.nextValueHead;
			while (this_valueHead)
			{
				if (this_valueHead->m_weight > max_weight)
				{
					max_weight = this_valueHead->m_weight;
					index_max_weight = this_valueHead->m_value;
				}
				this_valueHead = this_valueHead->nextValueHead;
			}
			
			//*f_isTrue = 0;
			if (sorted_count_N[count_N[index_max_weight].m_index_sorted].m_count_nega > sorted_count_P[count_P[index_max_weight].m_index_sorted].m_count_posi)
			{
				*f_isTrue = -1;
			}
			else
			{
				*f_isTrue = 1;
			}
			*f_index_value = index_max_weight;
			break;
		}
		case 6://smallest weight : +=3 after revert
		{
			double max_weight = 2100000000;
			int index_max_weight = 0;
			int count_posi = 0, count_nega = 0;
			struct ValueHeadNode* this_valueHead = valuesHeadHead.nextValueHead;
			while (this_valueHead)
			{
				if (this_valueHead->m_weight < max_weight)
				{
					max_weight = this_valueHead->m_weight;
					index_max_weight = this_valueHead->m_value;
				}
				this_valueHead = this_valueHead->nextValueHead;
			}
			if (sorted_count_N[count_N[index_max_weight].m_index_sorted].m_count_nega > sorted_count_P[count_P[index_max_weight].m_index_sorted].m_count_posi)
			{
				*f_isTrue = -1;
			}
			else
			{
				*f_isTrue = 1;
			}
			*f_index_value = index_max_weight;
			break;
		}
		case 7://largest weight : summary of pow(0.5 , length_clause-1)
		{
			double max_weihgt = -1;
			int index_max_weight = -1;
			int isTrue_while_max = 0;
			struct ValueHeadNode* this_valueHead = valuesHeadHead.nextValueHead;
			while (this_valueHead)
			{
				int temp_isTrue_while_max;
				int count_appear = sorted_count_valueAppear[count_valueAppear[this_valueHead->m_value].m_index_sorted].m_count;
				for (int i = 0; i <= 1; i++)
				{
					if (i == 0)
					{
						temp_isTrue_while_max = 1;
					}
					else
					{
						temp_isTrue_while_max = -1;
					}
					double weight_this_value = 0;
					struct ValueNode* this_Value_in_value = this_valueHead->nextValue_in_value;
					while (this_Value_in_value)
					{
						if (!XOR(this_Value_in_value->isNegative, temp_isTrue_while_max))
						{
							this_Value_in_value = this_Value_in_value->nextValue_in_value;
							continue;
						}
						int length_clause = 0;
						struct ValueNode* this_Value_in_clause = clausesHead[this_Value_in_value->index_clause].nextValue_in_clause;
						while (this_Value_in_clause)
						{
							length_clause++;
							this_Value_in_clause = this_Value_in_clause->nextValue_in_clause;
						}
						weight_this_value += pow(0.5, length_clause - 1);
						this_Value_in_value = this_Value_in_value->nextValue_in_value;
					}
					//weight_this_value *= pow(1, count_appear);
if (weight_this_value > max_weihgt)
{
	max_weihgt = weight_this_value;
	index_max_weight = this_valueHead->m_value;
	isTrue_while_max = temp_isTrue_while_max;
}
				}

				this_valueHead = this_valueHead->nextValueHead;
			}
			*f_isTrue = isTrue_while_max;
			*f_index_value = index_max_weight;
			break;
		}
		case 8://(posi + 1)*(nega + 1) in 2-length clause
		{
			long int max_weihgt = -1;
			int index_max_weight = -1;
			int min_length_clause = 2100000000;
			struct ClauseHeadNode* this_clauseHead = clausesHeadHead.nextClauseHead;
			while (this_clauseHead)
			{
				if (this_clauseHead->count_activeValue < min_length_clause)
					min_length_clause = this_clauseHead->count_activeValue;
				this_clauseHead = this_clauseHead->nextClauseHead;
			}
			struct ValueHeadNode* this_valueHead = valuesHeadHead.nextValueHead;
			while (this_valueHead)
			{
				int count_posi = 0, count_nega = 0;
				long int weight_this_value = 0;
				struct ValueNode* this_Value_in_value = this_valueHead->nextValue_in_value;
				while (this_Value_in_value)
				{
					if (clausesHead[this_Value_in_value->m_value].count_activeValue != /*min_length_clause*/2)
					{
						this_Value_in_value = this_Value_in_value->nextValue_in_value;
						continue;
					}
					if (this_Value_in_value->isNegative)
						count_nega++;
					else
						count_posi++;
					this_Value_in_value = this_Value_in_value->nextValue_in_value;
				}
				weight_this_value = (count_nega + 1) * (count_posi + 1);
				//weight_this_value *= pow(1, count_appear);
				if (weight_this_value > max_weihgt)
				{
					max_weihgt = weight_this_value;
					index_max_weight = this_valueHead->m_value;
					/*if(count_nega > count_posi)
						*f_isTrue = 1;
					else
						*f_isTrue = -1;*/
				}
				this_valueHead = this_valueHead->nextValueHead;
			}

			*f_index_value = index_max_weight;
			break;
		}
	}
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
	//����ֵ���������txt�ļ�
	{
		if (!fp_OutPut_Selection)
		{
			fp_OutPut_Selection = fopen("E:\\U\\DPLL\\OutPut.txt", "w");
		}
		fprintf(fp_OutPut_Selection, "**** %d-", *f_index_value);
		if (*f_isTrue == 1)
			fprintf(fp_OutPut_Selection, "TRUE");
		if (*f_isTrue == -1)
			fprintf(fp_OutPut_Selection, "FALSE");
		fprintf(fp_OutPut_Selection, "\n");
	}
	
	//�������һ�θ�ֵ�ı���
	if (index_lastSelected == *f_index_value)
	{
		valuesHead[index_lastSelected].m_weight += 2;
		printf(".");
	}
	index_lastSelected = *f_index_value;
}
//�Ƴ��Ӿ��еı���
void RemoveValue_in_clause(struct Stack_Value** f_stack_RemovedValue, struct ValueNode* removed_value)
{
	struct ClauseHeadNode* clauseHead_here = &clausesHead[removed_value->index_clause];
	if (clauseHead_here->latestValue_in_clause == removed_value)//����β�ڵ�
		clauseHead_here->latestValue_in_clause = removed_value->preValue_in_clause;
	if (clauseHead_here->nextValue_in_clause == removed_value)//ͷ�ڵ�����
		clauseHead_here->nextValue_in_clause = clauseHead_here->nextValue_in_clause->nextValue_in_clause;
	if (removed_value->preValue_in_clause)
		removed_value->preValue_in_clause->nextValue_in_clause = removed_value->nextValue_in_clause;
	if (removed_value->nextValue_in_clause)
		removed_value->nextValue_in_clause->preValue_in_clause = removed_value->preValue_in_clause;
	//��ɾ������ͷ�ڵ�
	MyPush(f_stack_RemovedValue, removed_value);
	clausesHead[removed_value->index_clause].count_activeValue--;
}
//�Ƴ�������һ�εĳ���
void RemoveValue_in_value(struct Stack_ValueHead** f_stack_RemovedValueHead, struct ValueNode* removed_value)
{
	struct ValueHeadNode* may_removedValueHead = &valuesHead[removed_value->m_value];
	if (may_removedValueHead->latestValue_in_value == removed_value)//����β�ڵ�
		may_removedValueHead->latestValue_in_value = removed_value->preValue_in_value;
	if (may_removedValueHead->nextValue_in_value == removed_value)//ͷ�ڵ�����
		may_removedValueHead->nextValue_in_value = may_removedValueHead->nextValue_in_value->nextValue_in_value;
;	if (removed_value->preValue_in_value)
		removed_value->preValue_in_value->nextValue_in_value = removed_value->nextValue_in_value;
	if (removed_value->nextValue_in_value)
		removed_value->nextValue_in_value->preValue_in_value = removed_value->preValue_in_value;
	//ɾ������ͷ�ڵ�
	if (!may_removedValueHead->latestValue_in_value)//����������ڵ��Ǳ�����Ψһһ�γ���
	{
		RemoveValueHead(f_stack_RemovedValueHead, may_removedValueHead);
	}
	MinusCountAppear(removed_value->m_value);
	MinusCountPoN(removed_value->m_value, removed_value->isNegative);
}
//�Ƴ��Ӿ�ͷ�ڵ�
void RemoveClauseHead(struct Stack_ClauseHead** f_stack_RemovedClauseHead, struct ClauseHeadNode* removed_clauseHead)
{
	if (removed_clauseHead->preClauseHead)
		removed_clauseHead->preClauseHead->nextClauseHead = removed_clauseHead->nextClauseHead;
	if (removed_clauseHead->nextClauseHead)
		removed_clauseHead->nextClauseHead->preClauseHead = removed_clauseHead->preClauseHead;
	MyPush_2(f_stack_RemovedClauseHead,removed_clauseHead);
}
//�Ƴ�����ͷ�ڵ�
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
//��������ֵ
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
	valuesHead[*f_index_value].m_weight += 1;
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
//����Ƿ�Ϊ��cnf,����������
bool CheckEmptyCNF()
{
	if (clausesHeadHead.nextClauseHead)
	{
		return false;
	}
	return true;
}
//����Ƿ��п��Լ�,���򲻿�����
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
//���������ĸ�ֵ
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
		if (selection_strategy == 5)
		{
			valuesHead[back_value->m_value].m_weight *= 0.9;
		}
		else
		{
			valuesHead[back_value->m_value].m_weight += 3;
		}
		/*if (!valuesHead[back_value->m_value].nextValue_in_value)
		{
			valuesHead[back_value->m_value].nextValue_in_value = back_value;
			back_value->preValue_in_value = NULL;
		}*/
		back_value = MyPop(f_stack_RemovedValue);
	}
}
//�ڿ���̨�����
void MyPrintResult()
{
	count_solution++;
	printf("��%d����: ",count_solution);
	for (int i = 1; i <= count_value; i++)
	{
		printf("%d ", valuesHead[i].m_truth);
	}
	printf("\n");
	Convert_CNF_to_Sodoku();
}
//�ѽ������ͬĿ¼ͬ��.res�ļ�
void WriteRes(int count_solution, double time)
{
	if (time == -1 && count_solution != 0)
	{
		fprintf(fp_OutPut_Res, "s %d\n", count_solution);
		fprintf(fp_OutPut_Res, "v ");
		for (int i = 1; i <= count_value; i++)
		{
			if (valuesHead[i].m_truth == 1)
			{
				fprintf(fp_OutPut_Res, "%d ", i);
			}
			else if(valuesHead[i].m_truth == -1)
			{
				fprintf(fp_OutPut_Res, "-%d ", i);
			}
			else
			{
				fprintf(fp_OutPut_Res, "*%d ", i);
			}
		}
		fprintf(fp_OutPut_Res, "\n");
	}
	else if (time != -1 && count_solution != 0)
	{
		fprintf(fp_OutPut_Res, "t %d", (int)time);
	}
	else if( time != -1 && count_solution == 0)
	{
		fprintf(fp_OutPut_Res, "s 0\n");
		fprintf(fp_OutPut_Res, "v \n");
		fprintf(fp_OutPut_Res, "t %d", (int)time);
		return;
	}
}
//DPLL���ݹ�
bool DPLL()
{
	struct Stack_Value* stack_RemovedValue = NULL/*(struct Stack_Value*)malloc(sizeof(struct Stack_Value))*/;
	struct Stack_ClauseHead* stack_RemovedClauseHead = NULL/*(struct Stack_ClauseHead*)malloc(sizeof(struct Stack_ClauseHead))*/;
	struct Stack_ValueHead* stack_RemovedValueHead = NULL/*(struct Stack_ValueHead*)malloc(sizeof(struct Stack_ValueHead))*/;
	int* index_value_p = (int*)malloc(sizeof(int));
	int* isTrue = (int*)malloc(sizeof(int));
	while (1)//��鵥λ�Ӿ�
	{
		GetSingleValue_in_clause(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, &stack_RemovedValue , &stack_RemovedClauseHead, &stack_RemovedValueHead);
	}
	if (!isTrue)
	{
		isTrue = (int*)malloc(sizeof(int));
	}
	while (1)//����������
	{
		GetSingleValue_in_value(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, &stack_RemovedValue , &stack_RemovedClauseHead, &stack_RemovedValueHead);
	}
	if (!isTrue)
	{
		isTrue = (int*)malloc(sizeof(int));
	}
	while (1)//��鴿����
	{
		GetPureValue(index_value_p, &isTrue);
		if (!isTrue)
			break;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
	}
	if (!isTrue)
	{
		isTrue = (int*)malloc(sizeof(int));
	}
	{//��鸳ֵ�Ƿ����
		if (CheckEmptyCNF())//û�о���
		{
			MyPrintResult();
			WriteRes(count_solution, -1);
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return true;
		}
		if (CheckEmptyClause())//�пվ���
		{
			RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
			return false;
		}
	}
	

	bool state = false;
	ChooseValue(index_value_p, isTrue);//ѡ������������ȸ�ֵ�����
	if (*isTrue == -1)//���ȸ�ֵΪ��
	{
		*isTrue = -1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		if (state)//������ͷ���
		{
			return true;
		}
		*isTrue = 1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		return state;
	}
	else//���ȸ�ֵΪ��
	{
		*isTrue = 1;
		SetValue(index_value_p, isTrue, &stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		state = DPLL();
		RevertChange(&stack_RemovedValue, &stack_RemovedClauseHead, &stack_RemovedValueHead);
		if (state)//������ͷ���
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