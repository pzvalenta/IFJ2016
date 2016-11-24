#include "str.h"

#define BASE_STRING_SIZE 4




// returns pointer to an array of chars BASE_STRING_SIZE long
String *newString(){
	String *ret = (String *) malloc(sizeof(String));
	if (ret == NULL) return NULL; //TODO handle error

	ret->data = (char *) malloc(BASE_STRING_SIZE*sizeof(char));
	if (ret->data == NULL){
		destroyString(ret);
		return NULL; //TODO handle error
	}


	else
		ret->data[0]='\0';


	ret->size = BASE_STRING_SIZE;
	ret->len = 0;

	return ret;
}

String *resizeString(String *string){
	int size = string->size;
	int len = string->len;
	char *new = realloc(string->data, 2*size*sizeof(char));
	if (new == NULL) printf("ERROR\n");
	// if (string == NULL){
	// 	// char *new2 = (char *) malloc(2*size*sizeof(char)); //TODO je toto nunte?
	// 	// if (new2 == NULL)
	// 	// {
	// 	// 	printf("ERROR\n");
	// 	// 	return NULL; //TODO handle error
	// 	// }
	// 	// else {
	// 	// 	strcpy(new2, string->data);
	// 	// 	destroyStringData(string); //TODO je toto nutne?
	// 	// 	string->data = new2;
	// 	// 	string->size = 2*size;
	// 	// 	string->len = len;
	// 	// 	return;
	// 	// }
	// 	printf("ERROR\n");
	// 	string->size = 2*size;
	// 	string->len = len;
	// 	return ret;
	// }
	// else {
	string->data = new;
		string->size = 2*size;
		string->len = len;
		return string;
	// }
}

void appendChar(String *str, char c){
	if (str->len + 1 >= str->size) resizeString(str);

	str->data[str->len++] = c;
	str->data[str->len] = '\0';

	//TODO realloc on string end
}

void destroyStringData(String *string){
	if (string->data != NULL){
		free(string->data);
		string->data = NULL;
	}

	string->len = -1;
	string->size = -1;
}

void destroyString(String *string){
	if (string == NULL) return;
	destroyStringData(string);
	free(string);
	string = NULL;
}

String *eraseString(String *in){
	destroyStringData(in);

	in->data = (char *) malloc(BASE_STRING_SIZE*sizeof(char));
	if (in->data == NULL){
		destroyString(in);
		fprintf(stderr ,"erase string malloc error\n");
		return NULL; //TODO handle error
	}
	else
		in->data[0]='\0';

	in->size = BASE_STRING_SIZE;
	in->len = 0;
	return in;
}


//TODO navratova hodnota z realloc
// String *copyString(String* old){
// 	String *new = newString();
//
// 	if (old->size > BASE_STRING_SIZE)
// 		new->data = realloc(new->data, old->size*sizeof(char)); //TODO handle error
//
// 	new->size = old->size;
// 	new->len = old->len;
// 	strcpy(new->data, old->data);
// 	return new;
// }
