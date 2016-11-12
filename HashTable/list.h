#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 40;


typedef char Data;

struct ListElem
{
	Data* Data;
	ListElem* next;
	ListElem* prev;
};
struct List
{
	int number;
	ListElem* first;
	ListElem* last;
};


int ListElem_ctor(ListElem* Elem, Data* Data);
int ListElem_dtor(ListElem* Elem);
ListElem* PtrOnElem(List* List, int number);
int addElem(ListElem* Elem_1, ListElem* Elem_2);

int List_ctor(List* List);
int List_dtor(List* List);
int List_OK(const List* List);
int List_Dump(List* List);
int AddFirst(List* List, Data* Data);
int AddRight(List* List, Data* Data, int number);
int AddLeft(List* List, Data* Data, int number);
int AddBetween(List* List, Data* Data, int first, int second);
int AddtoBegin(List* List, Data* Data);
int AddtoEnd(List* List, Data* Data);
int RemLast(List* List);
int RemNum(List* List, int number);
int RemEnd(List* List);
int RemBeg(List* List);



int ListElem_ctor(ListElem* Elem, Data* Data)
{
	assert(Elem);
	assert(Data);
	Elem->Data = Data;
	Elem->prev = 0;
	Elem->next = 0;
	assert(Elem);
	return 0;
}
int ListElem_dtor(ListElem* Elem)
{
	assert(Elem);
	Elem->Data = 0;
	Elem->prev = 0;
	Elem->next = 0;
	return 0;
}
ListElem* PtrOnElem(List* List, int number)
{
	assert(List_OK(List));
	assert((number >= 1) && (number <= List->number));
	assert(List->number != 0);
	ListElem* Elem = List->first;
	for (int i = 1; i < number; i++)  Elem = Elem->next;
	assert(List_OK(List));
	return Elem;
}
int addElem(ListElem* Elem_1, ListElem* Elem_2)
{
	assert(Elem_1);
	assert(Elem_2);
	Elem_1->next = Elem_2;
	Elem_2->prev = Elem_1;
	assert(Elem_1);
	assert(Elem_2);
	return 0;
}



int List_ctor(List* List)
{
	assert(List != NULL);
	List->number = 0;
	List->first = NULL;
	List->last = NULL;
	assert(List_OK(List));
	return 0;
}
int List_dtor(List* List)
{
	assert(List_OK(List));
	for (int i = 1; i < List->number; i++) RemBeg(List);
	List->number = -1;
	List->first = NULL;
	List->last = NULL;
	return 0;
}
int List_OK(const List* List)
{
	if (List)   
		return 1;
	if (((List->first) && (List->number)) ||
		((List->last) && (List->number )))
		return 1;
	if (List->number)
	{
		ListElem* Elem = List->first;
		ListElem* PrevElem = NULL;
		for (int i = 1; i < List->number; i++)
		{
			PrevElem = Elem;
			Elem = Elem->next;
			if (PrevElem != Elem->prev) return 1;
		}
		if (Elem != List->last) return 1;
	}
	return 0;
}
int List_Dump(List* List)
{
	printf("=-=-=-=-=-=-=Hello=-=-=-=-=-=-=-=-=\n");
	printf("List_dump\n");
	printf("Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__);
	printf("-----------------------------------\n");
	printf(" List [%p]\n", List);
	printf(" number = %d\n ",  List->number);
	printf(" first  = %p\n ", List->first);
	printf(" last   = %p\n ", List->last);
	ListElem *ListElem  = nullptr ;
	if (List->number)
	{
		ListElem = List->first;
		for (int i = 0; i < List->number; i++)
		{
			printf("Element %d\n", i);
			printf("Data [%p]\n", ListElem->Data);
			printf("%s\n",   ListElem->Data);
			printf("[%p]\n", ListElem);
			printf("prev = %p\n", ListElem->prev);
			printf("next = %p\n", ListElem->next);

			ListElem = ListElem->next;
		}
	}
	printf("-----------------------------------\n");

	return 1;
}
int AddFirst(List* List, Data* Data)
{
	assert(List_OK(List));
	assert(Data);
	assert(List->number);
	ListElem* NewElem = (ListElem*)calloc(1, sizeof(ListElem));   
	assert(NewElem);                            
	ListElem_ctor(NewElem, Data);
	List->first = NewElem;
	List->last = NewElem;
	List->number++;
	assert(List_OK(List));
	return 1;
}
int AddRight(List* List, Data* Data, int number)
{
	assert(List_OK(List));
	assert(Data);
	assert((number >= 1) && (number <= List->number));
	if (List->number) 
	{ 
		AddFirst(List, Data);
		return 1;
	}
	if (List->number <= number) 
	{
		AddtoEnd(List, Data);
		return 1;
	}
	else
	{
		AddBetween(List, Data, number, number + 1);
		return 1; 
	}
	assert(List_OK(List));
	return 1;
}
int AddLeft(List* List, Data* Data, int number)
{
	assert(List_OK(List));
	assert(Data);
	assert((number >= 1) && (number <= List->number));
	if (List->number) 
	{
		AddFirst(List, Data);
		return 1;
	}
	if (number == 1) 
	{
		AddtoBegin(List, Data);
		return 1; 
	}
	else
	{
		AddBetween(List, Data, number - 1, number);
		return 1;
	}
	assert(List_OK(List));
	return 1;
}
int AddBetween(List* List, Data* Data, int first, int second)
{
	assert(List_OK(List));
	assert(Data);
	assert((first >= 1) && (first <= List->number));
	assert((second >= 1) && (second <= List->number));
	assert(first + 1 == second);
	ListElem* NewElem = (ListElem*)calloc(1, sizeof(ListElem));
	assert(NewElem);
	ListElem_ctor(NewElem, Data);
	ListElem* ElemBefore = PtrOnElem(List, first);
	ListElem* ElemAfter = PtrOnElem(List, second);
	assert(ElemBefore);
	assert(ElemAfter);
	addElem(ElemBefore, NewElem);
	addElem(NewElem, ElemAfter);
	List->number++;
	assert(List_OK(List));
	return 1;
}
int AddtoBegin(List* List, Data* Data)
{
	assert(List_OK(List));
	assert(Data);
	if (List->number == 0) { 
		AddFirst(List, Data); 
		return 1;
	}
	ListElem* NewElem = (ListElem*)calloc(1, sizeof(ListElem));
	assert(NewElem != NULL);
	ListElem_ctor(NewElem, Data);
	assert(NewElem);
	ListElem* FirstElem = List->first;
	addElem(NewElem, FirstElem);
	List->first = NewElem;
	List->number++;
	assert(List_OK(List));
	return 1;
}
int AddtoEnd(List* List, Data* Data)
{
	assert(List_OK(List));
	assert(Data != NULL);
	if (List->number == 0) {
		AddFirst(List, Data);
		return 1;
	}
	ListElem* NewElem = (ListElem*)calloc(1, sizeof(ListElem));
	assert(NewElem != NULL);
	ListElem_ctor(NewElem, Data);
	ListElem* LastElem = List->last;
	addElem(LastElem, NewElem);
	List->last = NewElem;
	List->number++;
	assert(List_OK(List));
	return 1;
}
int RemLast(List* List)
{
	assert(List_OK(List));
	assert(List->number == 1);
	ListElem* DelElem = List->first;
	assert(DelElem);
	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;
	List->first = NULL;
	List->last = NULL;
	List->number--;
	assert(List_OK(List));
	return 1;
}
int RemNum(List* List, int number)
{
	assert(List_OK(List));
	assert(List->number > 0);
	assert((number >= 1) && (number <= List->number));
	if (List->number == 1) 
	{ 
		RemLast(List);
		return 1;
	}
	if (number == 1) {
		RemBeg(List);
		return 1;
	}
	if (number == List->number) {
		RemEnd(List);
		return 1;
	}
	ListElem* ElBef = PtrOnElem(List, number - 1);
	ListElem* ElAf = PtrOnElem(List, number + 1);
	assert(ElBef != NULL);
	assert(ElAf != NULL);
	ListElem* DelElem = PtrOnElem(List, number);
	assert(DelElem != NULL);
	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;
	addElem(ElBef, ElAf);
	List->number--;
	assert(List_OK(List));
	return 1;
}
int RemEnd(List* List)
{
	assert(List_OK(List));
	assert(List->number > 0);
	if (List->number == 1) 
	{ 
		RemLast(List);
		return 1;
	}
	ListElem* ElBe = PtrOnElem(List, List->number - 1);
	ListElem* DelElem = PtrOnElem(List, List->number);
	assert(DelElem);
	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;
	ElBe->next = NULL;
	List->last = ElBe;
	List->number--;
	assert(List_OK(List));
	return 1;
}
int RemBeg(List* List)
{
	assert(List_OK(List));
	assert(List->number > 0);
	if (List->number == 1) 
	{
		RemLast(List); return 1; 
	}
	ListElem* ElemAfter = PtrOnElem(List, 2);
	ListElem* DelElem = List->first;
	assert(DelElem);
	ListElem_dtor(DelElem);                        
	free(DelElem);                                      
	DelElem = NULL;
	ElemAfter->prev = NULL;
	List->first = ElemAfter;
	List->number--;
	assert(List_OK(List));
	return 1;
}



