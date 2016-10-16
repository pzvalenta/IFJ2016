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
String *newString(){
	String *ret = (String *) malloc(sizeof(String));
	if (ret == NULL) return NULL; //TODO handle error

	ret->data = (char *) malloc(BASE_STRING_SIZE*sizeof(char));
	if (ret->data == NULL){
		return NULL; //TODO handle error
		destroyString(ret);
	}
	else
		ret->data[0]='\0';

	ret->size = BASE_STRING_SIZE;
	ret->len = 0;
	return ret;
}

void resizeString(String *string){
	size = string->size;
	len = string->len;
	char *new = (char *) realloc(string, 2*size));
	if (new == NULL){
		char *new2 = (char *) malloc(2*size); //TODO je toto nunte?
		if (new2 == NULL)
			return NULL; //TODO handle error
		else {
			strcpy(new2, string->data);
			destroyStringData(string);
			str->data = new2;
			str->size = 2*size;
			str->len = len;
			return;
		}
	}
	else {
		destroyStringData(string);
		str->data = new;
		str->size = 2*size;
		str->len = len;
		return;
	}
}


void appendChar(String *str, char c){
	if (str->len + 1 >= str->size) resizeString(str);

	str->data[str->len++] = c;
	str->data[len] = '\0';
}

void destroyStringData(String *string){
	free(string->data);
	string->data = NULL;
	string->len = -1;
	string->size = -1;
}

void destroyString(String *string){
	destroyStringData(string);
	free(string);
}
