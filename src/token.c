#include <stdio.h>
#include "token.h"

struct _Token{
	char id; // na to nase id nam staci jeden byte
	union{ // union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; // int
		double f; // float
		char * s; // string
		// pomoci tohoto pointeru budeme predavat bud text, nebo ukazatel do tabulky hodnot
	} data;
};

Token *newToken(){
	Token *ret = malloc(sizeof(Token));
	if (ret == NULL){
		fprintf("Not enought memory, can't alloc.\n",stderr);
		return NULL;
	}
	ret->id = NULL;
	return ret;
}


void destroyToken(Token *token){ //TODO
	if (token != NULL){
		if (token->id == 101 || token->id ==  ............) /// jestlize jde o token ktery ma v union zabrany ukazatel s, musim uvolnit tento ukazatel
			free(token->s)
		free(token)
	}
}
	
	
	
	
