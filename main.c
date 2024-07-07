#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_INVALID_ARGS 0x01
#define EXIT_NO_READFILE 0x02
#define EXIT_NO_WRITEFILE 0x03 

int main(int argc, char** argv)
{
 	if (!(argc == 2))
	{
		fprintf(stderr, "Invalid arguments!\n");
		exit(EXIT_INVALID_ARGS);
	}

	printf("Opening: %s\n", argv[1]);
	int namesize = (int) strlen(argv[1]);

	int ch;
	int buffchar0, buffchar1;

	char* outfex = ".out";
	char inname[128];
	for (long int i = 0; i < namesize; i++)
	{
		*(inname + i) = argv[1][i];
	}
	*(inname + namesize) = '\0';

	char* outname = strcat(argv[1], outfex);

	int mode = 1;

	FILE* readfile = fopen(inname, "r");
	
	if (readfile == NULL)
	{
		fprintf(stderr, "Unable to read file!\n");
		exit(EXIT_NO_READFILE);
	}

	FILE* writefile = fopen(outname, "w");

	if (readfile == NULL)
	{
		fprintf(stderr, "Unable to read file!\n");
		exit(EXIT_NO_WRITEFILE);
	}

	printf("Output in: %s\n", outname);

	//printf("%c ", fgetc(readfile));
	//fputc('L', writefile);

	while((ch = fgetc(readfile)) != EOF)
	{
		//printf("%c", ch);
		if (ch == '/')
		{
			buffchar0 = fgetc(readfile);
			if (buffchar0 == '/')
			{
				mode = 2;
			}
			else if (buffchar0 = '*')
			{
				mode = 3;		
			}
		
		}
		
		if ((mode == 2) && ch == '\n')
		{
			mode = 1;
		
		}
		
		if ((mode == 3) && (ch == '*'))
		{
			buffchar1 = fgetc(readfile);
			if (buffchar1 == '/')
			{
				mode = 1;
				continue;
		
			}
		
		}
		
		if (mode == 1)
		{
			fputc(ch, writefile);
		}
	}

	fclose(readfile);
	fclose(writefile);
	printf("Success!!!\n");

	return 0;
}
