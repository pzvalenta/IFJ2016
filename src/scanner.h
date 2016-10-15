/** Prekladac jazyka IFJ16
 *  Projekt do predmetu IFJ a IAL
 *  VUT FIT Brno, 2016
 *
 *  Tym 051, varianta a/2/I
 *  Autori:
 *      Petr Valenta
 *      Eliska Kadlecova
 *      Daniel Doubek
 *      Martin Kovarik
 *      Petr Jares
 *
 */

#ifndef SCANNER
#define SCANNER

#define T_IDENT         101
#define T_KEY           200

#define T_NUMBER_I      301
#define T_NUMBER_D      302
#define T_STRING        303


#define T_END           001

#define T_EQUAL         401
#define T_ADD           402
#define T_PLUS          403
#define T_GREAT         405
#define T_GEQUAL        406
#define T_MINUS         407
#define T_LESS          409
#define T_LEQUAL        410
#define T_MUL           411
#define T_EXCLAIM       414
#define T_SLASH         415

#define T_LBRACKET      501
#define T_RBRACKET      502
#define T_LCBRACKET     503
#define T_RCBRACKET     504
#define T_LSBRACKET     505
#define T_RSBRACKET     506
#define T_SEMICLN       507
#define T_COMMA         508
#define T_DOT           509

typedef struct _Token {
	char id; //na to nase id nam staci jeden byte
	union{ //union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; //int
		double f; //float
		char * s; //string
		//pomoci tohoto pointeru budeme predavat bud text, nebo ukazatel do tabulky hodnot
	}data;
} Token;

#endif // SCANNER
