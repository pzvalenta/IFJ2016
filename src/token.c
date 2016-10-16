#include <stdio.h>
#include "token.h"
#include "str.h"
#include "scanner.h"



Token *newToken(){
	Token *ret = (String *) malloc(sizeof(Token));
	if (ret == NULL){
		fprintf("Not enought memory, can't alloc.\n",stderr);
		return NULL; //TODO handle error
	}
	ret->id = -1;
	return ret;
}


void destroyToken(Token *token){
	if (token != NULL){
		if (token->id == T_STRING) /// jestlize jde o token ktery ma v union zabrany ukazatel s, musim uvolnit tento ukazatel
			destroyString(token->s);
		else if (token->id == T_IDENT)
			destroySimTableNode(token->s);
		free(token);
		token = NULL;
	}
}
