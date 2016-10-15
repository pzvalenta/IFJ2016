#include <stdio.h>
#include "token.h"
#include "str.h"
#include "scanner.h"

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
	Token *ret = (String *) malloc(sizeof(Token));
	if (ret == NULL){
		fprintf("Not enought memory, can't alloc.\n",stderr);
		return NULL;
	}
	ret->id = NULL;
	return ret;
}


void destroyToken(Token *token){
	if (token != NULL){
		if (token->id == T_STRING) /// jestlize jde o token ktery ma v union zabrany ukazatel s, musim uvolnit tento ukazatel
			destroyString(token->s);
		else if (token->id == T_IDENT)
			destroySimTableNode(token->s);
		free(token);
	}
}
