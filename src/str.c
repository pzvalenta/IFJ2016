#include "str.h"

#define BASE_STRING_SIZE 4




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
	int size = string->size;
	int len = string->len;
	realloc(string, 2*size*sizeof(char));
	if (string == NULL){
		char *new2 = (char *) malloc(2*size*sizeof(char)); //TODO je toto nunte?
		if (new2 == NULL)
			return NULL; //TODO handle error
		else {
			strcpy(new2, string->data);
			destroyStringData(string); //TODO je toto nutne?
			string->data = new2;
			string->size = 2*size;
			string->len = len;
			return;
		}
	}
	else {
		string->size = 2*size;
		string->len = len;
		return;
	}
}

void appendChar(String *str, char c){
	if (str->len + 1 >= str->size) resizeString(str);

	str->data[str->len++] = c;
	str->data[str->len] = '\0';

	//TODO realloc on string end
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

String *copyString(String* old){
	String *new = newString();

	if (old->size > BASE_STRING_SIZE)
		realloc(new->data, old->size*sizeof(char)); //TODO handle error

	new->size = old->size;
	new->len = old->len;
	strcpy(new->data, old->data);
	return new;
}
