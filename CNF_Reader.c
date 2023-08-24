#include"Definition.h"
#include"CNF_Reader.h"
//extern int count_value, count_clause;
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
	struct ValueNode* new_value =(struct ValueNode*)malloc(sizeof(struct ValueNode*));
	if (!new_value)return new_value;
	new_value->isNegative = isNegative;
	new_value->m_value = index_value;
	new_value->preValue_in_clause = NULL;
	new_value->nextValue_in_clause = NULL;
	new_value->preValue_in_value = NULL;
	new_value->nextValue_in_value = NULL;
	return new_value;
}
void AddNextValue_of_Clause(int index_clause,struct ValueNode* new_value)
{
	if (!clausesHead[index_clause].latestValue_in_clause)
	{
		clausesHead[index_clause].nextValue_in_clause = new_value;
		//new_value->preValue_in_clause = clausesHead[index_clause].valueSpeciallyInClauseHead;
		new_value->preValue_in_clause = NULL;
	}
	else
	{
		clausesHead[index_clause].latestValue_in_clause->nextValue_in_clause = new_value;
		new_value->preValue_in_clause = clausesHead[index_clause].latestValue_in_clause;
	}
	clausesHead[index_clause].latestValue_in_clause = new_value;
}
void AddNextValue_of_Value(int index_value,struct ValueNode* new_value)
{
	if (!valuesHead[index_value].nextValue_in_value)
	{
		valuesHead[index_value].nextValue_in_value = new_value;
		//new_value->preValue_in_value = valuesHead[index_value].valueSpeciallyInValueHead;
		new_value->preValue_in_value = NULL;
	}
	else
	{
		valuesHead[index_value].latestValue_in_value->nextValue_in_value = new_value;
		new_value->preValue_in_value = valuesHead[index_value].latestValue_in_value;
	}
	valuesHead[index_value].latestValue_in_value = new_value;
}
void CreateValueHeadLink()
{
	struct ValueHeadNode* last = &valuesHeadHead;
	last->preValueHead = NULL;
	last->nextValueHead = NULL;
	for (int i = 1; i <= count_value; i++)
	{
		valuesHead[i].m_value = i;
		valuesHead[i].nextValueHead = NULL;
		last->nextValueHead = &valuesHead[i];
		valuesHead[i].preValueHead = last;
		last = &valuesHead[i];
	}
}
void CreateClauseHeadLink()
{
	struct ClauseHeadNode* last = &clausesHeadHead;
	last->preClauseHead = NULL;
	last->nextClauseHead = NULL;
	for (int i = 0; i < count_clause; i++)
	{
		clausesHead[i].nextClauseHead = NULL;
		last->nextClauseHead = &clausesHead[i];
		clausesHead[i].preClauseHead = last;
		last = &clausesHead[i];
	}
}
void ReadClause(int index_clause)
{
	while (1)
	{
		int index_value = 0;
		bool isNegative = false;
		char t[10];
		MyGetString(t);
		if (strcmp(t,"0") == 0)
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
void ReadCNF(char t)
{
	if (t != 'p')
		return;
	char str[10] = "";
	scanf("%s", str);
	if (str[0] != 'c')
		return;
	scanf("%d%d", &count_value, &count_clause);
	/*values = malloc(sizeof(struct ValueHeadNode) * (count_value + 1));
	if (!values)
		return;
	clauses = malloc(sizeof(struct ValueHeadNode) * (count_clause + 1));
	if (!clauses)
		return;*/
	for (int i = 0; i < count_value; i++)
	{
		valuesHead[i].m_truth = 0;
		valuesHead[i].nextValue_in_value = NULL;
		//valuesHead[i].valueSpeciallyInValueHead = NULL;
		//valuesHead[i].latestValue_in_value = valuesHead[i].valueSpeciallyInValueHead;
		valuesHead[i].latestValue_in_value = NULL;
	}
	for (int i = 0; i < count_clause; i++)
	{
		clausesHead[i].nextValue_in_clause = NULL;
		clausesHead[i].nextClauseHead = NULL;
		clausesHead[i].preClauseHead = NULL;
		/*clausesHead[i].valueSpeciallyInClauseHead = NULL;
		clausesHead[i].latestValue_in_clause = clausesHead[i].valueSpeciallyInClauseHead;*/
		clausesHead[i].latestValue_in_clause = NULL;

		ReadClause(i);
	}
	CreateValueHeadLink();
	CreateClauseHeadLink();
}
