#ifndef tTools
#define tTools

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxI 512 //max items
#define MaxL 1024 //max string length
#define MaxP 2048 //max path length
#define MaxD 4096 //max data size

int discount = -1, count = 0;
FILE *inf, *ouf;

//run cmd command and put feedback into string resp
void getCmd(const char cmd[], char resp[])
{
	char buf[MaxD] = "";
	FILE *fp = _popen(cmd, "r");

	while (fgets(buf, sizeof(buf), fp))
		strcat(resp, buf);

	_pclose(fp);
}

int strfchr(char src[], char c)
{
	int len = strlen(src), i;

	if (!len) return(-1);
	return((int) strchr(src, c) - (int) strchr(src, src[0]));
}

//break string src into array of strings by char x
int separate(char src[], char dst[MaxP][MaxI], char x)
{
	int len = strlen(src), i = 0, pos;

	memset(dst, 0, sizeof(dst));
	while ((pos = strfchr(src, 10)) != -1)
	{
		strncpy(dst[i], src, pos);
		strcpy(src, src + pos + 1);
		if (strcmp(dst[i], "models")) i++;
	}

	return i;
}

int findStr(char src[])
{
	int len = strlen(src), i, j;
	if (!len) return(0);

	char str[MaxL] = "";

	const char a[] = "Price=";
	const char b[] = "UnlockByExploration=";
	const char c[] = "UnlockByRank=";

	for (i = 0; i < len && (32 == src[i] || '\t' == src[i]); i++);

	strcpy(str, src + i);

	if (!strncmp(str, a, strlen(a))) return(1);
	if (!strncmp(str, b, strlen(b))) return(2);
	if (!strncmp(str, c, strlen(c))) return(3);

	return(0);
}

//to see if the file needs to be changed
int needChange(char fileName[])
{
	char cache[MaxL] = "";
	int r = 0;
	FILE *inf = fopen(fileName, "r");

	while (fgets(cache, sizeof(cache), inf) != NULL)
		if (findStr(cache)) r = 1;
	fclose(inf);
	return(r);
}

void backupAndPrepareNew(char fileName[])
{
	char bakFile[MaxL] = "",
		command[MaxP] = "if not exist ",
		fileName4space[MaxL] = "\"",
		bakFile4space[MaxL] = "\"";

	strncpy(bakFile, fileName, strlen(fileName) - 3);
	strcat(bakFile, "bak");

	//deal with space
	if (strchr(fileName, 32))
	{
		strcat(fileName4space, fileName);
		strcat(fileName4space, "\"");
		strcpy(bakFile4space, bakFile);
		strcat(bakFile4space, "\"");

		strcat(command, bakFile4space);
		strcat(command, " copy ");
		strcat(command, fileName4space);
		strcat(command, " ");
		strcat(command, bakFile4space);
		system(command);
	}
	else
	{
		strcat(command, bakFile);
		strcat(command, " copy ");
		strcat(command, fileName);
		strcat(command, " ");
		strcat(command, bakFile);
		system(command);
	}

	//printf("Backup made.\n%s\n\n", bakFile);
	inf = fopen(bakFile, "r");
	ouf = fopen(fileName, "w");
}

void findAndChangeData(FILE *inf, FILE *ouf)
{
	char cache[MaxL] = "", *x, num[MaxL] = "";
	int price;

	while (fgets(cache, sizeof(cache), inf) != NULL)
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

		//printf("%s", cache);//test
	}
}

void toChangeFile(char fileName[])
{
	char command[MaxP] = "del ";

	if (needChange(fileName))
	{
		//test
		count++;
		printf("File No.%d\n", count);
		backupAndPrepareNew(fileName);
		printf("Now changing:\n%s\n\n", fileName);
		findAndChangeData(inf, ouf);
		fclose(inf);
		fclose(ouf);
	}
	else
	{
	//	printf("No need to change file:\n%s\n\n", fileName);//test
		strcat(command, fileName);
		system(command);
	}
}

int checkNotFolder()
{
	char data[MaxP] = "";
	const char prefix[] = "classes\n_dlc\n_templates\n";

	getCmd("dir /a:d /b", data);
	//test
	//return(0);
	return(strcmp(data, prefix));
}

int notEmpty(char data[])
{
	const char f404[] = "File Not Found\n";
	const char F404[] = "找不到文件\n";

	return(strlen(data, "") && strcmp(data, f404) && strcmp(data, F404));
}

#endif
