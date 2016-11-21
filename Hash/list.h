#include <assert.h>
#include "list_elem.h"


struct List_t
{

	
	int number;
	Listelem_t* head;
	Listelem_t* tail;


};

int List_ctor  (List_t* List);
int List_dtor  (List_t* List);

int List_OK    (const List_t* List);
int List_Dump  (const List_t* List);

int AddFirst   (List_t* List, Data_t* Data);
int AddRight   (List_t* List, Data_t* Data, int number);
int AddLeft    (List_t* List, Data_t* Data, int number);
int AddBetween (List_t* List, Data_t* Data, int first, int second);
int AddBeg     (List_t* List, Data_t* Data);
int AddEnd     (List_t* List, Data_t* Data);

int RemLast    (List_t* List);
int RemNum     (List_t* List, int number);
int RemEnd     (List_t* List);
int RemBeg     (List_t* List);

Listelem_t* PtrOnElem ( const List_t* List, int number         );
int Search            ( const List_t* List, const Data_t* Data );