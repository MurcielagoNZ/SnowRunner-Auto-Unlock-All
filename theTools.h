#ifndef tTools
#define tTools

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxL 100

FILE *inf, *ouf;

//run cmd command and put feedback into string resp
void getCmd(const char cmd[], char resp[])
{
	char buf[1024] = "";
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
int separate(char src[], char dst[], char x)
{
	int len = strlen(src), i = 0, pos;

	memset(dst, 0, sizeof(dst));
	while ((pos = strfchr(src, 10)) != -1)
	{
		strncpy(dst + i * MaxL, src, pos);
		strcpy(src, src + pos + 1);
		i++;
	}
	return i;
}

int findStr(char src[])
{
	int len = strlen(src), i, j;
	if (!len) return(0);

	char str[100] = "";

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
	char cache[100] = "";
	int r = 0;
	FILE *inf = fopen(fileName, "r");

	while (fgets(cache, MaxL, inf) != NULL)
		if (findStr(cache)) r = 1;
	fclose(inf);
	return(r);
}

void backupAndPrepareNew(char fileName[])
{
	char bakfile[100] = "";
	char command[100] = "copy /-y ";

	strncpy(bakfile, fileName, strlen(fileName) - 3);
	strcat(bakfile, "bak");
	strcat(command, fileName);
	strcat(command, " ");
	strcat(command, bakfile);
	system(command);
	inf = fopen(bakfile, "r");
	ouf = fopen(fileName, "w");
}

#endif
