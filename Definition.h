//#ifndef DEFINITION_H_
//#define DEFINITION_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define max_count_value 10001		//最大变量数
#define max_count_clause 150001		//最大子句数
#define N 9							//数独最长边
#define EXIT 0						//退出主循环
#define REPEAT 1					//继续主循环
#define OK 12138					//您有一点好！
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
//出现次数,双数组模拟有序双向链表
struct CountAppear
{
	int m_count;
	int m_index_value;
	int m_index_sorted;
}count_valueAppear[max_count_value],sorted_count_valueAppear[max_count_value];
//正/负数出现次数,双数组模拟有序双向链表
struct CountPosi_or_Nega
{
	int m_count_posi;
	int m_count_nega;
	int m_index_value;
	int m_index_sorted;
}count_P[max_count_value],sorted_count_P[max_count_value],count_N[max_count_value], sorted_count_N[max_count_value];
//变量节点
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
//变量头节点
struct ValueHeadNode
{
	int m_value;									//变量名
	int m_truth;									//取值是否为真
	double m_weight;								//变量权重
	struct ValueNode* latestValue_in_value;			//该变量最后一次出现的位置

	//struct ValueNode* valueSpeciallyInValueHead;	//变量头节点特有的变量节点类型
	struct ValueNode* nextValue_in_value;			//该变量下一次出现的位置

	struct ValueHeadNode* nextValueHead;			//下一个变量头节点
	struct ValueHeadNode* preValueHead;				//上一个变量头节点
}/*变量头节点数组*/valuesHead[max_count_value],/*变量头节点的头节点*/ valuesHeadHead;
//子句头节点
struct ClauseHeadNode
{
	int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//子句中最后一个变量

	//struct ValueNode* valueSpeciallyInClauseHead;	//子句头节点特有的变量节点类型
	struct ValueNode* nextValue_in_clause;			//子句中下一个变量

	struct ClauseHeadNode* nextClauseHead;			//下一个子句头节点
	struct ClauseHeadNode* preClauseHead;			//上一个子句头节点
}/*子句头节点数组*/clausesHead[max_count_clause] ,/*子句头节点的头节点*/ clausesHeadHead;
//变量节点栈
struct Stack_Value 
{
	struct ValueNode* m_value;
	struct Stack_Value* next;
};
//子句头节点栈
struct Stack_ClauseHead
{
	struct ClauseHeadNode* m_value;
	struct Stack_ClauseHead* next;
};
//变量头节点栈
struct Stack_ValueHead
{
	struct ValueHeadNode* m_value;
	struct Stack_ValueHead* next;
};
//#endif // !DEFINATION_H_
