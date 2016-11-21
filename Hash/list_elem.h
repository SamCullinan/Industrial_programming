#pragma once
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


const int MAX_ELEM_SIZE = 100;

typedef char Data_t;

struct Listelem_t
{
	Data_t* Data;
	Listelem_t* prev;
	Listelem_t* next;
};

int ListElem_ctor(Listelem_t* Elem, Data_t* Data);
int ListElem_dtor(Listelem_t* Elem);

int ListElem_OK(const Listelem_t* Elem);
int ListElem_Dump(const Listelem_t* Elem, int count);

int PrintData(char* Data);
int PrintData(int*  Data);

int Compare(Listelem_t* Elem, const char* Data);

int Add(Listelem_t* Elem_1, Listelem_t* Elem_2);

