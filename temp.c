//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include "theTools.h"

#define MaxD 3000
#define MaxI 30

int discount = 0, depth = 0;
char /*data[MaxL][MaxI] = { 0 }, */path[] = "";

void findAndChange()
{
	char cache[100] = "", *x, num[7] = "";
	int price;

	while (fgets(cache, MaxL, inf) != NULL)
	{
		switch (findStr(cache))
		{
			case 1://Price="（数字）"
				if (discount >= 0)
				{
					x = strchr(cache, '\"');
					strcpy(num, x + 1);
					price = atoi(num);
					price = price * discount / 100;
					itoa(price, num, 10);
					strcpy(x + 1, num);
					strcat(cache, "\"\n");
				}
				break;
			case 2://UnlockByExploration="false"（或true）
				x = strchr(cache, '=');
				strcpy(x, "=\"false\"\n");
				break;
			case 3://UnlockByRank="1"
				x = strchr(cache, '=');
				strcpy(x, "=\"1\"\n");
				break;
		}
		fputs(cache, ouf);
	}
}

void toChange(char fileName[])
{
	inf = fopen(fileName, "r");
	if (needChange(fileName))
		backupAndPrepareNew(fileName);
	else
		return;

	findAndChange();

	fclose(inf);
	fclose(ouf);

	system("pause");
}

int checkFolder()
{
	char data[MaxD];
	const char prefix[] = "classes\n_dlc\n_templates\n";

	getCmd("dir /a:d /b", data);
	if (!strcmp(data, prefix)) return(1);
	else return(0);
}

void searchAndChange(char currPath[])
{
	char data[MaxD], fileName[MaxL], names[MaxL][MaxI], str[MaxL * MaxI];
	int i, count;
	const char cmd[] = "dir ";
	const char cmd4folder[] = " /a:d /b";
	const char cmd4file[] = " *.xml /a:-d /b";
	const char f404[] = "File Not Found\n";
	const char F404[] = "找不到文件\n";

	depth++;

	//for all files
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4file);
	getCmd(str, data);
	if (strcmp(data, f404) && strcmp(data, F404))
	{
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
		}

	}

	//for all folders
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4folder);
	getCmd(str, data);
	if (strcmp(data, f404) && strcmp(data, F404))
	{
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
			searchAndChange(str);
		}
	}
	depth--;
}

int main(int argc, char *argv[])
{
	printf("Would like a discount?\n");
	printf("\nInput an integer for percent and press ENTER.\n");
	printf("For example:\n90\nmeans the price will be 90%% of before.\n");
	printf("An item of price 5000 will be change into 4500.\n");
	printf("\n0 (zero) will make everything free.\n");
	printf("\nNegative number means no discount needed.\n");
	printf("(The original price will not be modified.)\n");
	scanf("%d", &discount);

	char fileName[100] = "gearboxes_scouts.xml";

	//if (argc > 1)
	//{
	//	strcpy(fileName, argv[1]);
	//	strcpy(fileName, strrchr("\\", fileName) + 1);
	//	toChange(fileName);
	//}
	//else
	if (checkFolder())
	{
		printf("Wrong folder!\n");
		return -1;
	}

	searchAndChange(path);

	return 0;
}

/*
第一阶段：
遍历每一个文件夹，并且搜索每一个xml文件，发现有
			Price="（数字）"
			UnlockByExploration="false"（或true）
就把路径、文件名输出到屏幕上
如果发现
			UnlockByRank="1"
但rank不等于1，把路径、文件名输出到屏幕上

第二阶段：
修改对应的值，并且把修改前的文件扩展名改成.bak
提供选项把价格改成x折
			*/

/*
	getCmd("dir /a:d /b", data);
	strcat(currDir, data);
	printf("%s", data);*/


	/*getCmd("dir gearboxes\\*.xml /b", res);
	printf("data1:\n%s\n", res);
	separate(res, fileName, 10);*/
