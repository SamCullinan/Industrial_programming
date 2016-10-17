#ifndef  M_Stack__H
#define  M_Stack__H

//DEFINES
#define  STACK_DUMP ( This )  Stack_dump( This, #This );
#define  ASSERT_OK  ( This )  if( !Stack_OK ( This ) ) \
{                                                       \
	STACK_DUMP ( This );                             \
	abort ( );                                        \
}

typedef double type;

typedef struct Stack
{	
	int protection1;
	
	type* data;
	int   count;
	int   max;
		
	type hash;
	type* prot_Date;
	bool allocator = 0;
 
	int protection2;
	
} Stack_t;

/*Êîíñòàíòû*/

const int    Error_pos = -666;
const double Daterror = -666;

/*Ôóíêöèè*/

int  Stack_construct ( Stack_t *This, int size );
int  Stack_destruct  ( Stack_t *This );

int  Stack_push      ( Stack_t *This, int value );
type Stack_pop       ( Stack_t *This );

bool Stack_OK        ( const Stack_t *This );
void Stack_dump      ( Stack_t *This, char* stk );
bool Stack_Rehash    ( const Stack *This );

#endif M_Stack__H
