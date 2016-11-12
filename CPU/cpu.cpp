#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <assert.h>
#include "M_Stack.h"


int EIP = 0;
char * InputFile = "";
int StackMaxSize = 1000;

enum Command
{
    #define DEF_CMD_  ( name, num, pref , code ) CMD_##name = num,
    #include "commands.h"
    #undef DEF_CMD_
    CMD_MAX
};

struct CPU
{
    Stack_t Stack;
    Stack_t CallStack;
    #define REGISTER_ ( name, num )  double name = 0;
    #include "registers.h"
    #undef REGISTER_
};

double * readCommandFromFile ( int *commandLength, int *errorNumber    );
int  CPU_ctor                ( CPU *cpu, int stackSize, int maxCommand );
void pushRegister            ( CPU *cpu, int registr                   );
void popRegister             ( CPU *cpu, int registr                   );
void inputToRegister         ( CPU *cpu, double * command              );
void outputFromRegister      ( CPU *cpu, double * command              );
void printCommand            ( double *command                         );
void CPU_dump                ( CPU *cpu                                );

int main()
{
    int error   = 0,
    commandSize = 0;
    double * command = readCommandFromFile( &commandSize, &error );
    assert (  command );

    CPU cpu = {};
    CPU_ctor  ( &cpu, StackMaxSize, commandSize );

    while ( ( EIP < commandSize ) && ( EIP >= 0 ) )
    {
        printCommand( command );
        printf ( "command[eip+1] = %f,  eip = %d, operand = %f\n", command[ EIP + 1 ], EIP, command[ EIP + 1 ] );
        switch ( ( int )command[ EIP ] )
        {
            #define DEF_CMD_( name, num, pref, code ) case num : { code; break; }
            #include "commands.h"
            #undef DEF_CMD_
        }
    }
}

void printCommand( double *command )
{
    int comnd = ( int )command[ EIP ];
    #define DEF_CMD_( name, num, pref , code ) if( comnd == num ) {printf(#name); printf(" ");}
    #include "commands.h"
    #undef DEF_CMD_
}


void pushRegister(CPU *cpu, int registr)
{
    switch (registr)
        {
            #define REGISTER_(name, num) case(num) : {Stack_push(&cpu->Stack, cpu->name); break;}
            #include "registers.h" 
            #undef REGISTER_ 
        }
}


void inputToRegister(CPU *cpu, double * command)
{
    switch ((int)command[EIP + 1])
    {
        #define REGISTER_(name, num) case(num) : {scanf("%lf", &cpu->name); break;}
        #include "registers.h" 
        #undef REGISTER_ 
    }
}


void outputFromRegister(CPU *cpu, double * command)
{
    switch ((int)command[EIP + 1])
    {
        #define REGISTER_(name, num) case(num) : {printf(#name); printf(" %lf \n", cpu->name); break;}
        #include "registers.h" 
        #undef REGISTER_ 
    }
}

void popRegister(CPU *cpu, int registr)
{
    switch (registr)
    {
        #define REGISTER_(name, num) case(num) : {cpu->name = stack_pop(&cpu->Stack); break;}
        #include "registers.h" 
        #undef REGISTER_ 
    }
}


int CPU_OK(CPU *cpu)
{
    if (!Stack_OK(&( cpu->CallStack ))) return 1;
    if (!Stack_OK(&( cpu->Stack )) )return 1;
    return 0;
}


void CPU_dump(CPU *cpu)
{
    printf("Version %d.%d.%d (%s %s)\n\n", 0, 1, 2, __DATE__, __TIME__);
    printf("=================================\n");
    printf("Stack:\n");
    STACK_DUMP(&cpu->Stack);
    printf("Call stack:\n");
    STACK_DUMP(&cpu->CallStack);
    printf("Registers: \n");
    #define REGISTER_(name, num)  printf(#name); printf(" :%lf\n",cpu->name);
    #include "registers.h"
    #undef REGISTER_
    printf("=================================\n");

}


int CPU_ctor(CPU *cpu, int stackSize, int maxCommand)
{
    Stack_t Stack;
    Stack_t	CallStack;
    Stack_construct(&Stack, stackSize);
    Stack_construct(&CallStack, maxCommand);
    cpu->CallStack = CallStack;
    cpu->Stack = Stack;
    return 1;
}


double * readCommandFromFile(int *commandLength, int *errorNumber)
{

    assert(commandLength);
    assert(errorNumber);

    FILE *in= fopen(InputFile, "rb");

    assert(in);
    if (in)
    {
        *commandLength = filelength(fileno(in));
        double *buff = (double *)calloc(*commandLength, sizeof(double));
        double tmpNumb = 0;
        int i = 0;
        while (!feof(in))
        {
            fscanf(in, "%lf", &tmpNumb);
            buff[i] = tmpNumb;
            i++;
        } 
        buff[i - 1] = 0;
        *commandLength = i;
        fclose(in);
        *errorNumber = 0;
        return buff;
    }
    else
    {
        *errorNumber = -1;
        return NULL;
    }

} 