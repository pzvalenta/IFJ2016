#ifndef HEADER_TOKEN
#define HEADER_TOKEN

typedef struct _Token{
	char id; // na to nase id nam staci jeden byte
	union{ // union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; // int
		double f; // float
		char * s; // string
		// pomoci tohoto pointeru budeme predavat bud text, nebo ukazatel do tabulky hodnot
	} data;
} Token;

Token *newToken();

void destroyToken(Token *token);

#endif
