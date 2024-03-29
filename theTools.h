#ifndef tTools
#define tTools

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxI 1024 //max items
#define MaxL 1280 //max string length
#define MaxP 4096 //max path length
#define MaxD 16896 //max data size

int discount = -1, difflock = 0, count = 0;
FILE* inf, * ouf;

//debug
FILE* log;

#define BFC 23

const char blkFolders[BFC][25] =
{
	"_templates",
	"addons_category",
	"ambients",
	"cameras",
	"cargo_types",
	"customization_presets",
	"daytimes",
	"driver_characters",
	"editor",
	"env",
	"grass",
	"media_data_types",
	"models",
	"mud",
	"overlays",
	"particles",
	"plants",
	"skies",
	"sounds",
	"terrain_layers",
	"waters",
	"weather",
	"zones"
};
const char
Torque[] = "Torque=\"none\"\n",
Country[] = "Country=",
DiffLockType[] = "DiffLockType=\"None\"\n",
UnlockByExploration[] = "UnlockByExploration=",
Price[] = "Price=",
UnlockByRank[] = "UnlockByRank=";

const char f404[] = "File Not Found\n";
const char F404[] = "找不到文件\n";


//run cmd command and put feedback into string resp
void getCmd(const char cmd[], char resp[])
{
	char buf[MaxD] = "";
	FILE* fp = _popen(cmd, "r");

	while (fgets(buf, sizeof(buf), fp))
		strcat(resp, buf);

	_pclose(fp);
}

int strfchr(char src[], char c)
{
	int len = strlen(src);

	if (!len) return(-1);
	return((int)strchr(src, c) - (int)strchr(src, src[0]));
}

//break string src into array of strings by char x
int separate(char src[], char dst[MaxP][MaxI], char x)
{
	int i = 0, pos;

	while ((pos = strfchr(src, x)) != -1)
	{
		memset(dst[i], 0, sizeof(dst[i]));
		strncpy(dst[i], src, pos);
		strcpy(src, src + pos + 1);
		i++;
	}

	return i;
}

int findStr(char src[])
{
	int len = strlen(src), i;
	if (!len) return(0);

	char str[MaxL] = "";

	for (i = 0; i < len && (32 == src[i] || '\t' == src[i]); i++);

	memset(str, 0, sizeof(str));
	strcpy(str, src + i);

	if (!strncmp(str, Country, strlen(Country)))
		return(1);
	if (!strncmp(str, Price, strlen(Price)))
		return(2);
	if (!strncmp(str, UnlockByExploration, strlen(UnlockByExploration)))
		return(3);
	//if (!strncmp(str, UnlockByRank, strlen(UnlockByRank)))
	//	return(4);
	if (!strcmp(str, Torque))
		return(5);
	if (!strcmp(str, DiffLockType))
		return(6);

	return(0);
}

//to see if the file needs to be changed
int needChange(char fileName[])
{
	char cache[MaxL] = "";
	FILE* inf = fopen(fileName, "r");

	while (fgets(cache, sizeof(cache), inf) != NULL)
		if (findStr(cache))
		{
			fclose(inf);
			return(1);
		}
	fclose(inf);
	return(0);
}

void backupAndPrepareNew(char fileName[])
{
	char bakFile[MaxL] = "",
		command[MaxP] = "";

	strncpy(bakFile, fileName, strlen(fileName) - 3);
	strcat(bakFile, "bak");

	strcat(command, " copy ");
	strcat(command, fileName);
	strcat(command, " ");
	strcat(command, bakFile);
	system(command);

	inf = fopen(bakFile, "r");
	ouf = fopen(fileName, "w");

}

void findAndChangeData(FILE* inf, FILE* ouf)
{
	char cache[MaxL] = "", * x, num[MaxL] = "";
	int price;

	while (fgets(cache, sizeof(cache), inf) != NULL)
	{
		switch (findStr(cache))
		{
		case 1://Country
			strcpy(cache, "\t\tCountry=\"\"\n");
			break;
		case 2://Price
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
		case 3://UnlockByExploration
			strcpy(cache, "\t\tUnlockByExploration=\"false\"\n");
			break;
		case 4://UnlockByRank
			strcpy(cache, "\t\tUnlockByRank=\"1\"\n");
			break;
		case 5://Torque="none"
			strcpy(cache, "\t\t\tTorque=\"default\"\n");
			break;
		//case 6://DiffLockType="none"
		//	strcpy(cache, "\t\t\t =\"default\"\n");
		//	break;
		}
		fputs(cache, ouf);
	}
}

void toChangeFile(char fileName[])
{
	char command[MaxP] = "del ";

//	if (needChange(fileName))
	if (1)
	{
		//debug
		fprintf(log, "%s\n", fileName);

		count++;
		system("cls");
		printf("File No.%d\n", count);
		backupAndPrepareNew(fileName);
		printf("Now changing:\n%s\n\n", fileName);
		findAndChangeData(inf, ouf);
		fclose(inf);
		fclose(ouf);
	}
	else
	{
		system("cls");
		printf("No need to change file:\n%s\n\n", fileName);//test
		strcat(command, fileName);
		system(command);
	}
}

int checkNotFolder()
{
	char data[MaxP] = "";

	getCmd("dir /a:d /b", data);
	return(0);
}

int notEmpty(char data[])
{
	return(strlen(data) && strcmp(data, f404) && strcmp(data, F404));
}

int whiteFolder(char name[])
{
	int i;

	for (i = 0; i < BFC; i++)
		if (!strcmp(name, blkFolders[i]))
			return(0);
	return(1);
}

void delDir(char path[])
{
	char command[MaxP] = "rd /s /q \"";

	strcat(command, path);
	strcat(command, "\"");
	system(command);
}

#endif
