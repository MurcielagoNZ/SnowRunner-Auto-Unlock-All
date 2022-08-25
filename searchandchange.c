#include "theTools.h"

#define MaxD 3000
#define MaxI 30

int discount = 0, depth = 0, i;
char name[MaxL] = "";

void searchAndChange(char currPath[])
{
	char data[MaxD], fileName[MaxL], names[MaxL][MaxI], str[MaxL * MaxI];
	int i, count;

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
			toChangeFile(fileName);
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

	if (argv > 1)
	{
		for (i = 1; i < argc; i++)
		{
			strcpy(name, argv[i]);
			backupAndPrepareNew(name);
			if (needChange(name))
				toChangeFile(name);
		}

		return 0;
	}
	else
		if (checkFolder())
		{
			printf("Wrong folder!\n");
			return -1;
		}
		else
			searchAndChange("");

	return 0;
}
