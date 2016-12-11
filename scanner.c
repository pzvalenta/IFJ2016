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

#define TABLE_SIZE 32 // pocet prvku v tabulce klicovych slov
#define KEYWORDS 17   // pocet klicovych slov
#define ASCII 48
//#define MAX_ESCAPE  377 // maximalni hodnota escape sekvence //TODO overflow
// error. musi to byt mensi jak 255

//=======
FILE *file;
struct String *string = NULL;
struct String *helpstring = NULL;
struct tListItem *head = NULL;
struct tListItem *tail = NULL;
int tokenValue = E_LEX;
int radek=1;

void set_file(FILE *source) { file = source; }

void set_token_list(struct tListItem *list) { head = list; }

// SEZNAM STAVU:
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
  S_LN_COMM,
  S_BL_COMM, // /*..*/
  S_ESCAPE,
  S_ESCAPE_N,
  S_ESCAPE_N2,
  S_NUM_DOT,
  S_NUM_DOT_NUM,
  S_NUM_EX,
  S_NUM_EX_NUM,
  S_C_IDENT,
};

const char *klicova_slova[TABLE_SIZE] = {
    // tabulka klicovych slov
    "boolean", "break",  "class", "continue", "do",    "double",
    "else",    "false",  "for",   "if",       "int",   "return",
    "String",  "static", "true",  "void",     "while",
};

int isWhiteSpace(char c) {
  /*
   * test zda neni bily znak
   */
  if (c == ' ' || c == '\t')
    return 1; //.......
  else
    return 0;
}

int insertLastToken() {
  if (head->id == START) {
    head->id = tokenValue;
    head->data = string;
    head->next = NULL;
    head->prev = NULL;
    head->radek=radek;
    tail = head;
  } else {

    // TODO optimalizace, nevkladat string pro tokeny krome identifikatoru a
    // literalu
    struct tListItem *tmp = malloc(sizeof(struct tListItem));
    if (tmp == NULL)
      return E_INTERNAL;
    tmp->prev = tail;
    tmp->next = NULL;
    tmp->data = string;
    tmp->id = tokenValue;
    tmp->radek=radek;
    tail->next = tmp;
    tail = tmp;

  }


  return E_OK;
}

int loadTokens() {
  int result = E_OK;
  do {
    string = newString();
    result = getToken();
    //fprintf(stderr, "string->data: %s\n", string->data);
    if (result != E_OK) {
      //fprintf(stderr, "CHYBA\n");
      destroyString(string);
      return result;
    }

    result = insertLastToken();
    if (result != E_OK) {
      destroyString(string);
      return result;
    }

  } while (tokenValue != T_END);

  return result;
}

int freeTokenList() {
  int result = E_OK;
  struct tListItem *tmp = head;
  struct tListItem *next = NULL;

  while (tmp != NULL) {
    free(tmp->data); // TODO errorcheck
    next = tmp->next;
    free(tmp);
    tmp = next;
  }

  return result;
}

int getToken() {
  /*
   * hlavni funkce scanneru
   */

  // Token *ret = newToken();

  int current_char;    // aktualne nacitany znak
  int state = S_START; // pocatek automatu

  //(*ret).id = START;
  //(*ret).data.s = NULL;
  while (1) {
    /*
     * v nekonecnem cyklu nacitame znaky
     */
    current_char = getc(file);
     fprintf(stderr,"current_char: %c\n", current_char);
     if(current_char=='\n')
      radek++;
    switch (state) {
    case S_START:
    //fprintf(stderr,"case S_START\n");
      if (isspace(current_char) != 0) {
        // testuje, zda je aktualni znak bily znak
        // nic se ale nestane, protoze je ignorujeme
        state = S_START;
      } else if ((isalpha(current_char)) != 0 || current_char == '$' ||
                 current_char == '_') {
                  // fprintf(stderr, "necotamnapis\n");

        // zacina znakem, dolarem nebo podtrzitkem
        // string = eraseString(string);
        // TODO if NULL, handle error
        appendChar(string, current_char);
        state = S_IDENT;
      } else if (isdigit(current_char) != 0) { // pokud to je cislo
        // string = eraseString(string);
        // TODO if NULL, handle error
        state = S_NUM;
        //fprintf(stderr, "go to S_NUM\n");
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
      } else if (current_char == '+') {
        tokenValue = T_PLUS;
        return E_OK;
      } else if (current_char == '-') {
        tokenValue = T_MINUS;
        return E_OK;
      } else if (current_char == '*') {
        tokenValue = T_MUL;
        return E_OK;
      } else if (current_char == '(') {
        tokenValue = T_LBRACKET;
        return E_OK;
      } else if (current_char == ')') {
        tokenValue = T_RBRACKET;
        return E_OK;
      } else if (current_char == '{') {
        // fprintf(stderr,"debug, {\n");
        tokenValue = T_LCBRACKET;
        return E_OK;
      } else if (current_char == '}') {
        tokenValue = T_RCBRACKET;
        return E_OK;
      } else if (current_char == '[') {
        tokenValue = T_LSBRACKET;
        return E_OK;
      } else if (current_char == ']') {
        tokenValue = T_RSBRACKET;
        return E_OK;
      } else if (current_char == ';') {
        tokenValue = T_SEMICLN;
        return E_OK;
      } else if (current_char == ',') {
        tokenValue = T_COMMA;
        return E_OK;
      } else if (current_char == EOF) {
        tokenValue = T_END;
        return E_OK;
      } else if (current_char == '\\'){
        //fprintf(stderr,"debug, {\n");
        tokenValue = T_B_SLASH;
        return E_OK;
      } else if (current_char == '\''){
        tokenValue = T_APOSTROPHE;
        return E_OK;
      }

      /*..............................................*/

      else if (current_char == '>') {
        // fprintf(stderr,"debug, char: %c\n", current_char);
        state = S_GREATER;
      } else if (current_char == '<') {
        state = S_LESS;
      } else if (current_char == '!') {
        state = S_EXCLAIM;
      } else if (current_char == '=') {
        state = S_EQUAL;
      } else if (current_char == '/') {
        //fprintf(stderr,"lomitko, char: %c\n", current_char);
        state = S_SLASH;
        //ungetc(current_char, file);
      } else if (current_char == '"') {
        // string = eraseString(string);
        // TODO if NULL, handle error
        state = S_STRING;
      } else
        return E_LEX;
      break;

    /*..............................................*/

    case S_GREATER:
    //ungetc(current_char, file);
      if (current_char == '=') {
        //fprintf(stderr,"T_GEQUAL %c\n", current_char);
        tokenValue = T_GEQUAL; // >=
        return E_OK;
      } else /*if (current_char == '\n')*/ {
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        //fprintf(stderr,"T_GREAT %c\n", current_char);
        tokenValue = T_GREAT; // >
        return E_OK;
      }
      break;

    case S_LESS:
    //ungetc(current_char, file);
      if (current_char == '=') {
        //fprintf(stderr,"T_LEQUAL %c\n", current_char);
        tokenValue = T_LEQUAL; // <=
        return E_OK;
      } else /*if (current_char == '\n')*/ {
        //fprintf(stderr,"LESS %c\n", current_char);
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        tokenValue = T_LESS; // <
        return E_OK;
      }
      break;

    case S_EXCLAIM:
    //ungetc(current_char, file);
      if (current_char == '=') {
        //fprintf(stderr,"T_EXCLAIM %c\n", current_char);
        tokenValue = T_EXCLAIM; // !=
        return E_OK;
      } else /*if (current_char == '\n')*/ {
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        //fprintf(stderr,"spatne: %c\n", current_char);
        return E_LEX;
      }
      break;

    case S_EQUAL:

    //fprintf(stderr,"ted: %c\n", current_char);
      if (current_char == '=') {
        //fprintf(stderr, "T_EQUAL\n");
        tokenValue = T_EQUAL; // ==
        return E_OK;
      } else /*if (isWhiteSpace(current_char))*/ {
        //fprintf(stderr, "T_ADD\n");
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        tokenValue = T_ADD; // =
        return E_OK;
      }
      break;

    case S_SLASH: // /
    if(current_char=='\n')
      radek--;
    ungetc(current_char, file);
    //fprintf(stderr,"s_slash\n");
    //fprintf(stderr,"ted: %c\n", current_char);
      if (current_char == '/') {
        //fprintf(stderr,"s_ln_comm\n");
        state = S_LN_COMM;              // prejdi na stav radkoveho komentare
      } else if (current_char == '*') { // /* - zacatek blokoveho komentare
        //fprintf(stderr,"S_BL_COMM\n");
        state = S_BL_COMM;
      } else { // pouze lomitko
        //fprintf(stderr,"t_slash\n");
        //ungetc(current_char, file);
        tokenValue = T_SLASH;
        return E_OK; // /
      }
      break;

    case S_BL_COMM: // /*
      // kdyz je komentar, scanner ho ignoruje -> rozpoznat a jit na start
      while (1) {                  // nekonecny cyklus nacitani dalsich znaku
        current_char = getc(file); // nacitani znaku
        if(current_char=='\n')
         radek++;
        if (current_char == '*') { /* pokud se dalsi nacteny znak bude rovnat
                                      hvezdicce,
                                      otestujeme, zda se dalsi znak rovna /.
                                      Pokud ano, ukoncime cyklus*/
          current_char = getc(file);
          if(current_char=='\n')
           radek++;
          if (current_char == '/') {
            break;
          }
        } else if (current_char == EOF) {
          // vypsat chybovou hlasku na stderr
          return E_LEX;
        }
      }
      state = S_START;
      break;

    case S_LN_COMM: // // - radkovy komentar
      do {
        //  fprintf(stderr,"KOMENT\n");
        if (current_char == '\n' || current_char == EOF) {
          //  fprintf(stderr,"KOMENT1\n");
          break;
        }
        // fprintf(stderr,"KOMENT2\n");
        current_char = getc(file);
        if(current_char=='\n')
         radek++;
      } while (current_char != EOF && current_char != '\n');
      // fprintf(stderr,"KOMENT3\n");
      state = S_START;
      break;

    /*...............IDENTIFIKATOR x KLICOVE SLOVO...............*/
    case S_C_IDENT:
    //fprintf(stderr, "S_C_IDENT %c\n", current_char);

      if ((isalnum(current_char)) != 0 || current_char == '$' ||
          current_char == '_') {
        // test, zda je to alfanumericky znak, dolar nebo podtrzitko - pak je to
        // identifikator
        appendChar(helpstring, current_char);
        //fprintf(stderr, "S_C_IDENT %s\n", helpstring->data);
        state = S_C_IDENT;
      } else if (current_char == ';' || current_char == '.' ||
                 current_char == '/' || current_char == '+' ||
                 current_char == '-' || (isspace(current_char) != 0) ||
                 current_char == '*' || current_char == '<' ||
                 current_char == '>' || current_char == ',' ||
                 current_char == '(' || current_char == ')' ||
                 current_char == '^' || current_char == '=' ||
                 current_char == '~' || current_char == '{' ||
                 current_char == '}' || current_char == '[' ||
                 current_char == ']' || current_char == EOF ||
                 current_char == '\\'|| current_char == '!' ||
                 current_char == '\'') { //
        // neni identifikator - testy na nepovolene znaky
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file); // vrati posledni znak zpet do souboru,
                                    // takze dalsi funkce jej precte znovu
        //fprintf(stderr, "S_C_IDENT else if %c\n", current_char);
        //fprintf(stderr, "S_C_IDENT: %s\n", helpstring->data);
        for (int a = 0; a < KEYWORDS; a++) {
          // fprintf(stderr,"Comparing with %s\n", klicova_slova[a]);

          if ((strcmp(helpstring->data, klicova_slova[a])) ==
              0) /****JAK POZNAT TO, CO MAM NACTENO***/
          {      // je to klicove slovo
            // destroyString(string);
            // tokenValue =
            //     T_KEY + a + 1; // vrati presny odkaz na dane klicove slovo
            // return E_OK;
            //fprintf(stderr, "je to klicove slovo\n");
            return E_LEX;
          }
        }
        //fprintf(stderr, "S_C_IDENT key: %s\n", helpstring->data);
        string = concatenate(string, helpstring);
        //fprintf(stderr, "S_C_IDENT key: %s\n", string->data);
        //fprintf(stderr, "S_C_IDENT len: %d\n", string->len);
        tokenValue = T_C_IDENT;     // byl to identifikator
        return E_OK;
      } else {
        return E_LEX; // chyba
      }
      break;

    case S_IDENT: // identifikator nebo klicove slovo -> zacina znakem,
                  // podtrzitkem nebo dolarem
      if ((isalnum(current_char)) != 0 || current_char == '$' ||
          current_char == '_') {
        // test, zda je to alfanumericky znak, dolar nebo podtrzitko - pak je to
        // identifikator
        appendChar(string, current_char);
        state = S_IDENT;
        // fprintf(stderr,"scanner, current state of indetificator = %s\n",
        // string->data);
      }  else if (current_char == '.') {
              appendChar(string, current_char);
              current_char = getc(file);
              //fprintf(stderr, "S_IDENT_DOT %c\n", current_char);
              if (isWhiteSpace(current_char))
              return E_LEX;
              else /*appendChar(string, current_char);*/
        ungetc(current_char, file);
        state = S_C_IDENT;
        helpstring = newString(); //pomocny string pro druhou cast identifikatoru

      } else if (current_char == ';' || current_char == '.' ||
                 current_char == '/' || current_char == '+' ||
                 current_char == '-' || (isspace(current_char) != 0) ||
                 current_char == '*' || current_char == '<' ||
                 current_char == '>' || current_char == ',' ||
                 current_char == '(' || current_char == ')' ||
                 current_char == '^' || current_char == '=' ||
                 current_char == '~' || current_char == '{' ||
                 current_char == '}' || current_char == '[' ||
                 current_char == ']' || current_char == EOF ||
                 current_char == '\\'|| current_char == '!' ||
                 current_char == '\'' ) { //
        // neni identifikator - testy na nepovolene znaky
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file); // vrati posledni znak zpet do souboru,
                                    // takze dalsi funkce jej precte znovu
        // fprintf(stderr,"DEBUG %s\n", string->data);
        for (int a = 0; a < KEYWORDS; a++) {
          // fprintf(stderr,"Comparing with %s\n", klicova_slova[a]);

          if ((strcmp(string->data, klicova_slova[a])) ==
              0) /****JAK POZNAT TO, CO MAM NACTENO***/
          {      // je to klicove slovo
            // destroyString(string);
            tokenValue =
                T_KEY + a + 1; // vrati presny odkaz na dane klicove slovo
            return E_OK;
          }
        }

        tokenValue = T_IDENT; // byl to identifikator
        return E_OK;

      } else {
        return E_LEX; // chyba
      }
      break;
    /*........................STRING......................*/
    case S_STRING: // "
      if (current_char == '\n') {
        return E_LEX;
      } else if (current_char == '"') {
        tokenValue = T_STRING_L; // "string"
        return E_OK;
      } else if (current_char == '\\') { /*   "..\    */
        state = S_ESCAPE;
      } else {
        appendChar(string, current_char);

        state = S_STRING; // dokud bude nacitat string, tak cykli
      }

      // TODO return E_LEX; ???
      break;

    /*........................ESCAPE......................*/

    case S_ESCAPE:
      // fprintf(stderr,"%d current_char0\n", current_char);
      if (current_char == 'n') {
        appendChar(string, '\n');
        state = S_STRING;
      } else if (current_char == 't') {
        appendChar(string, '\t');
        state = S_STRING;
      } else if (current_char == '\\') {
        appendChar(string, '\\');
        state = S_STRING;
      } else if (current_char == '\"') {
        appendChar(string, '\"');
        state = S_STRING;
      } else if (isdigit(current_char) != 0) { // je to cislo, mensi
        //  fprintf(stderr,"%s\n", current_char);
        // fprintf(stderr,"%d current_char\n", current_char);
        if ((current_char < '4') && (current_char >= '0')) {
          // fprintf(stderr,"prosel1\n");
          // appendChar(string, num);
          // fprintf(stderr,"%d\n", num);
          // fprintf(stderr,"%d\n", current_char);
          int esc = (current_char - ASCII) * 8 * 8; // 8^2 (nejlevejsi cislo)
          // fprintf(stderr,"%d\n", esc);
          current_char = getc(file); // dalsi cislo v escape sekvenci
          if(current_char=='\n')
           radek++;

          if ((current_char < '8') && (current_char >= '0')) { // \0-30-7
            // fprintf(stderr,"prosel2\n");
            esc = esc + (current_char - ASCII) * 8; // 8^1 (prostredni cislo)
            // fprintf(stderr,"%d\n", esc);
            current_char = getc(file); // dalsi cislo v escape sekvenci
            if(current_char=='\n')
             radek++;

            if ((current_char < '8') && (current_char >= '0')) { // \0-30-70-7
              // fprintf(stderr,"prosel3\n");
              esc = esc + (current_char - ASCII); // 8^0 (nejpravejsi cislo)
              if(esc == 0 || esc >= 255){ // 001-377
                return E_LEX;
              }
              // fprintf(stderr,"%d\n", esc);
              appendChar(string,
                         (char)esc); // pridani cele escape sekvence do stringu
              state = S_STRING;
            }
          }
        }
      }

      else {
        // fprintf(stderr,"escape \n");
        return E_LEX;
      }
      break;
    /*.........................CISLO......................*/
    case S_NUM: // cislo
    //fprintf(stderr, "S_NUM %c\n", current_char);
      if (isdigit(current_char) != 0) {
//fprintf(stderr, "je cislo\n");
        appendChar(string, current_char);
        // ERROR
        state = S_NUM;
      } else if (current_char == '.') { // desetinna tecka
         // jinak error
        state = S_NUM_DOT;
      } else if (current_char == 'e' || current_char == 'E') { // exponent
        appendChar(string, current_char);
        //fprintf(stderr, "E/e\n");
        // jinak error
        state = S_NUM_EX;
      }

      else {
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);

        tokenValue = T_NUMBER_I;
        return E_OK;
      }
      break;

    case S_NUM_DOT:                     // 0-9.
    //fprintf(stderr, "S_NUM_DOT %c\n", current_char);
      if (isdigit(current_char) != 0) { // test na cislo
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_DOT_NUM;
      } else {
        //fprintf(stderr,"skoncilo cislo: %s\n", string->data);
        return E_LEX;
      }
      break;

    case S_NUM_DOT_NUM:                     // 0-9.0-9
    //fprintf(stderr, "S_NUM_DOT_NUM %c\n", current_char);
      if (isdigit(current_char) != 0) { // test na cislo
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_DOT_NUM;
      } else if ((current_char == 'e') || (current_char == 'E')) {
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_EX;
      } else if ( (current_char == '.') || (current_char == ',') ||
                 (current_char == '!') || (current_char == '/')
                    || (current_char == 9) ||
                (current_char == 0) ) {
        // fprintf(stderr,"CHYBA S_NUM_DOT\n");
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        return E_LEX;
      } else {
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        tokenValue = T_NUMBER_D;
        return E_OK;
      }
      break;
    /*......................................................*/

    case S_NUM_EX: // 0-9eE || 0-9.0-9Ee
    //fprintf(stderr, "S_NUM_EX %c\n", current_char);
      if (current_char == '+' || current_char == '-' ||
          (isdigit(current_char)) != 0) {
        // dalsi znak je +,- nebo dalsi cislo
        appendChar(string, current_char);
        //current_char = getc(file);
        state = S_NUM_EX_NUM;
        //ungetc(current_char, file);
        //fprintf(stderr, "S_NUM_EX getc %c\n", current_char);
      }
      else {
        return E_LEX;
      }
      break;

    case S_NUM_EX_NUM: // 0-9eE+-0-9 || 0-9.0-9Ee+-0-9
    //fprintf(stderr, "S_NUM_EX_NUM %c\n", current_char);
      if (isdigit(current_char) != 0) {
        appendChar(string, current_char);
        state = S_NUM_EX_NUM; // dokud budou nacitana cisla - cyklus

      }
      else if (current_char == ';'  || current_char == '/' ||
               current_char == '*' || current_char == '(' ||
               current_char == ')') {
        if(current_char=='\n')
           radek--;
           //fprintf(stderr, "jsem tady\n");
        ungetc(current_char, file);
        tokenValue = T_NUMBER_D;
        return E_OK;
        // destroyString(string);
      } else {
         //fprintf(stderr,"CHYBA\n");
        if(current_char=='\n')
          radek--;
        ungetc(current_char, file);
        return E_LEX;
      }

      break;

    } // konec switch

  } // konec while

  // return ret;
}
