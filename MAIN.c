#include"Definition.h"
#include"CNF_Reader.h"
#include"Solver.h"
#include"Stack.h"
#include"HaniddokuC.h"
int MyPrintConsole()
{
	int option = -1;
	char t = '0';
	printf("\t\t-----------����DPLL��SAT�����------------\n");
	{//ѡ�����
		printf("\t\t*��ǰ���� : ");
		if (selection_strategy == -1)
			printf("δѡ��");
		else
			printf("%d", selection_strategy);
		printf("\n");
	}
	{//cnf·��
		printf("\t\t*��ǰcnf·�� : ");
		if (strlen(position_InPut_CNF) == 0)
			printf("δѡ��");
		else
			printf("%s", position_InPut_CNF);
		printf("\n");
	}
	
	printf("\n");
	printf("\t\t��ѡ�����(����0 - 3)\n");
	printf("\n");
	printf("\t\t1 : ���Ķ�ȡcnf��·��\n");
	printf("\t\t2 : ����DPLLѡ������Ĳ���\n");
	printf("\t\t3 : ��ʼDPLL\n");
	printf("\t\t 0 : �˳�\n");
	printf("\n");
	printf("\t\t����������:");
	scanf("%d", &option);
	switch (option)
	{
	case 0:
		printf("\n");
		printf("\t\t��лʹ��,�ݰ�!\n");
		return EXIT;
		break;
	case 1:
		printf("\n");
		printf("\t\t������cnf·��(�Զ�ɾ��˫����):");
		char t_string[1000] = "";
		scanf("%s", t_string);
		printf("\n");
		printf("\t\t·�����óɹ�!��Enter��������ҳ\n");
		{//�Զ�ɾ������˫����
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
		printf("\t\t��������Ա��(0 - 8) :");
		int t_int = -1;
		scanf("%d", &t_int);
		if (t_int < 0 || t_int > 8)
		{
			printf("\n");
			printf("\t\t�������ֲ��Ϸ�!��Enter��������ҳ\n");
		}
		else
		{
			printf("\n");
			printf("\t\t�������óɹ�!��Enter��������ҳ\n");
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
			printf("\t\tδ�����ȡ·��!��Enter��������ҳ\n");
			getchar();
			while ((t = getchar()) != '\n' && t != EOF);
			system("cls");
			return REPEAT;
		}
		else if (selection_strategy == -1)
		{
			printf("\n");
			printf("\t\tδѡ��DPLL����!��Enter��������ҳ\n");
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
		printf("\t\t�������ֲ��Ϸ�!��Enter��������ҳ\n");
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
		if (t_condition == EXIT)								//����̨����ֵ:�˳�ѭ��
			break;
		if (t_condition == REPEAT)								//����̨����ֵ:����ѭ��
			continue;
		//strcpy(position_InPut_CNF, "E:\\U\\DPLL\\Check\\3.cnf");//4��unsatisfied��
		//strcpy(position_InPut_CNF, "E:\\U\\DPLL\\Test\\��������\\M\\TEST.txt");
		//strcpy(position_InPut_CNF, "E:\\U\\DPLL\\OutPut_Sodoku_CNF.txt");
		strcpy(position_InPut_Sodoku, "E:\\U\\DPLL\\InPut_Sodoku.txt");
		strcpy(position_OutPut_Sodoku, "E:\\U\\DPLL\\OutPut_Sodoku.txt");
		strcpy(position_OutPut_Sodoku_CNF, "E:\\U\\DPLL\\OutPut_Sodoku_CNF.txt");
		strcpy(position_OutPut_Res, position_InPut_CNF);
		position_OutPut_Res[strlen(position_OutPut_Res) - 3] = 'r';
		position_OutPut_Res[strlen(position_OutPut_Res) - 2] = 'e';
		position_OutPut_Res[strlen(position_OutPut_Res) - 1] = 's';
		Convert_Sodoku_to_CNF();								//��61λ����.txt�ļ�ת����10597+n�е�.cnf

		bool isCheckValue = false;								//�Բ��Ƿ����,������ֵ(1 -1 0�б�)������cnfĩβ
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
				printf("��ɱ�����!\n");							//����̨����Ƿ����,���ڵ���
			}
			printf("time = %.0f ms\n", (double)(end - start) /*/ CLK_TCK*/);
			WriteRes(count_solution, (double)(end - start));	//�����ͬ·����ͬ��.res�ļ�
			fclose(fp_OutPut_Res);
		}
		fclose(fp_OutPut_Selection);
		
		printf("\n\t\t��Enter��������ҳ!");
		char t = '0';
		getchar();
		while ((t = getchar()) != '\n' && t != EOF);			//��ջ�����
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