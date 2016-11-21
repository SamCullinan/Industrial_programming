#pragma once
#include <stdio.h>
#include "list.h"



const int MAX_TAB_SIZE = 800;

struct Hash_t
{
	List_t List[MAX_TAB_SIZE];
	unsigned int(*HashFunc) (Data_t* Data);
};


int HashTab_ctor (Hash_t* HashTab, unsigned int(*HashFunc) (Data_t* Data));
int HashTab_dtor (Hash_t* HashTab);
int HashTab_OK   (Hash_t* HashTab);
int HashTab_Dump (Hash_t* HashTab);

int AddElem(Hash_t* HashTab, Data_t* Data);

unsigned int HashFunc_1(Data_t* Data);
unsigned int HashFunc_2(Data_t* Data);
unsigned int HashFunc_3(Data_t* Data);
unsigned int HashFunc_4(Data_t* Data);
unsigned int HashFunc_5(Data_t* Data);
