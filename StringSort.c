#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include "io.h"

//Ôóíêöèè

void controlpanel (  );
void print        ( int n, char **end  );
void greetprint   ( );
int  compare      ( char *text1, char*text2, int a = 0, int b = 0, int f );
void quickSort    ( char **end, int l, int r, int * end1,int f ) ;
void quickSort    ( char **end, int l, int r, int f );
int mystrlen      ( char **end, char *text, unsigned int size_of_file );
int readsize      ( char *text );
int* endstr       ( char **end, int n );

int main ( )
{
    setlocale ( LC_ALL, "Rus" );

    greetprint   ( );

    controlpanel ( );

	printf("Ñýð, ðàáîòó âûïîëíèë óñïåøíî.\nÏðîâåðüòå ôàéë,ÿ çàïèñàë âàì âñå òóäà.\nÓäà÷è,Ñýð.\n ");
	return 0;
}

void controlpanel (  ) {

//Ïåðåìåííûå
int FLAG      = 0;
int control   = 0;
int size      = 0;
int len       = 0;

scanf( "%d",&control );

 //Ìàññèâû
char  *text       = ( char* )  malloc ( sizeof ( text ) );
char  **beg       = ( char**)  malloc ( sizeof ( *beg ) );
int   *end        = ( int*  )  malloc ( sizeof ( end ) );

size = readsize ( text );
len  = mystrlen ( beg , text, size );

//Îðèãèíàëüíûé òåêñò
if ( control == 1 )
	{
        print( len, beg );

	}

// Åâãåíèé Îíåãèí
else	if ( control == 2 )
	{
        FLAG = -1;
        quickSort ( beg, 0, len, FLAG);
		print( len, beg );
	}

 //Cîðòèðâêà ñ êîíöà
else	if ( control == 3)
	{

    FLAG = 1;
    end = endstr ( beg, len );
    quickSort ( beg, 0, len, end, FLAG);
	print ( len, beg );
	}
	else printf ( "Íåïðàâèëüíûé ââîä ÷èñëà!" );
}

//Ñ÷èòûâàíèå
int readsize (char *text)
{
	long size_of_file = 0;
    //Îòêðûòèå ïîòîê
	FILE  *in = fopen ( "file.txt", "r" );
	assert( in );
    //Ðàçìåð ôàéëà
	fseek( in, 0, SEEK_END );
	size_of_file = ftell( in );
	rewind( in );
	text = ( char* ) realloc ( text, sizeof(char) * size_of_file );
	//Ñ÷èòûâàíèå
	fread ( text, 1, size_of_file, in );

	fclose ( in );
	return size_of_file;
}

//Íàõîæäåíèå êîíöà ñòðîê
int* endstr ( char **end, int n ) {

	int* end1 = ( int* ) malloc ( sizeof ( end1 )*( n + 1) );
	assert ( end1 ) ;

	int len = 0;
	for ( int i = 0; i <= n; i++ )
	{
		while ( * ( * ( end + i ) + len ) != '\0' )
		{
			len++;
		}
		end1[ i ] = len - 1;
		len = 0;
	}
	return end1;
}

//Íàõîæäåíèå êîë-âî  ñòðîê
int mystrlen( char **end, char *text, unsigned int size_of_file )
{

    int n = 0;
	end[ 0 ] = &text[ 0 ];

	for ( unsigned int i = 0; i < size_of_file; i++ )
	{
		if (text[ i ] == '\n')
		{
			text[ i ] = '\0';
			++n;
			end = ( char** ) realloc ( end, sizeof ( char* )*( n + 2 ) );
			end[ n ] = &text[i + 1];
		}
	}
	return n;
}

//Ïå÷àòü
void print ( int n, char **end )
{
	FILE *out = fopen ( "out.txt", "w" );
    assert(out);
	for ( int i = 0; i <= n; i++ )
	{
		fputs ( end[i], out );
		fputs ( "\n", out   );
	}

	fclose ( out );
}

 //Welcom,Guest!
void greetprint ( ) {

	printf("Âàñ ïðèâåòñòâóåò ïðîãðàììà 'Ñòèõîìàíèÿ v1.2' @Samir\n\n");
	printf("Íàæìèòå 1,  åñëè õîòèòå çàïèñàòü â ôàéë îðèãèíàëüíûé  òåêñò\n");
	printf("Íàæìèòå 2,  åñëè õîòèòå ïðèìåíèòü ñîðòèðîâêó 'Åâãåíèé Îíåãèí'\n");
	printf("Íàæìèòå 3,  åñëè õîòèòå ñäåëàòü ñëîâàðü ðèôì\n");
	printf("Íàæìèòå ëþáóþ äðóãóþ äëÿ òîãî,÷òîáû âûéòè\n\n\n");
	printf("\n") ;

}

//Áûñòðàÿ ñîðòèðîâêà
void quickSort ( char **end, int l, int r, int * end1,int f )
{

	char  **buffer = (char**)malloc(sizeof(*buffer));
	assert ( buffer );
    int top = 0;
    int i = l;
    int j = r;
    while ( i <= j )
   {

        while ( ( compare ( end[ i ], end[ ( l + r ) / 2 ], end1[ i ], end1 [ ( r + l ) / 2 ] ,f )  < 0 ) && ( i < r ) ) i++;
        while ( ( compare ( end[ j ], end[ ( l + r ) / 2 ], end1[ j ], end1 [ ( l + r ) / 2 ] ,f )  > 0 ) && ( j > l ) ) j--;
        if    ( i <= j )
        {
			if ( f == -1 )
			{
				top = end1[ i ];
				end1[ i ] = end1[ j ];
				end1[ j ] = top;
			}

            *buffer  = end[ i ];
            end[ i ]   = end[ j ];
            end[ j ]   = buffer[ 0 ];

            i++;
            j--;

        }
   }
	if ( i < r )
	{
		if( f == 1 )
		quickSort ( end, i, r, end1,f );
		else
			quickSort( end, i, r, f );

	}
	if ( l < j )
	{
	if ( f == 1 )
        quickSort ( end, l, j, end1,f ) ;
	else
        quickSort ( end, l, j,f );
	}
}

//Ñðàâíåíèå ñèìâîëîâ  â ñòðîêàõ
int compare ( char *Text1, char* Text2, int len1 = 0, int len2 = 0, int f = -1 )
{
    int compare  = 0;
    int count1     = 0;
	int count2     = 0;
	while ( Text1 && Text2 )
	{
        assert( Text1 );
        assert( Text2 );
        if (     Text1 [ ( len1 - count1 ) * f ] > 64  && Text2 [ (len2 - count2) * f ] > 64 ) {
			if ( Text1 [ ( len1 - count1 ) * f ] < Text2 [ (len2 - count2) * f ] )
			{
				compare--;
				break;
			}
			else if ( Text1 [ (len1 - count1) * f ] > Text2 [ (len2 - count2) * f ] )
			{
            compare++;
			break;
			}
				else
				{
					if ( Text1 [ (len1 - count1) * f ] == Text2 [ (len2 - count2) * f ] )
					{
						++count1;
						++count2;

						if ( Text1 [ (len1 - count1) * f ] == '\0' && Text2 [ (len2 - count2) * f ]	== '\0' )
						{
							break;
						}

						if ( Text1 [ (len1 - count1) * f ] == '\0' )
						{
							compare--;
							break;
						}

						if ( Text2 [ (len2 - count2) * f ] == '\0' )
						{
							compare++;
							break;
						}
					}
				}
	}
	else  {

			if ( Text1 [ (len1 - count1) * f ] <= 64 )
               count1++;
			if ( Text2 [ (len2 - count2) * f ] <= 64 )
               count2++ ;
		  }
}
	return compare;
}
