#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "io.h"
#include "clocale"

//Функции
int greetprint  ( );
void control    ( int control, char** beg, int nstr );

void print      ( char **text, int nstr );
char* read      ( int* len );

int nStrText    ( const char* text, const int length );
int begstr      ( char** Text, char* buff );

int compare     ( const void* beg1, const void* beg2 );
int compare_end ( const void* beg1, const void* beg2 );
int strcmpend   ( char* beg1, char* beg2 );

int main()
{
	setlocale(LC_ALL, "Russian");

	//! Контакт
	int len = 0;
	char* buf = read ( &len );//! int len = readfile( "file.txt", &buf );

	int nstr = nStrText ( buf, len ) + 1; //! countStrings (buf);
	char** beg = ( char** ) calloc ( nstr, sizeof( char* ) );

	int guestcontrol = 0;

	begstr( beg, buf ); //! divideStrings

	guestcontrol = greetprint ( ); //! getDecision
        control ( guestcontrol, beg, nstr );

	return 0;
}

void control( int control, char** beg, int nstr )
{
switch ( control )
     {
	case 1:
		print  ( beg, nstr );
		printf ( "\nß óñïåøíî âûïîëíèë ñâîþ çàäà÷ó=)\nÏîêà!!!\n" );
		break;

	case 2:
		qsort  ( beg, nstr, sizeof(char*), compare );
		print  ( beg, nstr );
                printf ( "\nß óñïåøíî âûïîëíèë ñâîþ çàäà÷ó=)\nÏîêà!!!\n" );
		break;

	case 3:
		qsort  ( beg, nstr, sizeof( char* ), compare_end );
		print  ( beg, nstr );
                printf ( "\nß óñïåøíî âûïîëíèë ñâîþ çàäà÷ó=)\nÏîêà!!!\n" );
		break;

	default:
			
                printf ( "\nÂû âûøëè èç ïðîãðàììû!!!\n" );
                printf ( "ß îñòàëñÿ áåç ðàáîòû =)\n" );
                break;
     }
}
int greetprint ( )
{
	int control = 0;

	printf ( "Âàñ ïðèâåòñòâóåò ïðîãðàììà 'Ñòèõîìàíèÿ v1.2' @Samir\n\n" );
	printf ( "Íàæìèòå 1,  åñëè õîòèòå çàïèñàòü â ôàéë îðèãèíàëüíûé  òåêñò\n"   );
	printf ( "Íàæìèòå 2,  åñëè õîòèòå ïðèìåíèòü ñîðòèðîâêó 'Åâãåíèé Îíåãèí'\n" );
	printf ( "Íàæìèòå 3,  åñëè õîòèòå ñäåëàòü ñëîâàðü ðèôì\n"  );
	printf ( "Íàæìèòå ëþáóþ äðóãóþ äëÿ òîãî,÷òîáû âûéòè\n\n\n" );

	scanf ( "%d", &control );

	return control;
}

char* read( int* len )
{
	FILE* f = fopen( "file.txt", "r" );

	assert( f );

	*len = filelength( fileno ( f ) );
	char* text = ( char* )calloc( *len, sizeof(char) );

	assert ( text );

	fread  ( text, *len, sizeof(char), f );

	fclose ( f );

	return text;
}

int nStrText ( const char* buff, const int len )
{
	assert ( buff );

	int nLen = 0;

	for ( int i = 0; i <= len; i++ )
	{
		if ( buff[i] == '\n' ) nLen++;
	}

	return nLen;
}

int begstr( char** beg, char* buff )
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
	
	assert(beg);
    	assert(buff);

	return 0;
}

void print(char **text, int nstr) //! fileName
{
	FILE *out = fopen( "out.txt", "w" );
	assert( out );
	assert(text);
	
	for ( int i = 0; i < nstr; i++ )
        {
		fputs ( *( text + i ), out );
		fputs ( "\n", out );
	}

	fclose ( out  );

	free   ( text );
	text = NULL;
}

int compare( const void* beg1, const void* beg2 )
{
    	int compare = strcmp ( *( char** ) beg1, *( char** ) beg2 );
	return compare;
}

int compare_end( const void* beg1, const void* beg2 )
{
    	int compare = strcmpend ( *( char** ) beg1, *( char** ) beg2 );
    	return compare;
}

int strcmpend ( char* beg1,  char* beg2 )
{
	assert ( beg1 );
	assert ( beg2 );
	
	const char* end1 = beg1 + strlen( beg1 ) - 1;
    	const char* end2 = beg2 + strlen( beg2 ) - 1;

	while ( *end1 < 65 && end1 > beg1 ) end1--;
	while ( *end2 < 65 && end2 > beg2 ) end2--;
	
	assert ( beg1 );
	assert ( beg2 );
	
	while ( end1 > beg1 && end2 > beg2 )
	{
		if ( *end1 > *end2 ) return  1;
		if ( *end1 < *end2 ) return -1;

		end1--;
		end2--;
	}
	return 0;
}
