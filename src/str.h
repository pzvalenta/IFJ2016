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

//////////////EXTERNAL FUNCTIONS//////////////

//returns pointer to new struct. null if not enough memory
String *newString(void);

//appends char c at the end of string str. If string is not big enough, it's resized
void appendChar(String *str, char c);

//destroys string. frees all memory
void destroyString(String *string);

///////////////////////////////////////////////




//////////////INTERNAL FUNCTIONS//////////////

void resizeString(String *string);

void destroyStringData(String *string);

String *copyString(String* old);

///////////////////////////////////////////////


#endif
