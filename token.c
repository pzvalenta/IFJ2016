//Zitra pripisu kod pro rozsirovani alokovane pameti pro char * s.
//Jednou z moznosti je stale ten zasobnik. Ptal jsem se jednoho lonskeho tymu, a ti to meli vyreseno jednodusse globalni promenou.



//Pro testovani pouzijte tuto strukturu.
typedef struct{
	char id; //na to nase id nam staci jeden byte
	union{ //union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; //int
		double f; //float
		char * s; //string
		//pomoci tohoto pointeru budeme predavat bud text, nebo ukazatel do tabulky hodnot
	};
} Token;


//nez se rozhodnu jak dal, volejte v testovani scanner pomoci funkce s nasledujicim predpisem:
Token * getToken(); 





//Prototypy funkci pro praci se strukturou
Token * newToken(){
	Token * ret = malloc(sizeof(Token));
	if (ret == NULL)
		printf("nedostatek pameti\n"); //error
		return NULL;
	ret->id = NULL;
	return ret;
}

void destroyToken(Token * token){ //TODO
	if (token != NULL){
		if (token->id == 101 || token->id ==  ............) /// jestlize jde o token ktery ma v union zabrany ukazatel s, musim uvolnit tento ukazatel
			free(token->s)
		free(token)
	}
}
	
	
	
	
