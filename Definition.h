//#ifndef DEFINITION_H_
//#define DEFINITION_H_
#define _CRT_SECURE_NO_WARNINGS
#define max_count_value 10001
#define max_count_clause 150001
#define N 9
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
int count_value, count_clause , count_solution , count_active_Value,index_lastSelected;
FILE* fp_InPut_CNF;
FILE* fp_InPut_Sodoku;
FILE* fp_OutPut_Selection;
FILE* fp_OutPut_CNF_of_Sodoku;
char position_InPut_CNF[1000];
char position_InPut_Sodoku[1000];
char position_OutPut_Sodoku_CNF[1000];
struct CountAppear
{
	int m_count;
	int m_index_value;
	int m_index_sorted;
}count_valueAppear[max_count_value],sorted_count_valueAppear[max_count_value];
struct CountPosi_or_Nega
{
	int m_count_posi;
	int m_count_nega;
	int m_index_value;
	int m_index_sorted;
}count_P[max_count_value],sorted_count_P[max_count_value],count_N[max_count_value], sorted_count_N[max_count_value];
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
	int count_activeValue;
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
