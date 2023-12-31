#include"Definition.h"
#include "HaniddokuC.h"
int count_1 = 0, count_num = 0,index_num = 0;
char temp[100];
//读入数字前的初始约束10597行
void OutPut_Initialize()
{
	int nums_in_line[10];
	int count_nums_in_line = 0;
	int shortest = N / 2 + 1;//最短边的长度 N = 9  =>  shortest = 5
	for (int index_direction = 0; index_direction < 3; index_direction++)
	{
		for (int index_line = 1; index_line <= 9; index_line++)
		{
			for (int line = 1; line <= N; line++)
			{
				int column = 1;
				if (line <= shortest)
				{
					column = shortest - line + 1;
					for (; column <= N; column++)
					{
						int temp_index_num = CollectLine(index_direction, index_line, line, column);
						if (temp_index_num != -1)
						{
							nums_in_line[count_nums_in_line] = temp_index_num;
							count_nums_in_line++;
						}
					}
				}
				else
				{
					for (; column <= N - (line - shortest); column++)
					{
						int temp_index_num = CollectLine(index_direction, index_line, line, column);
						if (temp_index_num != -1)
						{
							nums_in_line[count_nums_in_line] = temp_index_num;
							count_nums_in_line++;
						}
					}
				}
			}
			OutPut_Exclude_NumInLine(nums_in_line, count_nums_in_line);
			//查看这一行的数字编码
			/*for (int i = 0; i < count_nums_in_line; i++)
			{
				printf("%d ", nums_in_line[i]);
			}
			printf("\n");*/
			count_nums_in_line = 0;
		}
	}
	for (int line = 1; line <= N; line++)
	{
		int column = 1;
		if (line <= shortest)
		{
			column = shortest - line + 1;
			for (; column <= N; column++)
			{
				OutPut_Exclude_NumInGrid(line,column);
			}
		}
		else
		{
			for (; column <= N - (line - shortest); column++)
			{
				OutPut_Exclude_NumInGrid(line, column);
			}
		}
	}
}
//约束: 每个格子有且仅有一个数字
void OutPut_Exclude_NumInGrid(int line, int column)
{
	int temp_out = line * 100 + column * 10;
	count_1++;
	for (int candidate = 1; candidate <= 9; candidate++)		//每个格子至少在9个候选数中填一个
	{
		fprintf(fp_OutPut_CNF_of_Sodoku,"%d ", temp_out + candidate);
	}
	fprintf(fp_OutPut_CNF_of_Sodoku,"0\n");
	for (int i = 1; i < 9; i++)
	{
		for (int j = i + 1; j < 10; j++)						//组合数C9|2 → 每个格子不能同时填两个数字
		{
			count_1++;
			fprintf(fp_OutPut_CNF_of_Sodoku,"-%d -%d 0\n", temp_out + i , temp_out +j);
		}
	}
}
//约束: 每一行的连续数字
void OutPut_Exclude_NumInLine(int nums_in_line[10], int count_nums_in_line)
{
	
	for (int i = 0; i < count_nums_in_line - 1; i++)
	{
		for (int j = i + 1; j < count_nums_in_line; j++)
		{
			//一行任意两个不重复
			for (int candidate = 1; candidate <= 9; candidate++)
			{
				count_1++;
				//fprintf(fp_OutPut_CNF_of_Sodoku, "%d : ", count_1);
				fprintf(fp_OutPut_CNF_of_Sodoku,"-%d -%d 0\n",  nums_in_line[i]+ candidate, nums_in_line[j] + candidate);
			}
			//差值限定不超过 (这行数字的个数-1)
			for (int candidate_1 = 1; candidate_1 <= 9; candidate_1++)
			{
				for (int candidate_2 = 1; candidate_2 <= 9; candidate_2++)
				{
					if(candidate_2 == candidate_1)
						continue;
					int delta = candidate_1 > candidate_2 ? candidate_1 - candidate_2 : candidate_2 - candidate_1;
					if (delta >= count_nums_in_line)
					{
						count_1++;
						//fprintf(fp_OutPut_CNF_of_Sodoku, "%d : ", count_1);
						fprintf(fp_OutPut_CNF_of_Sodoku,"-%d -%d 0\n", nums_in_line[i] + candidate_1, nums_in_line[j] + candidate_2);
					}
				}
			}
		}
	}

}
//约束: 填入已知数
void OutPut_SingleGrid_while_Input(int x, int y, int value)
{
	//int direction[3] = { x,y,x + y - 1 };//将map中的坐标x,y 转换为三个方向上的行序号
	int temp_out = x * 100 + y * 10 + value;
	//printf("%d 0\n", temp_out);
	fprintf(fp_OutPut_CNF_of_Sodoku, "%d 0\n", temp_out);
}
//将这行里的格子坐标收集到数组中
int CollectLine(int index_direction, int index_line, int x, int y)
{
	int temp_out = x * 100 + y * 10;
	switch (index_direction)
	{
	case 0:
	{
		if (index_line == x)
			return temp_out;
		break;
	}
	case 1:
	{
		if (index_line == y)
			return temp_out;
		break;
	}
	case 2:
	{
		if (index_line == (x + y - 5))
			return temp_out;
		break;
	}
	default:
		break;
	}
	return -1;
}
//临时在txt中getchar到char数组
void MyGetchar_Try(int x, int y)//getchar读取单个数字
{
	fscanf(fp_InPut_Sodoku, "%c", &temp[index_num]);
	if (temp[index_num] == '0')
		return;
	count_num++;
}
//在char数组中getchar
void MyGetchar(int x, int y)//getchar读取单个数字
{
	if (temp[index_num] == '0')
		return;
	OutPut_SingleGrid_while_Input(x, y, (int)temp[index_num] - '0');
}
//临时读取并保存已知数个数
void TryInPutNum()
{
	index_num = 0;
	int shortest = N / 2 + 1;//最短边的长度 N = 9  =>  shortest = 5
	for (int line = 1; line <= N; line++)
	{
		int column = 1;
		if (line <= shortest)
		{
			column = shortest - line + 1;
			for (; column <= N; column++)
			{
				MyGetchar_Try(line, column);
				index_num++;
			}
			continue;
		}
		for (; column <= N - (line - shortest); column++)
		{
			MyGetchar_Try(line, column);
			index_num++;
		}
	}
}
//读取已保存的已知数
void InputNum()
{
	index_num = 0;
	int shortest = N / 2 + 1;//最短边的长度 N = 9  =>  shortest = 5
	for (int line = 1; line <= N; line++)
	{
		int column = 1;
		if (line <= shortest)
		{
			column = shortest - line + 1;
			for (; column <= N; column++)
			{
				MyGetchar(line, column);
				index_num++;
			}
			continue;
		}
		for (; column <= N - (line - shortest); column++)
		{
			MyGetchar(line, column);
			index_num++;
		}
	}
}
//数独61位数 → cnf
void Convert_Sodoku_to_CNF()
{
	fp_InPut_Sodoku = fopen(position_InPut_Sodoku, "r");
	fp_OutPut_CNF_of_Sodoku = fopen(position_OutPut_Sodoku_CNF, "w");
	strcpy(temp, "");
	TryInPutNum();
	fprintf(fp_OutPut_CNF_of_Sodoku, "p cnf 1000 %d\n", 10597+count_num);//10597+n
	OutPut_Initialize();
	InputNum();
	//printf("%d", count_1);
	fclose(fp_InPut_Sodoku);
	fclose(fp_OutPut_CNF_of_Sodoku);
}
//cnf → 数独61位数
void Convert_CNF_to_Sodoku()
{
	fp_OutPut_Sodoku = fopen(position_OutPut_Sodoku, "w");
	int accumulate = 0;
	for (int i = 150; i <= 960; i++)
	{
		if (valuesHead[i].m_truth == 0)
		{
			accumulate = 0;
			continue;
		}
		accumulate++;
		if (valuesHead[i].m_truth == 1)
			fprintf(fp_OutPut_Sodoku, "%d", accumulate);
	}
	fclose(fp_OutPut_Sodoku);
}