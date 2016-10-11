#include <stdio.h>
#include <string.h>

#include "str.h"

#define BASE_STRING_SIZE 4

// returns pointer to an array of chars BASE_STRING_SIZE long
char *newString(){
	char *ret = (char *) malloc(BASE_STRING_SIZE*sizeof(char));
	if (ret == NULL) return NULL;
	return ret;
}

// doubles the size of a char array
char *resizeString(char *string){
	char *ret = (char *) realloc(string, 2*strlen(string));
	if (ret == NULL){
		char *ret2 = (char *) malloc(2*strlen(string));
		if (ret2 == NULL)
			return NULL;
		else
			return ret2;
	} 
	else 
		return ret;
}