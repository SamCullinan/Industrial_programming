#include "hash.h"


int HashTab_ctor(Hash_t* HashTab, unsigned int(*HashFunc) (Data_t* Data))
{

	assert(HashTab);

	for (int i = 0; i < MAX_TAB_SIZE; i++)
		List_ctor(&(HashTab->List[i]));

	HashTab->HashFunc = HashFunc;

	assert(HashTab_OK(HashTab));
	
	return 0;

}

int HashTab_dtor(Hash_t* HashTab)
{
	
	assert(HashTab_OK(HashTab));

	for (int i = 0; i < MAX_TAB_SIZE; i++)
		List_dtor(&(HashTab->List[i]));

	HashTab->HashFunc = NULL;
	return 0;

}


int HashTab_OK(Hash_t* HashTab)
{
	
	for (int i = 0; i < MAX_TAB_SIZE; i++)
		if (!List_OK(&(HashTab->List[i]))) return 1;

	if ( !HashTab->HashFunc ) return 1;
	printf("HashTab_OK\n");
	return 0;


}


int HashTab_Dump(Hash_t* HashTab)
{
	
	printf("======================================\n");
	printf("Hash_Dump\n");
	printf("Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__);
	printf("HashTab [%p]\n", HashTab);
	for (int i = 0; i < MAX_TAB_SIZE; i++)
		List_Dump(&(HashTab->List[i]));

	printf("HashFunc [%p]\n", HashTab->HashFunc);
	printf("======================================\n");

	return 0;
}

int AddElem(Hash_t* HashTab, Data_t* Data)
{
	
	assert(HashTab_OK(HashTab));
	assert(Data);

	int result = HashTab->HashFunc(Data) % MAX_TAB_SIZE;

	if (Search(&(HashTab->List[result]), Data) == 0)
		AddBeg(&(HashTab->List[result]), Data);

	assert(HashTab_OK(HashTab));
	return 0;

}

unsigned int HashFunc_1(Data_t* Data)
{

	return 0;

}

unsigned int HashFunc_2(Data_t* Data)
{
	return (unsigned int)Data[0];
}

unsigned int HashFunc_3(Data_t* Data)
{
	return strlen(Data);
}

unsigned int HashFunc_4(Data_t* Data)
{
	
	int len = strlen(Data);
	unsigned int sum = 0;

	for (int i = 0; i < len; i++)
		sum += (unsigned int)Data[i];

	return sum;

}

unsigned int HashFunc_5(Data_t* Data)
{
	
	int length = strlen(Data);
	unsigned int h = 0;

	for (int i = 0; i < length; i++)
		h = (h << 1) ^ (unsigned int)Data[i];
	return h;

}

