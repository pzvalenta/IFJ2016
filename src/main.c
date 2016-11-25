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

#include "main.h"

int main(int argc, char **argv){
  int result = E_OK;

  if (argc == 2){
    //TODO zpracovat vstupy + nastavit input streamu pro scanner
    printf("opening: %s\n", argv[1]);
    FILE *source = fopen(argv[1], "r");
    //errorcheck TODO
    set_file(source);
    printf("opened: %p\n", source);
  }
  else ///REMOVE!!! TODO
  {
    FILE *source = fopen("/home/petr/Code/IFJ2016/testing/input/example1.java", "r");
    set_file(source);
  }


  // zabalit do inicializace
  struct tListItem *tokenListHead = malloc(sizeof(struct tListItem));
  if(tokenListHead == NULL) return E_INTERNAL;
  else {
    tokenListHead->next = NULL;
    tokenListHead->id = START;
  }


  fprintf(stderr, "############## Start Scanneru ##############\n");

  set_token_list(tokenListHead);
  result = loadTokens();
  if(result != E_OK){
    //TODO dealokace
    return result;
  }
  fprintf(stderr, "############# Vysledek Scanneru ############\n");
  eprint(result);


  // //DEBUG TOKEN LIST PRINT
  // printf("pointer na head %p\n", tokenListHead);
  //
  // while(tokenListHead != NULL){
  //   dprint(tokenListHead);
  //   tokenListHead = tokenListHead->next;
  // }



//testing //






  //deklarace tabulek
  TableNode *CTRoot = NULL;
  TableNode *GTRoot = NULL;

  //TODO inicializace ilistu

  fprintf(stderr, "############### Start Parseru ##############\n");

  //volani parseru
  result = parse(CTRoot, GTRoot, tokenListHead);
  fprintf(stderr, "############# Vysledek Parseru #############\n");
  eprint(result);
  //TODO errorcheck

  //TODO druhy pruchod?


  //volani interpretu   TODO odkaz na main v ilistu, jak?
  //result = interpret(ilist);

  //TODO errorcheck


  return result;
}
