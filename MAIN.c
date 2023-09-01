#include"Definition.h"
#include"CNF_Reader.h"
#include"Solver.h"
#include"Stack.h"
#include"HaniddokuC.h"
int MyPrintConsole()
{
	int option = -1;
	char t = '0';
	printf("\t\t-----------基于DPLL的SAT求解器------------\n");
	{//选择策略
		printf("\t\t*当前策略 : ");
		if (selection_strategy == -1)
			printf("未选择");
		else
			printf("%d", selection_strategy);
		printf("\n");
	}
	{//cnf路径
		printf("\t\t*当前cnf路径 : ");
		if (strlen(position_InPut_CNF) == 0)
			printf("未选择");
		else
			printf("%s", position_InPut_CNF);
		printf("\n");
	}
	
	printf("\n");
	printf("\t\t请选择操作(输入0 - 3)\n");
	printf("\n");
	printf("\t\t1 : 更改读取cnf的路径\n");
	printf("\t\t2 : 更改DPLL选择变量的策略\n");
	printf("\t\t3 : 开始DPLL\n");
	printf("\t\t 0 : 退出\n");
	printf("\n");
	printf("\t\t请输入数字:");
	scanf("%d", &option);
	switch (option)
	{
	case 0:
		printf("\n");
		printf("\t\t感谢使用,拜拜!\n");
		return EXIT;
		break;
	case 1:
		printf("\n");
		printf("\t\t请输入cnf路径(自动删除双引号):");
		char t_string[1000] = "";
		scanf("%s", t_string);
		printf("\n");
		printf("\t\t路径设置成功!按Enter键返回首页\n");
		{//自动删除多余双引号
			if (t_string[0] == '\"')
				strcpy(position_InPut_CNF, t_string + 1);
			else
				strcpy(position_InPut_CNF, t_string);
			if (position_InPut_CNF[strlen(position_InPut_CNF) - 1] == '\"')
				position_InPut_CNF[strlen(position_InPut_CNF) - 1] = '\0';
		}
		
		getchar();
		while ((t = getchar()) != '\n' && t != EOF);
		system("cls");
		return REPEAT;
		break;
	case 2:
		printf("\t\t请输入策略编号(0 - 8) :");
		int t_int = -1;
		scanf("%d", &t_int);
		if (t_int < 0 || t_int > 8)
		{
			printf("\n");
			printf("\t\t输入数字不合法!按Enter键返回首页\n");
		}
		else
		{
			printf("\n");
			printf("\t\t策略设置成功!按Enter键返回首页\n");
			selection_strategy = t_int;
		}
		getchar();
		while ((t = getchar()) != '\n' && t != EOF);
		system("cls");
		return REPEAT;
		break;
	case 3:
		if (strlen(position_InPut_CNF) == 0)
		{
			printf("\n");
			printf("\t\t未输入读取路径!按Enter键返回首页\n");
			getchar();
			while ((t = getchar()) != '\n' && t != EOF);
			system("cls");
			return REPEAT;
		}
		else if (selection_strategy == -1)
		{
			printf("\n");
			printf("\t\t未选择DPLL策略!按Enter键返回首页\n");
			getchar();
			while ((t = getchar()) != '\n' && t != EOF);
			system("cls");
			return REPEAT;
		}
		else
			return OK;
		break;
	default:
		printf("\n");
		printf("\t\t输入数字不合法!按Enter键返回首页\n");
		getchar();
		while ((t = getchar()) != '\n' && t != EOF);
		system("cls");
		return REPEAT;
		break;
	}
}
int main()
{
	selection_strategy = -1;
	strcpy(position_InPut_CNF, "");
	while (1)
	{
		int t_condition = MyPrintConsole();
		if (t_condition == EXIT)								//控制台返回值:退出循环
			break;
		if (t_condition == REPEAT)								//控制台返回值:继续循环
			continue;
		//strcpy(position_InPut_CNF, "E:\\U\\DPLL\\Check\\3.cnf");//4（unsatisfied）
		//strcpy(position_InPut_CNF, "E:\\U\\DPLL\\Test\\满足算例\\M\\TEST.txt");
		//strcpy(position_InPut_CNF, "E:\\U\\DPLL\\OutPut_Sodoku_CNF.txt");
		strcpy(position_InPut_Sodoku, "E:\\U\\DPLL\\InPut_Sodoku.txt");
		strcpy(position_OutPut_Sodoku, "E:\\U\\DPLL\\OutPut_Sodoku.txt");
		strcpy(position_OutPut_Sodoku_CNF, "E:\\U\\DPLL\\OutPut_Sodoku_CNF.txt");
		strcpy(position_OutPut_Res, position_InPut_CNF);
		position_OutPut_Res[strlen(position_OutPut_Res) - 3] = 'r';
		position_OutPut_Res[strlen(position_OutPut_Res) - 2] = 'e';
		position_OutPut_Res[strlen(position_OutPut_Res) - 1] = 's';
		Convert_Sodoku_to_CNF();								//将61位数的.txt文件转换成10597+n行的.cnf

		bool isCheckValue = false;								//自测是否成立,将变量值(1 -1 0列表)复制在cnf末尾
		fp_InPut_CNF = fopen(position_InPut_CNF, "r");
		ReadCNF(GetLine_Exclude_C());
		fclose(fp_InPut_CNF);
		if (isCheckValue)
		{
			ReadValue();
			CheckValue();
		}
		else
		{
			count_solution = 0;
			fp_OutPut_Res = fopen(position_OutPut_Res,"w");
			clock_t start, end;
			start = clock();
			DPLL();
			end = clock();
			if (count_solution == 0)
			{
				printf("绝杀，吴姐!\n");							//控制台输出是否成立,便于调试
			}
			printf("time = %.0f ms\n", (double)(end - start) /*/ CLK_TCK*/);
			WriteRes(count_solution, (double)(end - start));	//输出到同路径的同名.res文件
			fclose(fp_OutPut_Res);
		}
		fclose(fp_OutPut_Selection);
		
		printf("\n\t\t按Enter键返回主页!");
		char t = '0';
		getchar();
		while ((t = getchar()) != '\n' && t != EOF);			//清空缓冲区
		system("cls");
	}
	
	system("pause");
	return 0;
}
/*
c qw q
c wawa
p cnf 4 5
4 1 0
1 2 0
1 2 3 0
1 -3 0
2 -3 0
*/