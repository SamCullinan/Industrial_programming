#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "io.h"
#include "clocale"

int greetprint    ( );
void doDecision   ( int control, char** beg, int nstr);

void fileName     ( char **text, int nstr);
char* readfile    ( int* len );

int countStrings  ( const char* text, const int length );
int divideStrings ( char** Text, char* buff );

int compare       ( const void* beg1, const void* beg2 );
int compare_end   ( const void* beg1, const void* beg2 );
int strcmpend     ( char* beg1, char* beg2 );

int main( )
{
	setlocale( LC_ALL, "Russian" );

	int len = 0;
	char* buf = readfile( &len );

	int nstr = countStrings(buf, len) + 1;
	char** beg = ( char** )calloc( nstr, sizeof( char* ));

	int getDecision = 0;

	divideStrings( beg, buf );
	getDecision = greetprint( );
	doDecision( getDecision, beg, nstr );

	return 0;
}

void doDecision( int control, char** beg, int nstr )
{
	switch ( control )
	{
	case 1:
		fileName( beg, nstr );
		break;

	case 2:
		qsort( beg, nstr, sizeof( char* ), compare );
		fileName(beg, nstr);
		break;

	case 3:
		qsort( beg, nstr, sizeof( char* ), compare_end );
		fileName( beg, nstr );
		break;

	default:
		break;
	}
}
int greetprint( )
{
	int control = 0;



	scanf( "%d", &control  );

	return control;
}

char* readfile( int* len )
{
	FILE* f = fopen( "file.txt", "r" );

	assert( f );

	*len = filelength( fileno( f ) );
	char* text = ( char* )calloc( *len, sizeof( char ) );

	assert(text);

	fread( text, *len, sizeof( char ), f );

	fclose( f );

	return text;
}

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
	assert( beg  );
	assert( buff );

	*beg = buff;
	*beg++;
	*buff++;

	while ( *buff != '\0' )
	{
		if ( *( buff - 1 ) == '\n')
		{
			*beg = buff;
			*beg++;
			*( buff - 1 ) = '\0';
		}
		*buff++;
	}

	assert( beg );
	assert( buff );

	return 0;
}

void fileName( char **text, int nstr )
{
	FILE *out = fopen( "out.txt", "w" );
	assert( out );
	assert( text );

	for ( int i = 0; i < nstr; i++ )
	{
		fputs( *( text + i ), out );
		fputs( "\n", out );
	}

	fclose( out );
}

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
