#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
//const int max_count_value = 1000;
//const int max_count_clause = 1000;
int count_value, count_clause;

struct ValueNode
{
	int m_value;
	bool isActive;
	bool isNegative;
	struct ValueNode* nextValue;
};
struct ValueHeadNode
{
	bool isTrue;			//取值是否为真
	//int name;				//变量名字(int类型)
	struct ValueNode* nextValue;
}values[1000];



struct ClauseHeadNode
{
	//bool isActive;
	int count_activeValue;
	struct ValueNode* nextValue;
}clauses[10000];