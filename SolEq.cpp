//Этот вариант кода промежуточный, полностью готовый код я показывал тебе на семинаре)
//Ты мне даже зачел ее и мы перешли на Евгения Онегина. К сожалению,он у меня не сохранился.вот все,что от него осталось

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// doxygen.org

//! This constant is the one in the world!!!111!!!111!!!111
//! @warning Do not use it!!!!

const int    INF_Roots = -1 ;
const double EPS       = 0.000001;

int IsZero ( double a );
int SolEq  ( double a, double b, double c, double *x1, double *x2 );
int LinearEq ( double b, double c, double *x1, int nRoots );
int SqEq ( double a, double b, double c, double *x1, double *x2, int nRoots );

int main ()
{
    setlocale ( LC_ALL, " Rus " );
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    printf ( " #Solution of Equation v.1.0(c) Samir, 22.09.2016\n " );
    printf ( " #Ââåäèòå a, b, c: \n " );

    scanf  ( "%lg %lg %lg", &a, &b, &c );
    printf ( " \n " );

    int nRoots = SolEq ( a, b, c, &x1, &x2 );

    // Как я уже говорил, вынеси switch в отдельную функцию.
    switch ( nRoots ) 
		{

            case  2: printf ( " x1 = %lg\n " ,x1 );
                     printf ( " x2 = %lg\n " ,x2 );
                     break;
            case  1: printf ( " x = %lg\n "  ,x1 );
                     break;
            case  0: printf ( " Íåò ðåøåíèÿ " );
                     break;
            case -1: printf ( " Ìíîæåñòâî ðåøåíèé " );
                     break;

            default: printf ( " nRoots íå ðàâåí íè îäíîìó âàðèàíòó. Ñîâåò: Ïðîâåðèòü ïåðåìåííûå " );
                     break;
        }
    return 0;
}

int IsZero ( double  a )
{
    return ( fabs(a) < EPS );
}

//assert
int SolEq (double a, double b, double c, double *x1, double *x2)
{
    if ((x1 != x2 ) && ( x1 != NULL && x2 != NULL ))
    {
        int nRoots = 0;

        if ( IsZero (a) && IsZero (b) )
            return  ( INF_Roots );

        else if ( IsZero (a) )
            nRoots = LinearEq ( b, c, x1, nRoots );

        else if(  !IsZero (a) )
            nRoots = SqEq ( a, b, c, x1, x2, nRoots );

        return nRoots;
    }
    return ( 404 );
}

int LinearEq (double b, double c, double *x1, int nRoots)
{
    //bx+c=0
    *x1 = -c / b;
    nRoots = 1;
    return nRoots;
}

int  SqEq (double a, double b, double c, double *x1, double *x2, int nRoots)
{
        //ax^2+bx+c=0
    double d = b*b - 4*a*c;
    if ( d < 0 )
    {
        nRoots=0;
    }
    if ( IsZero ( d ) )
    {

        *x1 = -b / ( 2*a );
        nRoots = 1;
    }
    if ( d > 0 )
    {

        d = sqrt( d );
        *x1 = ( -b + d ) / ( 2*a );
        *x2 = ( -b - d ) / ( 2*a );
        nRoots = 2;
    }
    return nRoots;
}
