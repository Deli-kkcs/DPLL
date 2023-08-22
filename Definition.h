#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
int count_value, count_clause;

//�������
struct ValueNode
{
	int m_value;									//������
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
	bool isTrue;									//ȡֵ�Ƿ�Ϊ��
	struct ValueNode* latestValue_in_value;			//�ñ������һ�γ��ֵ�λ��

	struct ValueNode* valueSpeciallyInValueHead;	//����ͷ������еı����ڵ�����
	struct ValueNode* nextValue_in_value;			//�ñ�����һ�γ��ֵ�λ��

	struct ValueHeadNode* nextValueHead;			//��һ������ͷ���
	struct ValueHeadNode* preValueHead;				//��һ������ͷ���
}/*����ͷ�������*/valuesHead[1000],/*����ͷ����ͷ���*/ valuesHeadHead;

//�Ӿ�ͷ���
struct ClauseHeadNode
{
	//int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//�Ӿ������һ������

	struct ValueNode* valueSpeciallyInClauseHead;	//�Ӿ�ͷ������еı����ڵ�����
	struct ValueNode* nextValue_in_clause;			

	struct ClauseHeadNode* nextClauseHead;
	struct ClauseHeadNode* preClauseHead;
}/*�Ӿ�ͷ�������*/clausesHead[10000] ,/*�Ӿ�ͷ����ͷ���*/ clausesHeadHead;

/*CNF_Reader�к�������*/
void MyGetString(char t[10]);
char MyGetChar();
char GetLine_Exclude_C();
int Change_string_to_int(char t[10]);
struct ValueNode* CreateNewValueNode(bool isNegative, int index_value);
void AddNextValue_of_Clause(int index_clause, struct ValueNode* new_value);
void AddNextValue_of_Value(int index_value, struct ValueNode* new_value);
void CreateValueHeadLink();
void CreateClauseHeadLink();
void ReadClause(int index_clause);
void ReadCNF(char t);