#ifndef HEADER_STRING
#define HEADER_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"



struct String{
	int len;
	int type;
	int size;
	char * data;
};




//////////////EXTERNAL FUNCTIONS//////////////

//returns pointer to new struct. null if not enough memory
struct String *newString(void);

//appends char c at the end of string str. If string is not big enough, it's resized
void appendChar(struct String *str, char c);

//destroys string. frees all memory
void destroyString(struct String *string);


struct String *eraseString(struct String *in);

///////////////////////////////////////////////




//////////////INTERNAL FUNCTIONS//////////////

struct String *resizeString(struct String *string);

void destroyStringData(struct String *string);

struct String *copyString(struct String *old);

void *GetDataofString (struct String *str);

struct String *concatenate(struct String *str1, struct String *str2);

///////////////////////////////////////////////


#endif
