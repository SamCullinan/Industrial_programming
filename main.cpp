#include <iostream>
#include "M_Stack.h"
#include "Errno.h"
#include <clocale>

int main()
{
	setlocale ( LC_ALL, "Russian" );

	Stack_t Stack;

	Stack_construct ( &Stack, 5 );

	for ( int i = 0; i < 5; i++ )
		Stack_push( &Stack, i );

	for ( int i = 0; i < 8; i++ )
		printf ( "%lg\n", Stack_pop( &Stack ) );

	Stack_destruct ( &Stack );

	system ( "pause" );
	return 0;
}
