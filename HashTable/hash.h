
#include <stdio.h>
#include "list.h"

const int MAX_HASH= 777;

struct HashTab
{
	List Lists[MAX_HASH];
	unsigned int(*HashFunc) (Data* Data);
};


int HashTab_ctor(HashTab* HashTab, unsigned int(*HashFunc) (Data* Data));
int HashTab_dtor(HashTab* HashTab);
int Search(List* List, const Data* Data);
int CompareChar(ListElem* Elem, const char* Data);
int HashTab_OK(HashTab* HashTab);
int HashTab_Dump(HashTab* HashTab);
int AddElem(HashTab* HashTab, Data* Data);

unsigned int HashFunc_1(Data* Data);
unsigned int HashFunc_2(Data* Data);
unsigned int HashFunc_3(Data* Data);
unsigned int HashFunc_4(Data* Data);
unsigned int HashFunc_5(Data* Data);

int HashTab_ctor(HashTab* HashTab, unsigned int(*HashFunc) (Data* Data))
{
	assert(HashTab != NULL);

	for (int i = 0; i < MAX_HASH; i++)
		List_ctor(&(HashTab->Lists[i]));

	HashTab->HashFunc = HashFunc;

	assert(HashTab_OK(HashTab));

	return 1;
}
int HashTab_dtor(HashTab* HashTab)
{
	assert(HashTab_OK(HashTab));

	for (int i = 0; i < MAX_HASH; i++)
		List_dtor(&(HashTab->Lists[i]));

	HashTab->HashFunc = NULL;

	return 1;
}
int HashTab_OK(HashTab* HashTab)
{
	for (int i = 0; i < MAX_HASH; i++)
		if (!List_OK(&(HashTab->Lists[i]))) return 1;

	if (HashTab->HashFunc) return 1;

	return 0;
}

int HashTab_Dump(HashTab* HashTab)
{
	printf("=====================================\n");
	printf("HashTab [%p]\n", HashTab);
	for (int i = 0; i < MAX_HASH; i++)
		List_Dump(&(HashTab->Lists[i]));

	printf("HashFunc [%p]\n", HashTab->HashFunc);
	printf("======================================\n");

	return 1;
}


int AddElem(HashTab* HashTab, Data* Data)
{
	assert(HashTab_OK(HashTab));
	assert(Data != NULL);

	int result = HashTab->HashFunc(Data) % MAX_HASH;

	if (Search(&(HashTab->Lists[result]), Data) == 0)
		AddtoBegin(&(HashTab->Lists[result]), Data);

	assert(HashTab_OK(HashTab));
	return 0;
}

unsigned int HashFunc_1(Data* Data)
{
	return 0;
}

unsigned int HashFunc_2(Data* Data)
{
	return (unsigned int)Data[0];
}
unsigned int HashFunc_3(Data* Data)
{
	return strlen(Data);
}
unsigned int HashFunc_4(Data* Data)
{
	int len = strlen(Data);
	unsigned int sum = 0;

	for (int i = 0; i < len; i++)
		sum += (unsigned int)Data[i];

	return sum;
}
unsigned int HashFunc_5(Data* Data)
{
	int length = strlen(Data);
	unsigned int h = 0;

	for (int i = 0; i < length; i++)
		h = (h << 1) ^ (unsigned int)Data[i];

	return h;
}

int Search( List* List, const Data* Data)
{
	assert(List_OK(List));
	assert(Data != NULL);

	if (List->number == 0) return 0;

	ListElem* Elem = List->first;
	for (int i = 1; i <= List->number; i++)
	{
		if (CompareChar(Elem, Data) == 0) return i;
		Elem = Elem->next;
	}

	return 0;
}

int CompareChar(ListElem* Elem, const char* Data)
{
	if (strcmp(Elem->Data, Data) == 0) return 0;

	return 1;
}