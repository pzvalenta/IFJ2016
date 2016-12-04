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

int main(int argc, char **argv) {
  int result = E_OK;

  if (argc == 2) {
    // TODO zpracovat vstupy + nastavit input streamu pro scanner
    printf("opening: %s\n", argv[1]);
    FILE *source = fopen(argv[1], "r");
    // errorcheck TODO
    set_file(source);
    printf("opened: %p\n", source);
  } else /// REMOVE!!! TODO
  {
    FILE *source =
        fopen("/home/petr/Code/IFJ2016/testing/input/example3.java", "r");
    set_file(source);
  }

  // zabalit do inicializace
  struct tListItem *tokenListHead = malloc(sizeof(struct tListItem));
  if (tokenListHead == NULL)
    return E_INTERNAL;
  else {
    tokenListHead->next = NULL;
    tokenListHead->id = START;
  }

  fprintf(stderr, "############## Start Scanneru ##############\n");

  set_token_list(tokenListHead);
  result = loadTokens();
  if (result != E_OK) {
    // TODO dealokace
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

  // testing //

  // TODO inicializace ilistu

  fprintf(stderr, "############### Start Parseru 1st RUN ##############\n");

  // volani parseru
  printf("token list head = %s\n", tokenListHead->data->data);
  result = parse(tokenListHead);
  fprintf(stderr, "############# Vysledek Parseru 1st RUN #############\n");
  eprint(result);
  // TODO errorcheck

  // TODO druhy pruchod?
  fprintf(stderr, "############### Start Parseru 2nd RUN ##############\n");
  printf("token list head = %s\n", tokenListHead->data->data);

  SECOND_RUN = 1;
  // volani parseru
  result = parse(tokenListHead);
  fprintf(stderr, "############# Vysledek Parseru 2nd RUN #############\n");
  eprint(result);

  // volani interpretu   TODO odkaz na main v ilistu, jak?
  // result = interpret(ilist);

  // TODO errorcheck

  return result;
}
