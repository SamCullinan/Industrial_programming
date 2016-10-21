#include "M_Stack.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

int Stack_construct( Stack_t * This, int size )
{
	
	assert( This );

	if ( This -> allocator == 0 )
	{
		This -> protection1 = 255;

		This -> data = ( type* )calloc( size, sizeof( *This -> data ) );
		for ( int i = 0; i < size; i++ )
			This -> data[ i ] = Daterror;
		This -> max = size;
		This -> count = 0;

		This -> protection2 = 255;
		This -> allocator = 1;

		This -> hash = This -> protection1 + This -> protection2
			+ This -> max + This -> allocator;

		This -> prot_Date = This -> data;
	}
	else
	{
		printf( "\nВаш стек уже создан!!\n" );

		ASSERT_OK( This );

		return 1;
	}

	assert( This );

	return 0;
}

int  Stack_destruct( Stack_t * This )
{
	assert( This );

	if ( Stack_OK( This ) ) 
	{
		This -> max = 0;
		This -> count = Error_pos;
		This -> hash = 0;
		if (This -> data != NULL)
		{
			free( ( This -> data ) );
			This -> data = NULL;
			This -> prot_Date = NULL;
			return 0;
		}
		else
		{
			ASSERT_OK( This );
			return 1;
		}
	}
	else {
		printf( "Неверный стек!!!" );
		ASSERT_OK( This );
		return 1;
	}
}

int  Stack_push( Stack_t * This, int value )
{
	assert( Stack_OK( This ) );

	if ( This -> count >= This -> max )
	{
		printf( "Стек переполнен!!!\n" );
		printf( "Все плохо=(!!!\n" );
		abort( );
	}

	This -> data[ This -> count++ ] = value;

	assert( Stack_OK(This ) );

	return 0;
}

type Stack_pop( Stack_t * This )
{
	assert( Stack_OK( This ) );

	if ( !This -> count )
	{
		printf( "Обащение к несуществующему элементу\n" );
		ASSERT_OK( This );
	}

	This -> count--;
	type top = This -> data[ This -> count ];
	This -> data[ This -> count ] = Daterror;

	ASSERT_OK( This );

	return top;
}

bool Stack_OK( const Stack_t * This )
{
	return  This                       &&
		This -> count >= 0         &&
		This -> allocator          &&
		This -> data               &&
		This -> max                &&
		Stack_Rehash( This )       &&
		This -> count <= This -> max;
}

void Stack_dump( Stack_t *This, char* stk )
{
	printf( "Stack_dump\n" );
	printf( "Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__ );
	printf( "=================================\n" );

	if ( Stack_OK( This ) )
		printf( "Stack_t \"%s\" (Ok) [%p]\n", stk, This );
	else
		printf( "Stack_t \"[%s]\" (Error) [%p]\n", stk, This );

	printf( " data[%d] = [%p]\n", This -> max, This -> data );
	printf( " {\n" );

	for ( int i = 0; i < This -> max; i++ )
	{
		if ( i < This -> count )
		{
			if ( This -> data )
				printf( "   *[%d] = %lg\n", i, This -> data[ i ] );
		}
		else
		{
			if ( This -> data )
				printf( "   [%d] = %lg  Poison!\n", i, This -> data[ i ] );
		}
	}

	printf( " }\n" );
	printf( "count = %d\n", This->count );
	printf( "max   = %d\n", This -> max );
	printf( "=================================\n" );
}

bool Stack_Rehash( const Stack *This )
{
	type buff = This -> protection1 + This -> protection2 + This -> max
		+ This -> allocator;
	if (This -> hash == buff && This -> prot_Date == This -> data )
		return 1;
	else
		return 0;
}
