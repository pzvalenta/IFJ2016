#include "token.h"

Token *newToken(){
	Token *ret = (Token *) malloc(sizeof(Token));
	if (ret == NULL){
		fprintf(stderr,"Not enought memory, can't alloc.\n");
		return NULL; //TODO handle error
	}
	ret->id = -1;
	return ret;
}


void destroyToken(Token *token){
	if (token != NULL){
		if (token->id == T_STRING) /// jestlize jde o token ktery ma v union zabrany ukazatel s, musim uvolnit tento ukazatel
			destroyString(token->data.s);
		//else if (token->id == T_IDENT)
		//	destroySimTableNode(token->data.s);
		free(token);
		token = NULL;
	}
}
