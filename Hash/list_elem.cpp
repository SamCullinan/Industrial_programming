#include "list_elem.h"

int ListElem_ctor(Listelem_t* Elem, Data_t* Data)
{
	assert(Elem);
	assert(Data);

	Elem->Data = Data;

	Elem->prev = NULL;
	Elem->next = NULL;

	assert(ListElem_OK(Elem));

	return 0;
}

int ListElem_dtor(Listelem_t* Elem)
{
	assert(ListElem_OK(Elem));

	Elem->Data = NULL;
	Elem->prev = NULL;
	Elem->next = NULL;

	return 0;
}


int ListElem_OK(const Listelem_t* Elem)
{
	if (!Elem )return 1;
	if (!Elem->Data) return 1;

	return 0;
}



int ListElem_Dump(const Listelem_t* ListElem, int count)
{
	
	printf("ListElem_dump\n");
	printf("Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__);
	printf("Element %d\n", count);
	printf("Data [%p]\n" , ListElem->Data);
	printf("%s\n",		   ListElem->Data);
	printf("[%p]\n",	   ListElem);
	printf("prev = %p\n",  ListElem->prev);
	printf("next = %p\n",  ListElem->next);

	ListElem = ListElem->next;		
	return 0;
}

int PrintData(char* Data)
{
	printf("\n%s\n", Data);
	return 0;
}

int PrintData(int*  Data)
{
	for (int i = 0; i < MAX_ELEM_SIZE; i++)
		printf("Data [%p] = %d\n", Data + i, Data[i]);
	return 0;
}

int Compare(Listelem_t* Elem, const char* Data)
{
	if (strcmp(Elem->Data, Data) == 0) return 1;
	return 0;
}


int Add(Listelem_t* Elem_1, Listelem_t* Elem_2)
{
	
	assert(ListElem_OK(Elem_1));
	assert(ListElem_OK(Elem_2));

	Elem_1->next = Elem_2;
	Elem_2->prev = Elem_1;

	assert(ListElem_OK(Elem_1));
	assert(ListElem_OK(Elem_2));
	return 0;
}
