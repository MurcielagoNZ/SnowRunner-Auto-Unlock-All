#define _CRT_SECURE_NO_WARNINGS

#include "theTools.h"

const char cmd[] = "dir ";
const char cmd4folder[] = " /a:d /b";
const char cmd4file[] = " /a:-d *.xml /b";

int depth = 0, i;
char name[MaxP] = "";

void searchAndChange(char currPath[])
{
	char data[MaxP * MaxI] = "",
		names[MaxP][MaxI] = { 0 },
		str[MaxP] = "";
	int i, count;

	depth++;

	printf("Now working with path:\n%s\nDepth: %d\n\n", currPath, depth);

	//for all files
	memset(str, 0, sizeof(str));
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4file);
	getCmd(str, data);
	if (notEmpty(data))
	{
		printf("Found files:\n%s\n", data);
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
			toChangeFile(str);
		}
	}
	else printf("No files found.\n\n");

	//for all folders
	memset(str, 0, sizeof(str));
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4folder);
	getCmd(str, data);
	if (notEmpty(data))
	{
		printf("Found folders:\n%s\n", data);
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			memset(str, 0, sizeof(str));
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
			if (whiteFolder(names[i]))
				searchAndChange(str);
			else delDir(str);
		}
	}
	else printf("No folders found.\n\n");

	depth--;
}

int main()
{
	printf("该工具会帮你解锁物品的地区、级别限制，并让需要探索才能解锁的物品直接可用。\n新增了全轮驱动和焊死差速器功能。\n");
	printf("This tool will unlock everything.\nAWD-modify and differential-welde feature were added.\n\n");
	printf("想打折嘛？\n");
	printf("输入一个整数作为百分数并且按下【回车】。若不想打折，请输入负数。\n");
	printf("例如：\n90\n会将所有物品的价格打九折。\n");
	printf("原价5000的物品会变为4500。\n");
	printf("0（零）开启零元购。\n");
	printf("Would like a discount?\n");
	printf("Input an integer for percent and press ENTER. If don't want discount, input negative number.\n");
	printf("For example:\n90\nmeans the price will be 10%% off.\n");
	printf("An item of price 5000 will be change into 4500.\n");
	printf("0 (zero) will make everything free.\n");
	scanf("%d", &discount);
	printf("\n将所有卡车设置为全轮驱动吗？ (1 - 是; 0 - 否)\n");
	printf("Give all trucks AWD? (1 - yes; 0 - no)\n");
	scanf("%d", &AWD);
	printf("\n将所有不支持差速锁的卡车设置为差速锁常锁吗？ (1 - 是; 0 - 否)\n");
	printf("Give all trucks differential lock? (1 - yes; 0 - no)\n");
	scanf("%d", &difflock);
	system("cls");

	//debug
	//log = fopen("files_changed.log", "w");

	/*if (argc > 1)
		{
			printf("Working with given file.\n");

			for (i = 1; i < argc; i++)
			{
				memset(name, 0, sizeof(name));
				strcpy(name, argv[i]);
				if (needChange(name))
				{
					printf("Working with:\n%s\n\n", name);
					backupAndPrepareNew(name);
					toChangeFile(name);
				}
			}

			system("pause");
			return 0;
		}
		else*/
	if (checkNotFolder())
	{
		printf("Wrong folder!\n");
		system("pause");
		return -1;
	}
	else
	{
		printf("Searching folders.\n");
		searchAndChange("[media]");
	}

	system("del /s *.bak > nul");
	printf("All done. Changed %d files.\n", count);
	system("pause");

	//debug
	//fprintf(log, "%d\n", count);
	//fclose(log);

	return 0;
}

/*
* need manual change cuz format error:
* dlc6 step_3364_crocodile
* dlc8 step_39331_pike
*
* Offset="(从车辆中心+前-后; 从地面+上-下; 从车辆中心+左-右)"
*/