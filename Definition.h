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
	int m_index_sorted;
}count_valueAppear[max_count_value],sorted_count_valueAppear[max_count_value];

//变量结点
struct ValueNode
{
	int m_value;									//变量名
	int index_clause;								//所属句子序号
	bool isNegative;								//是否要取非
	struct ValueNode* nextValue_in_clause;			//子句中下一个变量
	struct ValueNode* preValue_in_clause;			//子句中上一个变量
	struct ValueNode* nextValue_in_value;			//该变量下一次出现的位置
	struct ValueNode* preValue_in_value;			//该变量上一次出现的位置
};
//变量头结点
struct ValueHeadNode
{
	int m_value;									//变量名
	int m_truth;									//取值是否为真
	struct ValueNode* latestValue_in_value;			//该变量最后一次出现的位置

	//struct ValueNode* valueSpeciallyInValueHead;	//变量头结点特有的变量节点类型
	struct ValueNode* nextValue_in_value;			//该变量下一次出现的位置

	struct ValueHeadNode* nextValueHead;			//下一个变量头结点
	struct ValueHeadNode* preValueHead;				//上一个变量头结点
}/*变量头结点数组*/valuesHead[max_count_value],/*变量头结点的头结点*/ valuesHeadHead;
//子句头结点
struct ClauseHeadNode
{
	//int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//子句中最后一个变量

	//struct ValueNode* valueSpeciallyInClauseHead;	//子句头结点特有的变量节点类型
	struct ValueNode* nextValue_in_clause;			

	struct ClauseHeadNode* nextClauseHead;
	struct ClauseHeadNode* preClauseHead;
}/*子句头结点数组*/clausesHead[max_count_clause] ,/*子句头结点的头结点*/ clausesHeadHead;
//三种栈
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
