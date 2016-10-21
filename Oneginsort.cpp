#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "io.h"
#include "clocale"

//=========Functions==========// 

int greetprint    ( );
void makeDecision ( int control, char** beg, int nstr );

void fileprint    ( char **text, int nstr, char *filename );
char* readfile    ( int* len );

int countStrings  ( const char* text, const int length );
int divideStrings ( char** Text, char* buff );

int compare       ( const void* beg1, const void* beg2 );
int compare_end   ( const void* beg1, const void* beg2 );
int strcmpend     ( char* beg1, char* beg2 );

int main()
{
	setlocale( LC_ALL, "Russian" );

	int len   = 0;
	char* buf = readfile( &len );

	int nstr   = countStrings( buf, len ) + 1;
	char** beg = ( char** )calloc( nstr, sizeof( char* ) );

	int getDecision = 0;

	divideStrings( beg, buf );
	getDecision = greetprint( );
	makeDecision( getDecision, beg, nstr );

	return 0;
}

//=========Functions==========//

void makeDecision( int control, char** beg, int nstr )
{
	char fileName1[ ] = "out1.txt";
	char fileName2[ ] = "out2.txt";
	char fileName3[ ] = "out3.txt";

	switch ( control )
	{
	case 1:

		fileprint( beg, nstr, fileName1 );
		break;

	case 2:

		qsort( beg, nstr, sizeof( char* ), compare );
		fileprint( beg, nstr, fileName2 );
		break;

	case 3:

		qsort( beg, nstr, sizeof( char* ), compare_end );
		fileprint( beg, nstr, fileName3 );
		break;

	default:
		printf( "\nВведена неверная команда\n!!!" );	
		break;
	}
}
int greetprint()
{
	int control = 0;

	printf( "Вас приветствует программа \"Стихомания\" @Samir v1.0.3\n" );
	printf( "Нажмите 1, если хотите оригинальный текст произведения\n" );
	printf( "Нажмите 2, если хотите применить сортировку \"Евгений Онегин\"\n" );
	printf( "Нажмите 3, если хотите применить сортировку \"CompareEnd\"\n" );

	scanf( "%d", &control );

	return control;
}

char* readfile( int* len )
{
	FILE* f = fopen( "file.txt", "r" );

	assert( f );

	*len = filelength( fileno( f ));
	char* text = ( char* )calloc( *len, sizeof( char ) );

	assert( text );

	fread( text, *len, sizeof( char ), f );

	fclose( f );

	return text;
}

//=========Operation with strings==========//

int countStrings( const char* buff, const int len )
{
	assert( buff );

	int nLen = 0;

	for ( int i = 0; i <= len; i++ )
	{
		if ( buff[i] == '\n' ) nLen++;
	}

	return nLen;
}

int divideStrings( char** beg, char* buff )
{
	assert( beg );
	assert( buff );

	*beg = buff;
	*beg++;
	*buff++;

	while ( *buff != '\0' )
	{
		if ( *( buff - 1 ) == '\n' )
		{
			*beg = buff;
			*beg++;
			*( buff - 1 ) = '\0';
		}
		*buff++;
	}

	assert( beg  );
	assert( buff );

	return 0;
}

//=========Print==========//

void fileprint( char **text, int nstr, char *filename )
{

	FILE *out = fopen( filename, "w" );
	assert( out  );
	assert( text );

	for ( int i = 0; i < nstr; i++ )
	{
		fputs( *( text + i ), out );
		fputs( "\n", out );
	}

	fclose( out );

	printf( "\nРабота успешна выполнена!\n" );
	printf( "Проверь файл!\n" );

}

//=========Compares==========//

int compare( const void* beg1, const void* beg2 )
{
	int compare = strcmp( *( char** )beg1, *( char** )beg2 );
	return compare;
}

int compare_end( const void* beg1, const void* beg2 )
{
	int compare = strcmpend( *( char** )beg1, *( char** )beg2 );
	return compare;
}

int strcmpend( char* beg1, char* beg2 )
{
	assert( beg1 );
	assert( beg2 );

	const char* end1 = beg1 + strlen( beg1 ) - 1;
	const char* end2 = beg2 + strlen( beg2 ) - 1;

	while ( *end1 < 65 && end1 > beg1 ) end1--;
	while ( *end2 < 65 && end2 > beg2 ) end2--;

	assert( beg1 );
	assert( beg2 );

	while ( end1 > beg1 && end2 > beg2 )
	{
		if ( *end1 > *end2 ) return  1;
		if ( *end1 < *end2 ) return -1;

		end1--;
		end2--;
	}
	return 0;
}

//=========Thanks You==========//
