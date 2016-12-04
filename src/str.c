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
//vytazeni hodnot ze stringu (konverze typu)
void *GetDataofString (String *str){
	if(str->type == T_NUMBER_D){
		double *dbl_num = malloc(sizeof(double));
		sscanf(str->data, "%lf", &dbl_num);
		return (void*) dbl_num;
	}
	if(str->type == T_NUMBER_I){
		int *int_num = malloc(sizeof(int));;
		sscanf(str->data, "%d", &int_num);
		return (void*) int_num;
	}
	if(str->type == T_STRING_L){
		String *str = newString(*str);
		str = copyString(*str);
		return str;
	}
}


String *copyString(String *old){
	if (old == NULL) return NULL;
	String *new = newString();

	for(int i = 0; i < old->len; i++){
		appendChar(new, old->data[i]);
	}

	return new;
}


String *concatenate(String *str1, String *str2){
	char *s1 = NULL;
	char *s2 = NULL;
	if(str1->type != T_STRING_L){
		void* s = GetDataofString(str1);
		s1 = (char*) s;
		s2 = str2->data;
	}
	if(str2->type != T_STRING_L){
		void* s = GetDataofString(str2);
		s2 = (char*) s;
		s1 = str2->data;
	}
	if((str1->type != T_STRING_L) && (str1->type != T_STRING_L)){
		s1 = str1->data;
		s2 = str2->data;
	}
	else{
		return E_TYP;
	}

	s1 = (char*) realloc(s1, strlen(s1) + strlen(s2) + 1);
	if(s1 == NULL){ //chyba pri realokaci pameti
		return NULL;
	}
	strcat(s1, s2);
	str1->data = s1;
	str1->size = /*TODO*/;
	str1->len = /*TODO*/;
	return str1;
}
