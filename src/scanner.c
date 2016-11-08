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



#include "scanner.h"

#define TABLE_SIZE  32 // pocet prvku v tabulce klicovych slov
#define KEYWORDS    17 // pocet klicovych slov
//#define MAX_ESCAPE  377 // maximalni hodnota escape sekvence //TODO overflow error. musi to byt mensi jak 255

<<<<<<< HEAD

=======
SymTableNode *root = NULL;
FILE* file;

void set_file(FILE *source){
file = source;
}
>>>>>>> origin/master
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
    S_ESCAPE_N,
    S_ESCAPE_N2,
    S_NUM_DOT,
    S_NUM_DOT_NUM,
    S_NUM_EX,
    S_NUM_EX_NUM,
};

String *string = NULL;


const char* klicova_slova [TABLE_SIZE] = { //tabulka klicovych slov
  "boolean"		,"break"	,"class",
  "continue"	,"do"       ,"double",
  "else"        ,"false"	,"for",
  "if"		    ,"int"	    ,"return",
  "String"	    ,"static"	,"true",
  "void"	    ,"while",
};

int isWhiteSpace(char c){
  if(c == ' ' || c == '\t') return 1; //.......
  else return 0;
}

Token * getToken()
{


    Token *ret = newToken();

    int current_char; //aktualne nacitany znak
    int state = S_START; //pocatek automatu


    (*ret).id = START;
    (*ret).data.s = NULL;

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
           string = newString();
           appendChar(string, current_char);
           state = S_IDENT;
        }
        else if (isdigit(current_char) != 0) { //pokud to je cislo
           string = newString();

            state = S_NUM;
        }
        else if (current_char == '+'){
            ret->id = T_PLUS;
            return ret;
        }
        else if (current_char == '-'){
            ret->id = T_MINUS;
            return ret;
        }
        else if (current_char == '*'){
            ret->id = T_MUL;
            return ret;
        }
        else if (current_char == '('){
            ret->id = T_LBRACKET;
            return ret;
        }
        else if (current_char == ')'){
            ret->id = T_RBRACKET;
            return ret;
        }
        else if (current_char == '{'){
            //printf("debug, {\n");
            ret->id = T_LCBRACKET;
            return ret;
        }
        else if (current_char == '}'){
            ret->id = T_RCBRACKET;
            return ret;
        }
        else if (current_char == '['){
            ret->id = T_LSBRACKET;
            return ret;
        }
        else if (current_char == ']'){
            ret->id = T_RSBRACKET;
            return ret;
        }
        else if (current_char == ';'){
            ret->id = T_SEMICLN;
            return ret;
        }
        else if (current_char == ','){
            ret->id = T_COMMA;
            return ret;
        }
        else if (current_char == '.'){
            ret->id = T_DOT;
            return ret;
        }
        else if (current_char == EOF){
            ret->id = T_END;
            return ret;
        }

/*..............................................*/

        else if (current_char == '>'){
            //printf("debug, char: %c\n", current_char);
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
            state = S_SLASH;
            //alokovat pamet (add char)
        }
        else if (current_char == '"'){
            string = newString();
            state = S_STRING;
        }
        break;

/*..............................................*/




    case S_GREATER:
        if (current_char == '='){
            ret->id = T_GEQUAL; // >=
            return ret;
        }
        else if (current_char == '\n'){
            ret->id = T_GREAT; // >
            //printf("DEBUG GREAT\n");
            return ret;
        }
        break;
    case S_LESS:
        if (current_char == '='){
            ret->id = T_LEQUAL;
            return ret; // <=
        }
        else if (current_char == '\n'){
            ret->id = T_LESS;
            return ret; // <
        }
        break;
    case S_EXCLAIM:
        if (current_char == '='){
            ret->id = T_EXCLAIM;
            return ret; // !=
        }
        else if (current_char == '\n'){
            goto Error_lex;     //pokud za vykricnikem nic neni
        }
        break;

    case S_EQUAL:
        if (current_char == '='){
            ret->id = T_EQUAL;
            return ret; // ==
        }
        else if (isWhiteSpace(current_char)){
           ret->id = T_ADD;
            return ret;        // =
        }
        break;

/*................KOMENTARE.................*/
    case S_SLASH: // /
        if (current_char == '/'){ // // - radkovy komentar
            do{
                if (current_char != '\n' || current_char != EOF){
                    break;
                }
              current_char = getc(file);
            }while (current_char != '\n' || current_char != EOF);
        }
        else if (current_char == '*'){  // /* - zacatek blokoveho komentare
            state = S_BL_COMM;
        }
        else if (current_char == '\n'){ // pouze lomitko
            ret->id = T_SLASH;
            return ret;     // /
        }
        break;


    case S_BL_COMM: // /*
        // kdyz je komentar, scanner ho ignoruje -> rozpoznat a jit na start
        while (1) {     //nekonecny cyklus nacitani dalsich znaku
        current_char = getc(file); //nacitani znaku
            if (current_char == '*'){ /* pokud se dalsi nacteny znak bude rovnat hvezdicce,
                otestujeme, zda se dalsi znak rovna /. Pokud ano, ukoncime cyklus*/
                current_char = getc(file);
                if (current_char == '/'){
                    break;
            }
            }
            else if (current_char == EOF){
                // vypsat chybovou hlasku na stderr
                goto Error_lex;
            }




        }
        state = S_START;
        break;

/*...............IDENTIFIKATOR x KLICOVE SLOVO...............*/

    case S_IDENT: // identifikator nebo klicove slovo -> zacina znakem, podtrzitkem nebo dolarem
        if ((isalnum(current_char)) != 0 || current_char == '$' || current_char == '_'){
           appendChar(string, current_char);
            // ERROR
            state = S_IDENT;
        }
        else if( current_char == ';' || current_char == '.' || current_char == '/' || current_char == '+' || current_char == '-' ||
                (isspace(current_char) != 0) || current_char == '*' || current_char == '<'|| current_char == '>' ||
                current_char == ',' || current_char == '('|| current_char == ')' || current_char == '^' || current_char == '='|| current_char == '~' ||
                current_char == '{'|| current_char == '}'|| current_char == '['|| current_char == ']' ){ //
           // neni identifikator
            ungetc(current_char, file); // vrati posledni znak zpet do souboru, takze dalsi funkce jej precte znovu

                 for (int a = 0; a < KEYWORDS; a++){
                      //printf("DEBUG %s\n", string->data);
                     if ((strcmp(string->data, klicova_slova[a])) == 0) /****JAK POZNAT TO, CO MAM NACTENO***/
                         { //je to klicove slovo
                           //printf("Comparing with %s\n", klicova_slova[a]);
                         ret->id = T_KEY + a + 1; //vrati presny odkaz na dane klicove slovo
                         destroyString(string);
                         return ret;
                
                         }
                 }
        ret->id = T_IDENT;
<<<<<<< HEAD
        SymTableNode *root = NULL;
        SymTableNode *node = newSymTableNode(ret, ident_string);
=======

        SymTableNode *node = newSymTableNode(ret, string);
>>>>>>> origin/master
        root = insertSymTableNode(root, node);
        ret->data.s = (String *)node;
        return ret;
        }
        else {
            goto Error_lex;
        }
        break;
/*........................STRING......................*/
    case S_STRING: // "
            if (current_char == '"'){
                ret->id = T_STRING;
                return ret;
            }
            else if (current_char == '\\'){ /*   "..\    */
                state = S_ESCAPE;
            }
            else {
                appendChar(string, current_char);

                state = S_STRING; //dokud bude nacitat string, tak cykli
            }

            break;

/*........................ESCAPE......................*/
    case S_ESCAPE:
        if (current_char == 'n'){
            appendChar(string, current_char);
            state = S_STRING;
        }
        else if (current_char == 't'){
             appendChar(string, current_char);
            state = S_STRING;
        }
         else if (current_char == '\\'){
             appendChar(string, current_char);
            state = S_STRING;
        }
         else if (current_char == '\"'){
             appendChar(string, current_char);
            state = S_STRING;
        }
         else if (current_char == 't'){
             appendChar(string, current_char);
            state = S_STRING;
        }
        else if (isdigit(current_char) < 4){ // je to cislo, mensi

            state = S_ESCAPE_N;

        }
        else{
            goto Error_lex;
        }
        break;


    case S_ESCAPE_N:
        if (isdigit(current_char) < 8){ // \0-30-7

            state = S_ESCAPE_N2;
        }
        else {
            goto Error_lex;
        }
        break;


    case S_ESCAPE_N2:
        if (isdigit(current_char) < 8){ // \0-30-70-7
            //
            state = S_STRING;
        }
        else {
            goto Error_lex;
        }
        break;
/*.........................CISLO......................*/
    case S_NUM: // cislo
        if (isdigit(current_char) != 0 ) {
            appendChar(string, current_char);
            // ERROR
            state = S_NUM;
        }
        else if (current_char == '.'){  // desetinna tecka
           appendChar(string, current_char);
            // jinak error
            state = S_NUM_DOT;
        }
        else if (current_char == 'e' || current_char == 'E'){ // exponent
            appendChar(string, current_char);
            // jinak error
            state = S_NUM_EX;
        }

        else {
            ungetc(current_char, file);
            ret->id = T_NUMBER_I;
            return ret;

        }
        break;



    case S_NUM_DOT: // 0-9.
        if (isdigit(current_char) != 0 ) { // test na cislo
             appendChar(string, current_char);
            //jinak error
            state = S_NUM_DOT_NUM;
        }
        else {
            //ERROR
        }
        break;


    case S_NUM_DOT_NUM: // 0-9.0-9
        if (isdigit(current_char) != 0 ) { // test na cislo
             appendChar(string, current_char);
            //jinak error
            state = S_NUM_DOT_NUM;
        }
        else if ( (current_char == 'e') || (current_char = 'E')){
             appendChar(string, current_char);
            //jinak error
            state = S_NUM_EX;
        }
        else {
          ungetc(current_char, file);
          ret->id = T_NUMBER_D;
            return ret;
        }
        break;

    case S_NUM_EX: //0-9eE || 0-9.0-9Ee
        if (current_char == '+' || current_char == '-' || (isdigit(current_char)) != 0) {
            // dalsi znak je +,- nebo dalsi cislo
            appendChar(string, current_char);

            state = S_NUM_EX_NUM;
        }
        else {
            //error
        }
        break;

    case S_NUM_EX_NUM: //0-9eE+-0-9 || 0-9.0-9Ee+-0-9
        if (isdigit(current_char) != 0) {
            state = S_NUM_EX_NUM; // dokud budou nacitana cisla - cyklus
            appendChar(string, current_char);
        }
        else {
            ungetc(current_char, file);
            ret->id = T_NUMBER_D;
            return ret;
            destroyString(string);
        }

        break;



/*......................................................*/

    } // konec switch



    } // konec while


Error_lex: //chyba



// vratit token, uvolnit posledni string








return ret;
}
