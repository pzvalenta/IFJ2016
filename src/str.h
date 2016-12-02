#ifndef HEADER_STRING
#define HEADER_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _String{
	int len;
	int type;
	int size;
	char * data;
} String;


typedef struct _Token{
	char id; // na to nase id nam staci jeden byte
	union{ // union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; // int
		double f; // float
		String *s; // string
		// pomoci tohoto pointeru budeme predavat bud text, nebo ukazatel do tabulky hodnot
	} data;
} Token;
//////////////EXTERNAL FUNCTIONS//////////////

//returns pointer to new struct. null if not enough memory
String *newString(void);

//appends char c at the end of string str. If string is not big enough, it's resized
void appendChar(String *str, char c);

//destroys string. frees all memory
void destroyString(String *string);


String *eraseString(String *in);

///////////////////////////////////////////////




//////////////INTERNAL FUNCTIONS//////////////

String *resizeString(String *string);

void destroyStringData(String *string);

String *copyString(String* old);

void *GetDataofString (String *str);

String *concatenate(String *str1, String *str2);

///////////////////////////////////////////////


#endif
