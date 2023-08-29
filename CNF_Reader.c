#include"Definition.h"
#include"CNF_Reader.h"
#include"Solver.h"
void MyGetString(char t[10])
{
	fscanf(fp_InPut_CNF,"%s", t);
	//scanf("%s", t);
}
void MyGetChar(char *f_char)
{
	fscanf(fp_InPut_CNF, "%c", f_char);
	//return getchar();
}
void MyGetInt(int *f_int)
{
	fscanf(fp_InPut_CNF,"%d", f_int);
	//scanf("%d", f_int);
}
char GetLine_Exclude_C()
{
	char t = '0';
	while (1)
	{
		MyGetChar(&t);
		if (t != 'c')
			break;
		while (t != '\n')
		{
			MyGetChar(&t);
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
struct ValueNode* CreateNewValueNode(bool isNegative, int index_value,int index_clause)
{
	struct ValueNode* new_value =(struct ValueNode*)malloc(sizeof(struct ValueNode));
	if (!new_value)return new_value;
	new_value->isNegative = isNegative;
	new_value->m_value = index_value;
	new_value->index_clause = index_clause;
	new_value->preValue_in_clause = NULL;
	new_value->nextValue_in_clause = NULL;
	new_value->preValue_in_value = NULL;
	new_value->nextValue_in_value = NULL;
	return new_value;
}
void AddCountAppear(int f_index_value)
{
	int this_index_sorted = count_valueAppear[f_index_value].m_index_sorted;
	sorted_count_valueAppear[this_index_sorted].m_count++;
	while(this_index_sorted < count_value)
	{
		if (sorted_count_valueAppear[this_index_sorted].m_count <= sorted_count_valueAppear[this_index_sorted+1].m_count)
			break;
		count_valueAppear[f_index_value].m_index_sorted++;
		count_valueAppear[sorted_count_valueAppear[this_index_sorted + 1].m_index_value].m_index_sorted--;
		int temp_index_value = sorted_count_valueAppear[this_index_sorted].m_index_value;
		sorted_count_valueAppear[this_index_sorted].m_index_value = sorted_count_valueAppear[this_index_sorted + 1].m_index_value;
		sorted_count_valueAppear[this_index_sorted + 1].m_index_value = temp_index_value;
		int temp_index_count = sorted_count_valueAppear[this_index_sorted].m_count;
		sorted_count_valueAppear[this_index_sorted].m_count = sorted_count_valueAppear[this_index_sorted+1].m_count;
		sorted_count_valueAppear[this_index_sorted+1].m_count = temp_index_count;
		this_index_sorted++;
	}
	while (this_index_sorted > 0)
	{
		if (sorted_count_valueAppear[this_index_sorted].m_count >= sorted_count_valueAppear[this_index_sorted - 1].m_count)
			break;
		count_valueAppear[f_index_value].m_index_sorted--;
		count_valueAppear[sorted_count_valueAppear[this_index_sorted - 1].m_index_value].m_index_sorted++;
		int temp_index_value = sorted_count_valueAppear[this_index_sorted].m_index_value;
		sorted_count_valueAppear[this_index_sorted].m_index_value = sorted_count_valueAppear[this_index_sorted - 1].m_index_value;
		sorted_count_valueAppear[this_index_sorted - 1].m_index_value = temp_index_value;
		int temp_index_count = sorted_count_valueAppear[this_index_sorted].m_count;
		sorted_count_valueAppear[this_index_sorted].m_count = sorted_count_valueAppear[this_index_sorted - 1].m_count;
		sorted_count_valueAppear[this_index_sorted - 1].m_count = temp_index_count;
		this_index_sorted--;
	}
}
void MinusCountAppear(int f_index_value)
{
	int this_index_sorted = count_valueAppear[f_index_value].m_index_sorted;
	sorted_count_valueAppear[this_index_sorted].m_count--;
	while (this_index_sorted < count_value)
	{
		if (sorted_count_valueAppear[this_index_sorted].m_count <= sorted_count_valueAppear[this_index_sorted + 1].m_count)
			break;
		count_valueAppear[f_index_value].m_index_sorted++;
		count_valueAppear[sorted_count_valueAppear[this_index_sorted + 1].m_index_value].m_index_sorted--;
		int temp_index_value = sorted_count_valueAppear[this_index_sorted].m_index_value;
		sorted_count_valueAppear[this_index_sorted].m_index_value = sorted_count_valueAppear[this_index_sorted + 1].m_index_value;
		sorted_count_valueAppear[this_index_sorted + 1].m_index_value = temp_index_value;
		int temp_index_count = sorted_count_valueAppear[this_index_sorted].m_count;
		sorted_count_valueAppear[this_index_sorted].m_count = sorted_count_valueAppear[this_index_sorted + 1].m_count;
		sorted_count_valueAppear[this_index_sorted + 1].m_count = temp_index_count;
		this_index_sorted++;
	}
	while (this_index_sorted > 0)
	{
		if (sorted_count_valueAppear[this_index_sorted].m_count >= sorted_count_valueAppear[this_index_sorted - 1].m_count)
			break;
		count_valueAppear[f_index_value].m_index_sorted--;
		count_valueAppear[sorted_count_valueAppear[this_index_sorted - 1].m_index_value].m_index_sorted++;
		int temp_index_value = sorted_count_valueAppear[this_index_sorted].m_index_value;
		sorted_count_valueAppear[this_index_sorted].m_index_value = sorted_count_valueAppear[this_index_sorted - 1].m_index_value;
		sorted_count_valueAppear[this_index_sorted - 1].m_index_value = temp_index_value;
		int temp_index_count = sorted_count_valueAppear[this_index_sorted].m_count;
		sorted_count_valueAppear[this_index_sorted].m_count = sorted_count_valueAppear[this_index_sorted - 1].m_count;
		sorted_count_valueAppear[this_index_sorted - 1].m_count = temp_index_count;
		this_index_sorted--;
	}
}
void AddCountPoN(int f_index_value , bool f_isNegative)
{
	if (f_isNegative)
	{
		int this_index_sorted = count_N[f_index_value].m_index_sorted;
		sorted_count_N[this_index_sorted].m_count_nega++;
		while (this_index_sorted < count_value)
		{
			if (sorted_count_N[this_index_sorted].m_count_nega <= sorted_count_N[this_index_sorted + 1].m_count_nega)
				break;
			count_N[f_index_value].m_index_sorted++;
			count_N[sorted_count_N[this_index_sorted + 1].m_index_value].m_index_sorted--;
			int temp_index_value = sorted_count_N[this_index_sorted].m_index_value;
			sorted_count_N[this_index_sorted].m_index_value = sorted_count_N[this_index_sorted + 1].m_index_value;
			sorted_count_N[this_index_sorted + 1].m_index_value = temp_index_value;
			int temp_index_count_nega = sorted_count_N[this_index_sorted].m_count_nega;
			sorted_count_N[this_index_sorted].m_count_nega = sorted_count_N[this_index_sorted + 1].m_count_nega;
			sorted_count_N[this_index_sorted + 1].m_count_nega = temp_index_count_nega;
			this_index_sorted++;
		}
		while (this_index_sorted > 0)
		{
			if (sorted_count_N[this_index_sorted].m_count_nega >= sorted_count_N[this_index_sorted - 1].m_count_nega)
				break;
			count_N[f_index_value].m_index_sorted--;
			count_N[sorted_count_N[this_index_sorted - 1].m_index_value].m_index_sorted++;
			int temp_index_value = sorted_count_N[this_index_sorted].m_index_value;
			sorted_count_N[this_index_sorted].m_index_value = sorted_count_N[this_index_sorted - 1].m_index_value;
			sorted_count_N[this_index_sorted - 1].m_index_value = temp_index_value;
			int temp_index_count_nega = sorted_count_N[this_index_sorted].m_count_nega;
			sorted_count_N[this_index_sorted].m_count_nega = sorted_count_N[this_index_sorted - 1].m_count_nega;
			sorted_count_N[this_index_sorted - 1].m_count_nega = temp_index_count_nega;
			this_index_sorted--;
		}
	}
	else
	{
		int this_index_sorted = count_P[f_index_value].m_index_sorted;
		sorted_count_P[this_index_sorted].m_count_posi++;
		while (this_index_sorted < count_value)
		{
			if (sorted_count_P[this_index_sorted].m_count_posi <= sorted_count_P[this_index_sorted + 1].m_count_posi)
				break;
			count_P[f_index_value].m_index_sorted++;
			count_P[sorted_count_P[this_index_sorted + 1].m_index_value].m_index_sorted--;
			int temp_index_value = sorted_count_P[this_index_sorted].m_index_value;
			sorted_count_P[this_index_sorted].m_index_value = sorted_count_P[this_index_sorted + 1].m_index_value;
			sorted_count_P[this_index_sorted + 1].m_index_value = temp_index_value;
			int temp_index_count_posi = sorted_count_P[this_index_sorted].m_count_posi;
			sorted_count_P[this_index_sorted].m_count_posi = sorted_count_P[this_index_sorted + 1].m_count_posi;
			sorted_count_P[this_index_sorted + 1].m_count_posi = temp_index_count_posi;
			this_index_sorted++;
		}
		while (this_index_sorted > 0)
		{
			if (sorted_count_P[this_index_sorted].m_count_posi >= sorted_count_P[this_index_sorted - 1].m_count_posi)
				break;
			count_P[f_index_value].m_index_sorted--;
			count_P[sorted_count_P[this_index_sorted - 1].m_index_value].m_index_sorted++;
			int temp_index_value = sorted_count_P[this_index_sorted].m_index_value;
			sorted_count_P[this_index_sorted].m_index_value = sorted_count_P[this_index_sorted - 1].m_index_value;
			sorted_count_P[this_index_sorted - 1].m_index_value = temp_index_value;
			int temp_index_count_posi = sorted_count_P[this_index_sorted].m_count_posi;
			sorted_count_P[this_index_sorted].m_count_posi = sorted_count_P[this_index_sorted - 1].m_count_posi;
			sorted_count_P[this_index_sorted - 1].m_count_posi = temp_index_count_posi;
			this_index_sorted--;
		}
	}
}
void MinusCountPoN(int f_index_value, bool f_isNegative)
{
	int this_index_sorted = count_P[f_index_value].m_index_sorted;
	if (f_isNegative)
	{
		int this_index_sorted = count_N[f_index_value].m_index_sorted;
		sorted_count_N[this_index_sorted].m_count_nega--;
		while (this_index_sorted < count_value)
		{
			if (sorted_count_N[this_index_sorted].m_count_nega <= sorted_count_N[this_index_sorted + 1].m_count_nega)
				break;
			count_N[f_index_value].m_index_sorted++;
			count_N[sorted_count_N[this_index_sorted + 1].m_index_value].m_index_sorted--;
			int temp_index_value = sorted_count_N[this_index_sorted].m_index_value;
			sorted_count_N[this_index_sorted].m_index_value = sorted_count_N[this_index_sorted + 1].m_index_value;
			sorted_count_N[this_index_sorted + 1].m_index_value = temp_index_value;
			int temp_index_count_nega = sorted_count_N[this_index_sorted].m_count_nega;
			sorted_count_N[this_index_sorted].m_count_nega = sorted_count_N[this_index_sorted + 1].m_count_nega;
			sorted_count_N[this_index_sorted + 1].m_count_nega = temp_index_count_nega;
			this_index_sorted++;
		}
		while (this_index_sorted > 0)
		{
			if (sorted_count_N[this_index_sorted].m_count_nega >= sorted_count_N[this_index_sorted - 1].m_count_nega)
				break;
			count_N[f_index_value].m_index_sorted--;
			count_N[sorted_count_N[this_index_sorted - 1].m_index_value].m_index_sorted++;
			int temp_index_value = sorted_count_N[this_index_sorted].m_index_value;
			sorted_count_N[this_index_sorted].m_index_value = sorted_count_N[this_index_sorted - 1].m_index_value;
			sorted_count_N[this_index_sorted - 1].m_index_value = temp_index_value;
			int temp_index_count_nega = sorted_count_N[this_index_sorted].m_count_nega;
			sorted_count_N[this_index_sorted].m_count_nega = sorted_count_N[this_index_sorted - 1].m_count_nega;
			sorted_count_N[this_index_sorted - 1].m_count_nega = temp_index_count_nega;
			this_index_sorted--;
		}
	}
	else
	{
		int this_index_sorted = count_P[f_index_value].m_index_sorted;
		sorted_count_P[this_index_sorted].m_count_posi--;
		while (this_index_sorted < count_value)
		{
			if (sorted_count_P[this_index_sorted].m_count_posi <= sorted_count_P[this_index_sorted + 1].m_count_posi)
				break;
			count_P[f_index_value].m_index_sorted++;
			count_P[sorted_count_P[this_index_sorted + 1].m_index_value].m_index_sorted--;
			int temp_index_value = sorted_count_P[this_index_sorted].m_index_value;
			sorted_count_P[this_index_sorted].m_index_value = sorted_count_P[this_index_sorted + 1].m_index_value;
			sorted_count_P[this_index_sorted + 1].m_index_value = temp_index_value;
			int temp_index_count_posi = sorted_count_P[this_index_sorted].m_count_posi;
			sorted_count_P[this_index_sorted].m_count_posi = sorted_count_P[this_index_sorted + 1].m_count_posi;
			sorted_count_P[this_index_sorted + 1].m_count_posi = temp_index_count_posi;
			this_index_sorted++;
		}
		while (this_index_sorted > 0)
		{
			if (sorted_count_P[this_index_sorted].m_count_posi >= sorted_count_P[this_index_sorted - 1].m_count_posi)
				break;
			count_P[f_index_value].m_index_sorted--;
			count_P[sorted_count_P[this_index_sorted - 1].m_index_value].m_index_sorted++;
			int temp_index_value = sorted_count_P[this_index_sorted].m_index_value;
			sorted_count_P[this_index_sorted].m_index_value = sorted_count_P[this_index_sorted - 1].m_index_value;
			sorted_count_P[this_index_sorted - 1].m_index_value = temp_index_value;
			int temp_index_count_posi = sorted_count_P[this_index_sorted].m_count_posi;
			sorted_count_P[this_index_sorted].m_count_posi = sorted_count_P[this_index_sorted - 1].m_count_posi;
			sorted_count_P[this_index_sorted - 1].m_count_posi = temp_index_count_posi;
			this_index_sorted--;
		}
	}
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
	clausesHead[index_clause].count_activeValue++;
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
	AddCountAppear(index_value);
	AddCountPoN(index_value , new_value->isNegative);
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
		struct ValueNode* new_value = CreateNewValueNode( isNegative, index_value,index_clause);
		AddNextValue_of_Clause(index_clause, new_value);
		AddNextValue_of_Value(index_value, new_value);
	}
	
}
void ReadCNF(char t)
{
	if (t != 'p')
		return;
	char str[10] = "";
	MyGetString(str);
	//scanf("%s", str);
	if (str[0] != 'c')
		return;
	MyGetInt(&count_value);
	MyGetInt(&count_clause);
	//scanf("%d%d", &count_value, &count_clause);
	count_active_Value = count_value;
	index_lastSelected = 0;
	/*values = malloc(sizeof(struct ValueHeadNode) * (count_value + 1));
	if (!values)
		return;
	clauses = malloc(sizeof(struct ValueHeadNode) * (count_clause + 1));
	if (!clauses)
		return;*/
	for (int i = 0; i <= count_value; i++)
	{
		count_P[i].m_index_sorted = i;
		count_P[i].m_count_nega = count_P[i].m_count_posi = count_P[i].m_index_value = -9999;
		sorted_count_P[i].m_count_nega = sorted_count_P[i].m_count_posi = 0;
		sorted_count_P[i].m_index_value = i;
		sorted_count_P[i].m_index_sorted = -9999;

		count_N[i].m_index_sorted = i;
		count_N[i].m_count_nega = count_P[i].m_count_posi = count_P[i].m_index_value = -9999;
		sorted_count_N[i].m_count_nega = sorted_count_N[i].m_count_posi = 0;
		sorted_count_N[i].m_index_value = i;
		sorted_count_N[i].m_index_sorted = -9999;

		count_valueAppear[i].m_index_sorted = i;
		count_valueAppear[i].m_count = count_valueAppear[i].m_index_value = -9999;
		sorted_count_valueAppear[i].m_count = 0;
		sorted_count_valueAppear[i].m_index_value = i;
		sorted_count_valueAppear[i].m_index_sorted = -9999;

		valuesHead[i].m_truth = 0;
		valuesHead[i].m_weight = 200;
		valuesHead[i].nextValue_in_value = NULL;
		//valuesHead[i].valueSpeciallyInValueHead = NULL;
		//valuesHead[i].latestValue_in_value = valuesHead[i].valueSpeciallyInValueHead;
		valuesHead[i].latestValue_in_value = NULL;
	}
	for (int i = 0; i < count_clause; i++)
	{
		clausesHead[i].count_activeValue = 0;
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
void ReadValue()
{
	for (int i = 1; i <= count_value; i++)
	{
		char t[10];
		MyGetString(t);
		if (t[0] == '-')
		{
			valuesHead[i].m_truth = -1;
		}
		else if (t[0] == '1')
		{
			valuesHead[i].m_truth = 1;
		}
		else
		{
			valuesHead[i].m_truth = 0;
		}
	}
}
bool CheckValue()
{
	for (int i = 0; i < count_clause; i++)
	{
		bool isTrueClause = false;
		struct ValueNode* this_value_in_clause = clausesHead[i].nextValue_in_clause;
		while (this_value_in_clause)
		{
			if (XOR(this_value_in_clause->isNegative, valuesHead[this_value_in_clause->m_value].m_truth))
			{
				isTrueClause = true;
				break;
			}
			this_value_in_clause = this_value_in_clause->nextValue_in_clause;
		}
		if (!isTrueClause)
		{
			printf("\n*** 不核里解");
			return false;
		}
	}
	printf("\n*** 核里解");
	return true;
}