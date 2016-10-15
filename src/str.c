#include <stdio.h>
#include <string.h>

#include "str.h"

#define BASE_STRING_SIZE 4

struct _String{
	int len;
	int size;
	char * data;
};


// returns pointer to an array of chars BASE_STRING_SIZE long
String *newString(int size){
	String *ret = (String *) malloc(sizeof(String));
	if (ret == NULL) return NULL;

	ret->data = (char *) malloc(sizeof(char));
	if (ret->data == NULL){
		return NULL;
		destroyString(ret);
	}

	ret->size = size;
	ret->len = 0;
	return ret;
}

// doubles the size of a char array
// char *resizeString(char *string){
// 	char *ret = (char *) realloc(string, 2*(strlen(string)+1));
// 	if (ret == NULL){
// 		char *ret2 = (char *) malloc(2*(strlen(string)+1)); //TODO je toto nunte?
// 		if (ret2 == NULL)
// 			return NULL;
// 		else
// 			return ret2;
// 	}
// 	else
// 		return ret;
// }

// char *copyString(char *old){
// 	char *ret = newString(strlen(old));
// 	strcpy(ret, old);
// 	return ret;
// }

//TODO
void appendChar(String *str){

}
