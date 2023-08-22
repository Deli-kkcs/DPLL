#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
int count_value, count_clause;
//变量结点
struct ValueNode
{
	int m_value;									//变量名
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
	bool isTrue;									//取值是否为真
	struct ValueNode* latestValue_in_value;			//该变量最后一次出现的位置

	//struct ValueNode* valueSpeciallyInValueHead;	//变量头结点特有的变量节点类型
	struct ValueNode* nextValue_in_value;			//该变量下一次出现的位置

	struct ValueHeadNode* nextValueHead;			//下一个变量头结点
	struct ValueHeadNode* preValueHead;				//上一个变量头结点
}/*变量头结点数组*/valuesHead[1000],/*变量头结点的头结点*/ valuesHeadHead;

//子句头结点
struct ClauseHeadNode
{
	//int count_activeValue;
	struct ValueNode* latestValue_in_clause;		//子句中最后一个变量

	//struct ValueNode* valueSpeciallyInClauseHead;	//子句头结点特有的变量节点类型
	struct ValueNode* nextValue_in_clause;			

	struct ClauseHeadNode* nextClauseHead;
	struct ClauseHeadNode* preClauseHead;
}/*子句头结点数组*/clausesHead[10000] ,/*子句头结点的头结点*/ clausesHeadHead;

typedef struct Stack_Value 
{
	struct ValueNode m_value;
	struct Stack_Value* next;
};
//stack为当前的链栈，a表示入栈元素
struct Stack_Value* push(struct Stack_Value* stack, struct ValueNode value) 
{
	struct Stack_Value* new_elem = (struct Stack_Value*)malloc(sizeof(struct Stack_Value));
	if (!new_elem)
		return new_elem;
	new_elem->m_value = value;
	new_elem->next = stack;
	stack = new_elem;
	return stack;
}
struct Stack_Value* pop(struct Stack_Value* stack) 
{
	if (!stack) 
		return stack;
	struct Stack_Value* p = stack;
	stack = stack->next;
	free(p);
	return stack;
}

/*CNF_Reader中函数声明*/
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

/*Solver中函数声明*/
void GetSingleValue_in_clause(int* f_index_value, bool* f_isTrue);
void GetSingleValue_in_value(int* f_index_value, bool* f_isTrue);
int ChooseValue();
void SetValue(int* f_index_value, bool* f_isTrue);
bool CheckEmptyCNF();
bool CheckEmptyClause();
bool DPLL();