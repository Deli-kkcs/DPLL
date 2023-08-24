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
	int m_truth;									//ȡֵ�Ƿ�Ϊ��
	struct ValueNode* latestValue_in_value;			//�ñ������һ�γ��ֵ�λ��

	//struct ValueNode* valueSpeciallyInValueHead;	//����ͷ������еı����ڵ�����
	struct ValueNode* nextValue_in_value;			//�ñ�����һ�γ��ֵ�λ��

	struct ValueHeadNode* nextValueHead;			//��һ������ͷ���
	struct ValueHeadNode* preValueHead;				//��һ������ͷ���
}/*����ͷ�������*/valuesHead[1000],/*����ͷ����ͷ���*/ valuesHeadHead;

//�Ӿ�ͷ���
struct ClauseHeadNode
{
	//int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//�Ӿ������һ������

	//struct ValueNode* valueSpeciallyInClauseHead;	//�Ӿ�ͷ������еı����ڵ�����
	struct ValueNode* nextValue_in_clause;			

	struct ClauseHeadNode* nextClauseHead;
	struct ClauseHeadNode* preClauseHead;
}/*�Ӿ�ͷ�������*/clausesHead[10000] ,/*�Ӿ�ͷ����ͷ���*/ clausesHeadHead;

//����ջ���弰Stack.c�к�������
struct Stack_Value 
{
	struct ValueNode m_value;
	struct Stack_Value* next;
};
struct Stack_Value* MyPush(struct Stack_Value* stack, struct ValueNode value);
struct Stack_Value* MyPop(struct Stack_Value* stack);
struct Stack_ClauseHead
{
	struct ClauseHeadNode m_value;
	struct Stack_ClauseHead* next;
};
struct Stack_ClauseHead* MyPush_2(struct Stack_ClauseHead* stack, struct ClauseHeadNode value);
struct Stack_ClauseHead* MyPop_2(struct Stack_ClauseHead* stack);
struct Stack_ValueHead
{
	struct ValueHeadNode m_value;
	struct Stack_ValueHead* next;
};
struct Stack_ValueHead* MyPush_3(struct Stack_ValueHead* stack, struct ValueHeadNode value);
struct Stack_ValueHead* MyPop_3(struct Stack_ValueHead* stack);


/*CNF_Reader.c�к�������*/
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

/*Solver.c�к�������*/
void/* struct ClauseHeadNode* */ GetSingleValue_in_clause(int* f_index_value, bool** f_isTrue);
void GetSingleValue_in_value(int* f_index_value, bool** f_isTrue);
void ChooseValue(int* f_index_value);
void SetValue
(
	int* f_index_value,bool* f_isTrue,
	struct Stack_Value* f_stack_RemovedValue,
	struct Stack_ClauseHead* f_stack_RemovedClauseHead,
	struct Stack_ValueHead* f_stack_RemovedValueHead
);
bool CheckEmptyCNF();
bool CheckEmptyClause();
void RevertChange
(
	struct Stack_Value* f_stack_RemovedValue,
	struct Stack_ClauseHead* f_stack_RemovedClauseHead,
	struct Stack_ValueHead* f_stack_RemovedValueHead
);
bool DPLL();