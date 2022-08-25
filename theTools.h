#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxL 100

void getCmd(const char cmd[], char resp[])
{
	char buf[1024] = "";
	FILE *fp = _popen(cmd, "r");

	while (fgets(buf, sizeof(buf), fp))
		strcat(resp, buf);

	_pclose(fp);
}

int separate(char src[], char dst[], char x)
{
	int len = strlen(src), i, s;

	for (i = 0; src[i] != x; i++)
		dst[i] = src[i];
	dst[i] = 0;
	s = i + 1;

	//for (i = 0; i < len; i++)
	//	src[i] = src[i + s];
	strcpy(src, src + s);

	return s;
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

	//for (j = 0; j < len; j++) str[j] = src[i + j];
	strcpy(str, src + i);

	if (!strncmp(str, a, strlen(a))) return(1);
	if (!strncmp(str, b, strlen(b))) return(2);
	if (!strncmp(str, c, strlen(c))) return(3);

	return(0);
}

int needChange(char fname[])
{
	char cache[100] = "";
	int r = 0;
	FILE *inf = fopen(fname, "r");

	while (fgets(cache, MaxL, inf) != NULL)
		if (findStr(cache))
		{
			r = 1;
			fclose(inf);
		}
	fclose(inf);
	return(r);
}

int strfchr(char src[], char c)
{
	int len = strlen(src), i;

	//for (i = 0; i < len; i++)
	//	if (src[i] == c) return(i);
	return((int) src - (int) strchr(src, '='));

	return(-1);
}

#endif