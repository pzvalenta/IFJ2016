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



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"

#define TABLE_SIZE  32 // pocet prvku v tabulce klicovych slov
#define KEYWORDS    17 // pocet klicovych slov
#define MAX_ESCAPE  377 // maximalni hodnota escape sekvence

//SEZNAM STAVU:
enum {
    S_START = 0,
    S_IDENT,
    S_NUM,
    S_GREATER,
    S_LESS,
    S_EXCLAIM, // !=
    S_SLASH,
    S_EQUAL,
    S_STRING,
    S_BL_COMM,  // /*..*/
    S_ESCAPE,
    S_NUM_DOT,
    S_NUM_DOT_NUM,
    S_NUM_EX,
    S_NUM_EX_NUM,
};

int line = 1; //pocitadlo radku

const char* keywords[TABLE_SIZE] = { //tabulka klicovych slov - PREDELAT NA MALA PISMENA!!!!!
  "BOOLEAN"		,"BREAK"	,"CLASS",
  "CONTINUE"	,"DO"       ,"DOUBLE",
  "ELSE"        ,"FALSE"	,"FOR",
  "IF"		    ,"INT"	    ,"RETURN",
  "STRING"	    ,"STATIC"	,"TRUE",
  "VOID"	    ,"WHILE",
};

int init_string(T_STRING* s) //DODELAT!!!!!
{
/*Funkce pro inicializaci stringu. Vytvori pamet o velikost SIZE. Return 0 v pripade uspechu*/

	/*if ( (s->string = (char*)malloc(DAVKA)) == NULL )
	{//pokud se alokace nepodarila
		return 1;
	}

	/*s->string[0] = '\0';
	s->alloc_size = DAVKA;              ????
	s->lenght = 0;
	*/

	return 0;
}


Token * getToken(FILE *file)
{
    Token *ret = newToken();
    int current_char; //aktualne nacitany znak
    int state = S_START; //pocatek automatu

    // udelat vychozi stav tokenu

    while (1){

        current_char = getc(file); // v nekonecnem cyklu nacitame znaky

    switch(state){
    case S_START:
        if (isspace(current_char) != 0)
        {
        //testuje, zda je aktualni znak bily znak
        //nic se ale nestane, protoze je ignorujeme
            state = S_START;
        }
        else if ( (isalpha(current_char)) != 0 || current_char == '$' || current_char == '_'){
            //zacina znakem, dolarem nebo podtrzitkem
           //alokovat pamet
           state = S_IDENT;
        }
        else if (isdigit(current_char) != 0) { //pokud to je cislo
            state = S_NUM;
        }
        else if (current_char == '+'){
            ret->id = T_PLUS;
            return ret;
        }
        else if (current_char == '-'){
            return T_MINUS;
        }
        else if (current_char == '*'){
            return T_MUL;
        }
        else if (current_char == '('){
            return T_LBRACKET;
        }
        else if (current_char == ')'){
            return T_RBRACKET;
        }
        else if (current_char == 'EOF'){
            return T_END;
        }

/*..............................................*/

        else if (current_char == '>'){
            state = S_GREATER;
        }
        else if (current_char == '<'){
            state = S_LESS;
        }
        else if (current_char == '!'){
            state = S_EXCLAIM;
        }
        else if (current_char == '='){
            state = S_EQUAL;
        }
        else if (current_char == '/'){
            //alokovat pamet (init string)
            //pokud neni pamet -> error

            state = S_SLASH;
            //alokovat pamet (add char)
        }
        else if (current_char == '"'){
            state = S_STRING;
        }







    case S_GREATER:
        if (current_char == '='){
            return T_GEQUAL; // >=
        }
        else if (current_char == '\n'){
            return T_GREAT; // >
        }
    case S_LESS:
        if (current_char == '='){
            return T_LEQUAL; // <=
        }
        else if (current_char == '\n'){
            return T_LESS; // <
        }
    case S_EXCLAIM:
        if (current_char == '='){
            return T_EXCLAIM; // !=
        }
        else if (current_char == '\n'){
            goto Error_lex;     //pokud za vykricnikem nic neni
        }
        break;

    case S_EQUAL:
        if (current_char == '='){
            return T_EQUAL; // ==
        }
        else if (current_char == '\n'){
           return T_ADD;        // =
        }
/*................KOMENTARE.................*/
    case S_SLASH: // /
        if (current_char == '/'){ // // - radkovy komentar
            return T_LN_COMM;
        }
        else if (current_char == '*'){  // /* - zacatek blokoveho komentare
            state = S_BL_COMM;
        }
        else if (current_char == '\n'){ // pouze lomitko
            return T_SLASH;     // /
            // uvolnit string
        }


    case S_BL_COMM: // /*
        // kdyz je komentar, scanner ho ignoruje -> rozpoznat a jit na start
        while (1) {//nekonecny cyklus nacitani dalsich znaku
        current_char = getc(FILE); //nacitani znaku
            if (current_char == '*'){ /* pokud se dalsi nacteny znak bude rovnat hvezdicce,
                otestujeme, zda se dalsi znak rovna /. Pokud ano, ukoncime cyklus*/
                current_char = getc(FILE);
                if (current_char == '/'){
                    break;
            }
            else if (current_char == EOF){
                // vypsat chybovou hlasku na stderr
                goto Error_lex;
            }

            }


        }
        //uvolneni string
        state = S_START;
        break;

/*...............IDENTIFIKATOR x KLICOVE SLOVO...............*/

    case S_IDENT: // identifikator nebo klicove slovo -> zacina znakem, podtrzitkem nebo dolarem
        if ((isalnum(current_char)) != 0 || current_char == '$' || current_char == '_'){
            // pridat do retezce, jinak error
            // ERROR
        }
        else if(){

        }
/*........................STRING......................*/
    case S_STRING: // "
        while (1){
            current_char = getc(FILE); // nekonecne nacitani dalsich znaku
            if (current_char == '"'){
                return T_STRING;
            }
            else if (current_char == '\\'){
                state = S_ESCAPE;
            }
        }
/*........................ESCAPE......................*/
    case S_ESCAPE:
/*.........................CISLO......................*/
    case S_NUM: // cislo
        if (isdigit(current_char) != 0 ) {
            //pridani do retezce
            // jinak error
        }
        else if (current_char == '.'){  // desetinna tecka
            //pridani do retezce
            // jinak error
            state = S_NUM_DOT;
        }
        else if (current_char == 'e' || current_char == 'E'){ // exponent
            state = S_NUM_EX;
        }
         else if (current_char == '+' || current_char == '-' || current_char == '*' ||
                 current_char == '/' || current_char == '>' || current_char == '<' ||
                 current_char == '=' || isspace(c) != 0) {  // znaky, ktere mohou jit za cislem
            /***DOPLNIT***/

        // uvolnit string
        }
        else {
            //vypis erroru
        }
        break;



    case S_NUM_DOT: // 0-9.
        if (isdigit(current_char) != 0 ) { // test na cislo
            // pridani do retezce
            //jinak error
            state = S_NUM_DOT_NUM;
        }
        else {
            //ERROR
        }
        break;


    case S_NUM_DOT_NUM: // 0-9.0-9
        if (isdigit(current_char) != 0 ) { // test na cislo
            // pridani do retezce
            //jinak error
        }
        else if ( (current_char == 'e') || (current_char = 'E')){
            // pridani do retezce
            //jinak error
            state = S_NUM_EX;
        }
        else if (current_char == '+' || current_char == '-' || current_char == '*' ||
                 current_char == '/' || current_char == '>' || current_char == '<' ||
                 current_char == '=' || isspace(c) != 0) {  // znaky, ktere mohou jit za cislem
            /***DOPLNIT***/

            // uvolnit string
        }
        else {
            //vypis erroru
        }
        break;

    case S_NUM_EX: //0-9eE || 0-9.0-9Ee
        if (current_char == '+' || current_char == '-' || (isdigit(current_char)) != 0) {
            // dalsi znak je +,- nebo dalsi cislo
            state = S_NUM_EX_NUM;
        }
        else {
            //error
        }
        break;

    case S_NUM_EX_NUM: //0-9eE+-0-9 || 0-9.0-9Ee+-0-9
        if (isdigit(current_char) != 0) {
            state = S_NUM_EX_NUM; // dokud budou nacitana cisla - cyklus
        }
        else if (current_char == 'EOF'){
            return T_NUMBER_D;
            // DOPLNIT
            // UVOLNIT PAMET
        }
        else {
            //ERROR
        }
        break;



/*......................................................*/

    } // konec switch

    typedef struct{
	char id; //na to nase id nam staci jeden byte
	union{ //union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; //int
		double f; //float
		char * s; //string
		//pomoci tohoto pointeru budeme predavat bud text, nebo ukazatel do tabulky hodnot
	};
} Token;



    } // konec while


Error_lex: //chyba
//zde budou kroky, ktere se maji provest v pripade chyby


// vratit token, uvolnit posledni string








return ;
}

