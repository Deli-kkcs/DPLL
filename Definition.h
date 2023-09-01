//#ifndef DEFINITION_H_
//#define DEFINITION_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define max_count_value 10001		//��������
#define max_count_clause 150001		//����Ӿ���
#define N 9							//�������
#define EXIT 0						//�˳���ѭ��
#define REPEAT 1					//������ѭ��
#define OK 12138					//����һ��ã�
int count_value, count_clause , count_solution , count_active_Value,index_lastSelected;
int selection_strategy;
FILE* fp_InPut_CNF;
FILE* fp_InPut_Sodoku;
FILE* fp_OutPut_Sodoku;
FILE* fp_OutPut_Selection;
FILE* fp_OutPut_CNF_of_Sodoku;
FILE* fp_OutPut_Res;
char position_InPut_CNF[1000];
char position_InPut_Sodoku[1000];
char position_OutPut_Sodoku[1000];
char position_OutPut_Sodoku_CNF[1000];
char position_OutPut_Res[1000];
//���ִ���,˫����ģ������˫������
struct CountAppear
{
	int m_count;
	int m_index_value;
	int m_index_sorted;
}count_valueAppear[max_count_value],sorted_count_valueAppear[max_count_value];
//��/�������ִ���,˫����ģ������˫������
struct CountPosi_or_Nega
{
	int m_count_posi;
	int m_count_nega;
	int m_index_value;
	int m_index_sorted;
}count_P[max_count_value],sorted_count_P[max_count_value],count_N[max_count_value], sorted_count_N[max_count_value];
//�����ڵ�
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
//����ͷ�ڵ�
struct ValueHeadNode
{
	int m_value;									//������
	int m_truth;									//ȡֵ�Ƿ�Ϊ��
	double m_weight;								//����Ȩ��
	struct ValueNode* latestValue_in_value;			//�ñ������һ�γ��ֵ�λ��

	//struct ValueNode* valueSpeciallyInValueHead;	//����ͷ�ڵ����еı����ڵ�����
	struct ValueNode* nextValue_in_value;			//�ñ�����һ�γ��ֵ�λ��

	struct ValueHeadNode* nextValueHead;			//��һ������ͷ�ڵ�
	struct ValueHeadNode* preValueHead;				//��һ������ͷ�ڵ�
}/*����ͷ�ڵ�����*/valuesHead[max_count_value],/*����ͷ�ڵ��ͷ�ڵ�*/ valuesHeadHead;
//�Ӿ�ͷ�ڵ�
struct ClauseHeadNode
{
	int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//�Ӿ������һ������

	//struct ValueNode* valueSpeciallyInClauseHead;	//�Ӿ�ͷ�ڵ����еı����ڵ�����
	struct ValueNode* nextValue_in_clause;			//�Ӿ�����һ������

	struct ClauseHeadNode* nextClauseHead;			//��һ���Ӿ�ͷ�ڵ�
	struct ClauseHeadNode* preClauseHead;			//��һ���Ӿ�ͷ�ڵ�
}/*�Ӿ�ͷ�ڵ�����*/clausesHead[max_count_clause] ,/*�Ӿ�ͷ�ڵ��ͷ�ڵ�*/ clausesHeadHead;
//�����ڵ�ջ
struct Stack_Value 
{
	struct ValueNode* m_value;
	struct Stack_Value* next;
};
//�Ӿ�ͷ�ڵ�ջ
struct Stack_ClauseHead
{
	struct ClauseHeadNode* m_value;
	struct Stack_ClauseHead* next;
};
//����ͷ�ڵ�ջ
struct Stack_ValueHead
{
	struct ValueHeadNode* m_value;
	struct Stack_ValueHead* next;
};
//#endif // !DEFINATION_H_
