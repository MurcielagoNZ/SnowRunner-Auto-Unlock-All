#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "theTools.h"

//char res[1000], path[100];
int discount = 0;
FILE *inf, *ouf;

void backupAndPrepareNew(char fname[])
{
	char bakfile[100] = "";
	char command[100] = "copy /-y ";

	strncpy(bakfile, fname, strlen(fname) - 3);
	strcat(bakfile, "bak");
	strcat(command, fname);
	strcat(command, " ");
	strcat(command, bakfile);
	system(command);
	inf = fopen(bakfile, "r");
	ouf = fopen(fname, "w");
}

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

void changeGiven(char fname[])
{
	inf = fopen(fname, "r");
	if (needChange(fname))
		backupAndPrepareNew(fname);
	else
		return;

	findAndChange();

	fclose(inf);
	fclose(ouf);

	system("pause");
}

void searchAndChange()
{

}

void main(int argc, char *argv[])
{
	printf("Would like a discount?\n");
	printf("Integer for percent, for example:\n90\nmeans the price will be 90%% of before.\n");
	printf("An item of price 5000 will be change into 4500.\n");
	printf("0 (zero) will make everything free.\n");
	printf("Negative number means no discount needed.\n");
	printf("(The original price will not be modified.)\n");
	scanf("%d", &discount);

	char fname[100] = "gearboxes_scouts.xml";

	if (argc > 1)
	{
		strcpy(fname, argv[1]);
		strcpy(fname, strrchr("\\", fname) + 1);
		changeGiven(fname);
	}
	else
		searchAndChange();
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
	separate(res, fname, 10);*/