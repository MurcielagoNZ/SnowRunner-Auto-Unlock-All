#include "theTools.h"

int depth = 0, i;
char name[MaxP] = "";

const char cmd[] = "dir ";
const char cmd4folder[] = " /a:d /b";
const char cmd4file[] = " *.xml /a:-d /b";

void searchAndChange(char currPath[])
{
	char data[MaxP * MaxI] = "",
		fileName[MaxP] = "",
		names[MaxP][MaxI] = { 0 },
		str[MaxP] = "";
	int i, count;

	depth++;

	printf("Now working with path:\n%s\nDepth: %d\n\n", currPath, depth);

	//for all files
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4file);
	getCmd(str, data);
	if (notEmpty(data))
	{
		//printf("Found files:\n%s\n", data);
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
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4folder);
	getCmd(str, data);
	if (notEmpty(data))
	{
		//printf("Found folders:\n%s\n", data);
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
			if (whiteFolder(names[i])) searchAndChange(str);
			else delDir(str);
		}
	}
	else printf("No folders found.\n\n");

	depth--;
}

int main(int argc, char *argv[])
{
	printf("Would like a discount?\n");
	printf("\nInput an integer for percent and press ENTER.\n");
	printf("For example:\n90\nmeans the price will be 10%% off.\n");
	printf("An item of price 5000 will be change into 4500.\n");
	printf("\n0 (zero) will make everything free.\n");
	printf("\nNegative number means no discount needed.\n");
	printf("(The original price will not be modified.)\n");
	scanf("%d", &discount);
	//test
	//discount = 0;

	if (argc > 1)
	{
		printf("Working with given file.\n");

		for (i = 1; i < argc; i++)
		{
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
	else
		if (checkNotFolder())
		{
			printf("Wrong folder!\n");
			system("pause");
			return -1;
		}
		else
		{
			printf("Searching folders.\n");
			searchAndChange("[media]");//test
			//searchAndChange("");
		}

	printf("All done. Changed %d files.\n", count);
	//system("pause");
	return 0;
}
