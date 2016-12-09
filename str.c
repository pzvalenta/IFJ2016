#include "str.h"

#define BASE_STRING_SIZE 4




// returns pointer to an array of chars BASE_STRING_SIZE long
struct String *newString(){
	struct String *ret = (struct String *) malloc(sizeof(struct String));
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

struct String *resizeString(struct String *string){
	int size = string->size;
	int len = string->len;
	char *new = realloc(string->data, 2*size*sizeof(char));
	if (new == NULL) fprintf(stderr,"ERROR\n");
	// if (string == NULL){
	// 	// char *new2 = (char *) malloc(2*size*sizeof(char)); //TODO je toto nunte?
	// 	// if (new2 == NULL)
	// 	// {
	// 	// 	fprintf(stderr,"ERROR\n");
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
	// 	fprintf(stderr,"ERROR\n");
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

void appendChar(struct String *str, char c){
	if (str->len + 1 >= str->size) resizeString(str);

	str->data[str->len++] = c;
	str->data[str->len] = '\0';

	//TODO realloc on string end
}

void destroyStringData(struct String *string){
	if (string->data != NULL){
		free(string->data);
		string->data = NULL;
	}

	string->len = -1;
	string->size = -1;
}

void destroyString(struct String *string){
	if (string == NULL) return;
	destroyStringData(string);
	free(string);
	string = NULL;
}

struct String *eraseString(struct String *in){
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
void *GetDataofString (struct String *str){
	if(str->type == T_NUMBER_D){
		double *dbl_num = malloc(sizeof(double));
		sscanf(str->data, "%lf", dbl_num);
		return (void*) dbl_num;
	}
	if(str->type == T_NUMBER_I){
		int *int_num = malloc(sizeof(int));;
		sscanf(str->data, "%d", int_num);
		return (void*) int_num;
	}
	if(str->type == T_STRING_L){
		struct String *str = newString();
		str = copyString(str);
		return str;
	}
	return NULL;
}


struct String *copyString(struct String *old){
	if (old == NULL) return NULL;
	struct String *new = newString();

	for(int i = 0; i < old->len; i++){
		appendChar(new, old->data[i]);
	}

	return new;
}



struct String *concatenate(struct String *str1, struct String *str2){
    char *s1 = NULL;
    char *s2 = NULL;
    char *s3 = NULL;
    struct String *ret = newString();
    s1 = str1->data;
    s2 = str2->data;

    s3 = (char*) realloc(s1, strlen(s1) + strlen(s2) + 1); //realokace pameti, aby se do s1 vlezlo s1+s2
    if(s3 == NULL){ //chyba pri realokaci pameti
        return NULL;
    }
    s3 = strcpy(s3, s1);
    s3 = strcat(s3, s2); //konkatenace, ulozi se do s3

    ret->data = s3;
    ret->size = strlen(s1) + strlen(s2) + 1;
    ret->len = strlen(s3);
    return ret;

}
