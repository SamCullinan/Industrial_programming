#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <ctime>
#include <clocale>


//! Названия макросов лучше писать только большими буквами, чтобы издалека
//! было видно, что это.
#define Stack_dump( This ) _Stack_dump( This, #This );
#define Assert_OK( This ) if( !Stack_OK( This ) ) Stack_dump( This );

typedef double type;
typedef struct Stack
{
	int protection1;
	type* data;
	int   count;
	int   max;
	int protection2;
	type* prot_Date;
	type hash;

} Stack_t;

/*Константы*/

const int    Error_pos = -666;
const double Daterror = -666;

/*Функции*/

int  Stack_construct ( Stack_t *This, int size );
int  Stack_destruct  ( Stack_t *This );

int  Stack_push      ( Stack_t *This, int value );
type Stack_pop       ( Stack_t *This );

bool Stack_OK        ( const Stack_t *This );
//! Почему _Stack_dump выделен _ спереди?
void _Stack_dump     ( Stack_t *This, char* stk );
bool Stack_Rehash    ( const Stack *This );

int main()
{
	setlocale ( LC_ALL,"Russian" );
	Stack_t Stack;

	Stack_construct ( &Stack, 5 );

	for (int i = 0; i < 5; i++)
		Stack_push( &Stack, i );

	Assert_OK  ( &Stack );
	Stack_dump ( &Stack );

	for (int i = 0; i < 5; i++)
		printf ( "%lg\n" , Stack_pop( &Stack ) );

	Stack_destruct ( &Stack );

	system ( "pause" );
	return 0;
}

int Stack_construct ( Stack_t * This, int size )
{
	assert ( This );

	/* Проверять стек в начале конструктора на правильность не нужно. */
	if ( !Stack_OK ( This ) ) {
		This -> protection1 = 255;

		This -> data = ( type* ) calloc( size, sizeof( *This -> data ) );

		for (int i = 0; i < size; i++)
			This -> data[i] = Daterror;

		This -> max   = size;
		This -> count = 0;

		This -> protection2 = 255;
		This -> hash = This -> protection1 + This -> protection2
			     + This -> max;
		This -> prot_Date = This -> data;
	}
	else
	{
		printf ( "\nТакой Стек уже создан!!\n" );
		return 1;
	}

	assert ( This );

	return 0;
}

int  Stack_destruct ( Stack_t * This )
{
	assert ( This );

	/* Вот эту логику я бы немного исправил: если тебе в дестрктор пришёл
	   запорченный стек, то это повод завершить программу, так как
	   если с ним что-то не так, то возможно и данные храгнятся не там.
	   А если ты вызовешь free() от указателя, который не заказывался аллокатором,
		 то вся прога упадёт без диагностики.
		 Лучше уж ты её завершишь, зато со всей нужной информацией.
	*/
	if ( Stack_OK ( This ) )
	{
		This -> max   = 0;
		This -> count = Error_pos;
		This -> hash  = 0;

		if ( This -> data != NULL )
		{
			free ( ( This -> data ) );
			This -> data = NULL;
			This -> prot_Date = NULL;
			return true;
		}
		else
			return false;
	}
	return true;
}

int  Stack_push ( Stack_t * This, int value )
{
	assert ( Stack_OK ( This ) );

	/* У тебя нет никакой проверки на то, что стек заполнен к моменту пуша.
	Если ты обратишься к памяти, которую ты не заказывал,
	прога может упасть без диагностики */
	This -> data [ This -> count++ ] = value;

	assert ( Stack_OK ( This ) );
	return 0;
}

type Stack_pop ( Stack_t * This )
{
	assert ( Stack_OK ( This ) );

	/* То же самое, что и с пушем. */
	This -> count--;
	type top = This -> data[This -> count];
	This -> data[This -> count] = Daterror;

	Assert_OK ( This );

	return top;
}

bool Stack_OK ( const Stack_t * This )
{
	return  This                      &&
		This -> count >= 0        &&
		This -> data              &&
		This -> max               &&
		Stack_Rehash ( This )     &&
		This -> count <= This -> max;
}

void _Stack_dump ( Stack_t *This, char* stk )
{
	printf ( "Stack_dump\n" );
	printf ( "Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__ );
	printf ( "=================================\n" );

	if ( Stack_OK ( This ) )
		printf ( "Stack_t \"%s\" (Ok) [%p]\n", stk + 1, This );
	else
		printf ( "Stack_t \"[%s]\" (Error) [%p]\n", stk, This );

	printf ( "data[%d] = [%p]\n", This->max, This->data );
	printf ( " {\n" );

	//! Будь здесь аккуратен, обращение по нулевому указателю дропает программу.
	for ( int i = 0; i < This -> max; i++ )
	{
		if ( i < This -> count )
			printf ( "   *[%d] = %lg\n", i, This -> data[i] );
		else
			printf ("   [%d] = %lg  Poison!\n", i, This -> data[i] );
	}

	printf ( " }\n" );
	printf ( "count = %d\n", This->count );
	printf ( "max   = %d\n", This->max );
	printf ( "=================================\n" );
}

bool Stack_Rehash ( const Stack *This )
{
	type buff = This -> protection1 + This -> protection2 + This -> max;
	if ( This -> hash == buff && This -> prot_Date == This -> data) return 1;
	else return 0;
}
