#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <io.h>
#include <locale.h>
#include "hash.h"
#include <fstream>

char* ReadFile (char *FileName, int* FileLength);
char* ReadWord (char* text, char** pointer);
int	  Hash	   (char* text, int FileLength, unsigned int(*HashFunc) (Data_t* Data), char* OutputFile);
int   PrintFile(char* OuputFile, Hash_t* HashTab);


#define HASHFUNC HashFunc_1

int main()
{
	setlocale(LC_ALL, "Russian");

	int FileLength = 0;

	char* text = ReadFile("Text.txt", &FileLength);

	Hash(text, FileLength, HASHFUNC, "1.csv");

	printf("\nok\n");
	
	return 0;
}

char* ReadFile(char* FileName, int* FileLength)
{
	FILE* in = fopen(FileName, "r");

	assert(in);

	*FileLength = filelength(fileno(in));

	char* text = (char*)calloc(*FileLength, sizeof(char));
	assert(text);

	fread(text, *FileLength, sizeof(char), in);

	fclose(in);

	return text;
}


char* ReadWord(char* text, char** buffer)
{

	assert(text);
	assert(buffer);

	char* word = *buffer;

	if (**buffer == '\0') return NULL;

	while (isalpha(**buffer))
	{
		**buffer = tolower(**buffer);
		(*buffer)++;
	}
	**buffer = '\0';
	(*buffer)++;

	return word;

}

int Hash(char* text, int FileLength, unsigned int(*HashFunc) (Data_t* Data), char* OutputFile)
{
	
	assert(text);
	assert(HashFunc);
	assert(OutputFile);

	Hash_t HashTab = {};
	HashTab_ctor(&HashTab, HashFunc);

	char* buf = (char*)calloc(FileLength, sizeof(char));
	assert(buf);

	strcpy(buf, text);

	char** ptr = &(buf);
	char* word = ReadWord(buf, ptr);

	while (word)
	{
		AddElem(&HashTab, word);
		word = ReadWord(buf, ptr);
	}

	PrintFile(OutputFile, &HashTab);

	HashTab_dtor(&HashTab);
	free(buf);

	return 0;

}


int PrintFile(char* OuputFile, Hash_t* HashTab)
{
	FILE* out = fopen(OuputFile, "w");
	assert(out);

	for (int i = 0; i < MAX_TAB_SIZE; i++)
	{
		fprintf(out, "%d; ", (&(HashTab->List[i]))->number);
	}

	return 0;
}
