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

int main(void){
  char result = E_OK;

  if (argv)
  //TODO zpracovat vstupy + nastavit input streamu pro scanner
  FILE *source = fopen(argv[1]);
  set_file(source);

  //deklarace tabulek
  TableNode *CTRoot = NULL;
  TableNode *GTRoot = NULL;

  //TODO inicializace ilistu

  //volani parseru
  result = parse(CTRoot, GTRoot)
  //TODO errorcheck

  //TODO druhy pruchod?


  //volani interpretu   TODO odkaz na main v ilistu, jak?
  result = interpret(ilist);

  //TODO errorcheck


  return result;
}
