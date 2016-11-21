#include "list.h"

int List_ctor(List_t* List)
{
	assert(List);

	List->number = 0;
	List->head = NULL;
	List->tail = NULL;

	assert(List_OK(List));

	return 0;
}

int List_dtor(List_t* List)
{
	assert(List_OK(List));

	for (int i = 1; i < List->number; i++) RemBeg(List);

	List->number = -666;
	List->head = NULL;
	List->tail = NULL;

	return 0;
}


int List_OK(const List_t* List)
{
	if (!List)  return 1;
	if (((List->head == NULL) && (List->number != 0)) ||
		((List->tail == NULL) && (List->number != 0))) return 1;

	if (List->number != 0)
	{
		Listelem_t* Elem = List->head;
		Listelem_t* PrevElem = NULL;

		for (int i = 1; i < List->number; i++)
		{
			PrevElem = Elem;
			Elem = Elem->next;
			if (PrevElem != Elem->prev) return 1;
		}

		if (Elem != List->tail) return 1;
	}

	return 0;
}


int List_Dump(List_t* List)
{
	printf("List_dump\n");
	printf("Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__);
	printf("=====================================\n");
	printf(" List [%p]\n", List);
	printf(" number = %d\n ", List->number);
	printf(" head  = %p\n ", List->head);
	printf(" tail   = %p\n ", List->tail);

	Listelem_t *ListElem = NULL;

	if (List->number)
	{
		ListElem = List->head;

		for (int i = 0; i < List->number; i++)
		{
			ListElem_Dump(ListElem, i);
		}
	}

	
	
	printf("=====================================\n");

	return 0;
}



int AddFirst(List_t* List, Data_t* Data)
{
	assert(List_OK(List));
	assert(Data);
	assert(List->number == 0);

	Listelem_t* NewElem =(Listelem_t*)calloc(1, sizeof(Listelem_t));
	
	assert(NewElem);
	
	ListElem_ctor(NewElem, Data);

	List->head = NewElem;
	List->tail = NewElem;

	List->number++;

	assert(List_OK(List));

	return 0;
}
int AddRight(List_t* List, Data_t* Data, int number)
{
	assert(List_OK(List));
	assert(Data != NULL);
	assert((number >= 1) && (number <= List->number));

	if (List->number == 0) { AddFirst(List, Data);                     return 0; }
	if (List->number <= number) { AddEnd(List, Data);                     return 0; }
	else { AddBetween(List, Data, number, number + 1); return 0; }

	assert(List_OK(List));

	return 0;
}

int AddLeft(List_t* List, Data_t* Data, int number)
{
	assert(List_OK(List));
	assert(Data);
	assert((number >= 1) && (number <= List->number));

	if (List->number == 0) 
	{
		AddFirst(List, Data);
		return 0; 
	}
	if (number == 1) {
		AddBeg(List, Data);
		return 0; 
	}
	else { 
		AddBetween(List, Data, number - 1, number);
		return 0; 
	}

	assert(List_OK(List));

	return 0;
}

int AddBetween(List_t* List, Data_t* Data, int first, int second)
{
	assert(List_OK(List));
	assert(Data);
	assert((first >= 1) && (first <= List->number));
	assert((second >= 1) && (second <= List->number));
	assert(first + 1 == second);

	Listelem_t* NewElem = (Listelem_t*)calloc(1, sizeof(Listelem_t));   
	assert(NewElem);                            
	ListElem_ctor(NewElem, Data);

	Listelem_t* ElemBefore = PtrOnElem(List, first);
	Listelem_t* ElemAfter = PtrOnElem(List, second);

	assert(ElemBefore);
	assert(ElemAfter);

	Add(ElemBefore, NewElem);
	Add(NewElem, ElemAfter);

	List->number++;

	assert(List_OK(List));

	return 0;
}

int AddBeg(List_t* List, Data_t* Data)
{
	assert(List_OK(List));
	assert(Data);

	if (List->number == 0) { AddFirst(List, Data); return 0; }
	
	Listelem_t* NewElem =(Listelem_t*)calloc(1, sizeof(Listelem_t));  
	assert(NewElem);         
	ListElem_ctor(NewElem, Data);
	Listelem_t* FirstElem = List->head;

	Add(NewElem, FirstElem);

	List->head = NewElem;
	List->number++;

	assert(List_OK(List));

	return 0;
}

int AddEnd(List_t* List, Data_t* Data)
{
	assert(List_OK(List));
	assert(Data != NULL);

	if (List->number == 0) { AddFirst(List, Data); return 0; }

	Listelem_t* NewElem = (Listelem_t*)calloc(1, sizeof(Listelem_t));   
	assert(NewElem);                            
	ListElem_ctor(NewElem, Data);
	Listelem_t* LastElem = List->tail;

	Add(LastElem, NewElem);

	List->tail = NewElem;
	List->number++;

	assert(List_OK(List));

	return 0;
}

int RemLast(List_t* List)
{
	assert(List_OK(List));
	assert(List->number == 1);

	Listelem_t* DelElem = List->head;
	assert(DelElem != NULL);
	

	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;

	List->head = NULL;
	List->tail = NULL;

	List->number--;

	assert(List_OK(List));

	return 0;
}

int RemNum(List_t* List, int number)
{
	assert(List_OK(List));
	assert(List->number > 0);
	assert((number >= 1) && (number <= List->number));

	if (List->number == 1) {
		RemLast(List);
		return 0;
	}
	if (number == 1) {
		RemBeg(List); 
		return 0; 
	}
	if (number == List->number) { 
		RemEnd(List);
		return 0;
	}

	Listelem_t* ElemBefore = PtrOnElem(List, number - 1);
	Listelem_t* ElemAfter = PtrOnElem(List, number + 1);

	assert(ElemBefore);
	assert(ElemAfter);

	Listelem_t* DelElem = PtrOnElem(List, number);
	assert(DelElem);


	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;

	Add(ElemBefore, ElemAfter);

	List->number--;

	assert(List_OK(List));

	return 0;
}

int RemEnd(List_t* List)
{
	assert(List_OK(List));
	assert(List->number > 0);

	if (List->number == 1) { RemLast(List); return 0; }

	Listelem_t* ElemBefore = PtrOnElem(List, List->number - 1);

	Listelem_t* DelElem = PtrOnElem(List, List->number);
	assert(DelElem);

	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;

	ElemBefore->next = NULL;
	List->tail = ElemBefore;

	List->number--;

	assert(List_OK(List));

	return 0;
}

int RemBeg(List_t* List)
{
	assert(List_OK(List));
	assert(List->number > 0);

	if (List->number == 1) { RemLast(List); return 0; }

	Listelem_t* ElemAfter = PtrOnElem(List, 2);

	Listelem_t* DelElem = List->head;
	assert(DelElem);
	
	ListElem_dtor(DelElem);
	free(DelElem);
	DelElem = NULL;


	ElemAfter->prev = NULL;
	List->head = ElemAfter;

	List->number--;

	assert(List_OK(List));

	return 0;
}


Listelem_t* PtrOnElem(const List_t* List, int number)
{
	assert(List_OK(List));
	assert((number >= 1) && (number <= List->number));
	assert(List->number != 0);

	Listelem_t* Elem = List->head;
	for (int i = 1; i < number; i++)  Elem = Elem->next;

	assert(List_OK(List));

	return Elem;
}

int Search(const List_t* List, const Data_t* Data)
{
	assert(List_OK(List));
	assert(Data);

	if (List->number == 0) return 1;

	Listelem_t* Elem = List->head;
	for (int i = 1; i <= List->number; i++)
	{
		if (Compare(Elem, Data) == 0) return i;
		Elem = Elem->next;
	}

	return 1;
}
