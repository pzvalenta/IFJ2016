#ifndef HEADER_STRING
#define HEADER_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _String{
	int len;
	int size;
	char * data;
} String;

String *newString(void);

void resizeString(String *string);

void appendChar(String *str, char c);

void destroyStringData(String *string);

void destroyString(String *string);

String *copyString(String* old);



#endif
