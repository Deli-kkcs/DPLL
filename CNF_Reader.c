#include"Definition.h"
void MyGetString(char t[10])
{
	scanf("%s", t);
}
char MyGetChar()
{
	return getchar();
}
char GetLine_Exclude_C()
{
	char t = '0';
	while (1)
	{
		t = MyGetChar();
		if (t != 'c')
			break;
		while (t != '\n')
		{
			t = MyGetChar();
		}
	}
	return t;
}
int Change_string_to_int(char t[10])
{
	int loc = 0,ans = 0;
	while (t[loc] != '\0')
	{
		ans *= 10;
		ans += t[loc] - '0';
		loc++;
	}
	return ans;
}
struct ValueNode* CreateNewValueNode(bool isNegative, int index_value)
{
	struct ValueNode* new_value = malloc(sizeof(struct ValueNode*));
	if (!new_value)return new_value;
	new_value->isActive = false;
	new_value->isNegative = isNegative;
	new_value->m_value = index_value;
	new_value->nextValue = NULL;
	return new_value;
}
void AddNextValue_of_Clause(int index_clause,struct ValueNode* new_value)
{
	if (!clauses[index_clause].nextValue)
	{
		clauses[index_clause].nextValue = new_value;
		return;
	}
	new_value->nextValue = clauses[index_clause].nextValue;
	clauses[index_clause].nextValue = new_value;
}
void AddNextValue_of_Value(int index_value,struct ValueNode* new_value)
{
	if (!values[index_value].nextValue)
	{
		values[index_value].nextValue = new_value;
		return;
	}
	new_value->nextValue = values[index_value].nextValue;
	values[index_value].nextValue = new_value;
}

void ReadClause(int index_clause)
{
	while (1)
	{
		int index_value = 0;
		bool isNegative = false;
		char t[10];
		MyGetString(t);
		if (t == "0")
		{
			break;
		}
		if (t[0] == '-')
		{
			index_value = Change_string_to_int(t + 1);
			isNegative = true;
		}
		else
		{
			index_value = Change_string_to_int(t);
		}
		struct ValueNode* new_value = CreateNewValueNode( isNegative, index_value);
		AddNextValue_of_Clause(index_clause, new_value);
		AddNextValue_of_Value(index_value, new_value);
	}
	
}
/*
c csn cs
p cnf 20 30
1 -2 3 0
*/
void ReadCNF(char t)
{
	if (t != 'p')
		return;
	char str[4] = "";
	scanf("%s", str);
	if (str[0] != 'c')return;
	scanf("%d%d", &count_value, &count_clause);
	/*values = malloc(sizeof(struct ValueHeadNode) * (count_value + 1));
	if (!values)
		return;
	clauses = malloc(sizeof(struct ValueHeadNode) * (count_clause + 1));
	if (!clauses)
		return;*/
	for (int i = 0; i < count_value; i++)
	{
		values[i].isTrue = false;
		values[i].nextValue = NULL;
	}

	for (int i = 0; i < count_clause; i++)
	{
		clauses[i].nextValue = NULL;
		ReadClause(i);
	}
}
int main()
{
	ReadCNF(GetLine_Exclude_C());
	return 0;
}