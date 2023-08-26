//#ifndef DEFINITION_H_
//#define DEFINITION_H_
#define _CRT_SECURE_NO_WARNINGS
#define max_count_value 10001
#define max_count_clause 150001
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
int count_value, count_clause , count_solution;
FILE* fp;
struct CountAppear
{
	int m_count;
	int m_index_value;
	struct CountAppear* next;
	struct CountAppear* pre;
}count_valueAppear[max_count_value],*head_count_valueAppear;
void AddCountAppear(int f_index_value)
{
	count_valueAppear[f_index_value].m_count++;
	while (count_valueAppear[f_index_value].next)
	{
		if (count_valueAppear[f_index_value].m_count > count_valueAppear[f_index_value].next->m_count)
		{

		}
	}
	//TODO_2
}
void MinusCountAppear(int f_index_value)
{
	count_valueAppear[f_index_value].m_count--;
	//TODO_2
}
//�������
struct ValueNode
{
	int m_value;									//������
	int index_clause;								//�����������
	bool isNegative;								//�Ƿ�Ҫȡ��
	struct ValueNode* nextValue_in_clause;			//�Ӿ�����һ������
	struct ValueNode* preValue_in_clause;			//�Ӿ�����һ������
	struct ValueNode* nextValue_in_value;			//�ñ�����һ�γ��ֵ�λ��
	struct ValueNode* preValue_in_value;			//�ñ�����һ�γ��ֵ�λ��
};
//����ͷ���
struct ValueHeadNode
{
	int m_value;									//������
	int m_truth;									//ȡֵ�Ƿ�Ϊ��
	struct ValueNode* latestValue_in_value;			//�ñ������һ�γ��ֵ�λ��

	//struct ValueNode* valueSpeciallyInValueHead;	//����ͷ������еı����ڵ�����
	struct ValueNode* nextValue_in_value;			//�ñ�����һ�γ��ֵ�λ��

	struct ValueHeadNode* nextValueHead;			//��һ������ͷ���
	struct ValueHeadNode* preValueHead;				//��һ������ͷ���
}/*����ͷ�������*/valuesHead[max_count_value],/*����ͷ����ͷ���*/ valuesHeadHead;
//�Ӿ�ͷ���
struct ClauseHeadNode
{
	//int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//�Ӿ������һ������

	//struct ValueNode* valueSpeciallyInClauseHead;	//�Ӿ�ͷ������еı����ڵ�����
	struct ValueNode* nextValue_in_clause;			

	struct ClauseHeadNode* nextClauseHead;
	struct ClauseHeadNode* preClauseHead;
}/*�Ӿ�ͷ�������*/clausesHead[max_count_clause] ,/*�Ӿ�ͷ����ͷ���*/ clausesHeadHead;
//����ջ
struct Stack_Value 
{
	struct ValueNode* m_value;
	struct Stack_Value* next;
};
struct Stack_ClauseHead
{
	struct ClauseHeadNode* m_value;
	struct Stack_ClauseHead* next;
};
struct Stack_ValueHead
{
	struct ValueHeadNode* m_value;
	struct Stack_ValueHead* next;
};
//#endif // !DEFINATION_H_
