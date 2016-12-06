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
struct tListItem *head = NULL;
struct tListItem *tail = NULL;
int tokenValue = E_LEX;

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
  S_EOL,
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
    //fprintf(stderr, "token debug %d\n", result);
    if (result != E_OK) {
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
    // fprintf(stderr,"current_char: %c\n", current_char);

    switch (state) {
    case S_START:
      if (isspace(current_char) != 0) {
        // testuje, zda je aktualni znak bily znak
        // nic se ale nestane, protoze je ignorujeme
        state = S_START;
      } else if ((isalpha(current_char)) != 0 || current_char == '$' ||
                 current_char == '_') {
        // zacina znakem, dolarem nebo podtrzitkem
        // string = eraseString(string);
        // TODO if NULL, handle error
        appendChar(string, current_char);
        state = S_IDENT;
      } else if (isdigit(current_char) != 0) { // pokud to je cislo
        // string = eraseString(string);
        // TODO if NULL, handle error
        state = S_NUM;
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
      } else if (current_char == '.') {
        tokenValue = T_DOT;
        return E_OK;
      } else if (current_char == EOF) {
        tokenValue = T_END;
        return E_OK;
      } else if (current_char == '\n') {
        state = S_EOL;
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
        state = S_SLASH;

      } else if (current_char == '"') {
        // string = eraseString(string);
        // TODO if NULL, handle error
        state = S_STRING;
      } else
        return E_LEX;
      break;

    /*..............................................*/

    case S_GREATER:
      if (current_char == '=') {
        tokenValue = T_GEQUAL; // >=
        return E_OK;
      } else if (current_char == '\n') {
        tokenValue = T_GREAT; // >
        return E_OK;
      }
      break;

    case S_LESS:
      if (current_char == '=') {
        tokenValue = T_LEQUAL; // <=
        return E_OK;
      } else if (current_char == '\n') {
        tokenValue = T_LESS; // <
        return E_OK;
      }
      break;

    case S_EXCLAIM:
      if (current_char == '=') {
        tokenValue = T_EXCLAIM; // !=
        return E_OK;
      } else if (current_char == '\n') {
        tokenValue = E_LEX; // pokud za vykricnikem nic neni
        return E_OK;
      }
      break;

    case S_EQUAL:
      if (current_char == '=') {
        tokenValue = T_EQUAL; // ==
        return E_OK;
      } else if (isWhiteSpace(current_char)) {
        tokenValue = T_ADD; // =
        return E_OK;
      }
      break;

    case S_SLASH: // /
      if (current_char == '/') {
        state = S_LN_COMM;              // prejdi na stav radkoveho komentare
      } else if (current_char == '*') { // /* - zacatek blokoveho komentare
        state = S_BL_COMM;
      } else if (current_char == '\n') { // pouze lomitko
        // fprintf(stderr,"slash\n");
        tokenValue = T_SLASH;
        return E_OK; // /
      }
      break;

    case S_BL_COMM: // /*
      // kdyz je komentar, scanner ho ignoruje -> rozpoznat a jit na start
      while (1) {                  // nekonecny cyklus nacitani dalsich znaku
        current_char = getc(file); // nacitani znaku
        if (current_char == '*') { /* pokud se dalsi nacteny znak bude rovnat
                                      hvezdicce,
                                      otestujeme, zda se dalsi znak rovna /.
                                      Pokud ano, ukoncime cyklus*/
          current_char = getc(file);
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
      } while (current_char != EOF && current_char != '\n');
      // fprintf(stderr,"KOMENT3\n");
      state = S_START;
      break;

    /*...............IDENTIFIKATOR x KLICOVE SLOVO...............*/
    case S_C_IDENT:
      if ((isalnum(current_char)) != 0 || current_char == '$' ||
          current_char == '_') {
        // test, zda je to alfanumericky znak, dolar nebo podtrzitko - pak je to
        // identifikator
        appendChar(string, current_char);
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
                 current_char == ']') { //
        // neni identifikator - testy na nepovolene znaky
        ungetc(current_char, file); // vrati posledni znak zpet do souboru,
                                    // takze dalsi funkce jej precte znovu
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
      } else if (current_char == '.') {
        appendChar(string, current_char);
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
                 current_char == ']') { //
        // neni identifikator - testy na nepovolene znaky
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

          if ((current_char < '8') && (current_char >= '0')) { // \0-30-7
            // fprintf(stderr,"prosel2\n");
            esc = esc + (current_char - ASCII) * 8; // 8^1 (prostredni cislo)
            // fprintf(stderr,"%d\n", esc);
            current_char = getc(file); // dalsi cislo v escape sekvenci

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
      if (isdigit(current_char) != 0) {
        appendChar(string, current_char);
        // ERROR
        state = S_NUM;
      } else if (current_char == '.') { // desetinna tecka
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_DOT;
      } else if (current_char == 'e' || current_char == 'E') { // exponent
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_EX;
      }

      else {
        ungetc(current_char, file);
        tokenValue = T_NUMBER_I;
        return E_OK;
      }
      break;

    // case S_NUM_DOT:                     // 0-9.
    //   if (isdigit(current_char) != 0) { // test na cislo
    //     appendChar(string, current_char);
    //     // jinak error
    //     state = S_NUM_DOT_NUM;
    //   } else {
    //     return E_LEX;
    //   }
    //   break;

    case S_NUM_DOT:                     // 0-9.0-9
      if (isdigit(current_char) != 0) { // test na cislo
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_DOT;
      } else if ((current_char == 'e') || (current_char == 'E')) {
        appendChar(string, current_char);
        // jinak error
        state = S_NUM_EX;
      } else if ((current_char == '.') || (current_char == ',') ||
                 (current_char == '!') || (current_char == '/')) {
        // fprintf(stderr,"CHYBA S_NUM_DOT\n");
        ungetc(current_char, file);
        return E_LEX;
      } else {
        ungetc(current_char, file);
        tokenValue = T_NUMBER_D;
        return E_OK;
      }
      break;
    /*......................................................*/

    case S_NUM_EX: // 0-9eE || 0-9.0-9Ee
      if (current_char == '+' || current_char == '-' ||
          (isdigit(current_char)) != 0) {
        // dalsi znak je +,- nebo dalsi cislo
        appendChar(string, current_char);

        state = S_NUM_EX_NUM;
      } else {
        return E_LEX;
      }
      break;

    case S_NUM_EX_NUM: // 0-9eE+-0-9 || 0-9.0-9Ee+-0-9
      if (isdigit(current_char) != 0) {
        appendChar(string, current_char);
        state = S_NUM_EX_NUM; // dokud budou nacitana cisla - cyklus

      }

      else if (current_char == ';' || current_char == '+' ||
               current_char == '-' || current_char == '/' ||
               current_char == '*' || current_char == '(' ||
               current_char == ')') {
        ungetc(current_char, file);
        tokenValue = T_NUMBER_D;
        return E_OK;
        // destroyString(string);
      } else {
        // fprintf(stderr,"CHYBA\n");
        ungetc(current_char, file);
        return E_LEX;
      }

      break;

    } // konec switch

  } // konec while

  // return ret;
}