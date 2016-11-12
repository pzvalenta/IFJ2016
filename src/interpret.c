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
#include "ilist.h"
#include "str.h"

int interpret(SymTableNode *root, tInstrList *instrList);

int interpret(SymTableNode *root, tInstrList *instrList){
  list_first(instrList);    //aktivita na prvni polozku seznamu
  tInstr *I;      // instrukce I
  I = GetData(instrList);
  //cyklus dokud typ instrukce neni ukoncovaci instrukce programu
  while(I->Inst_typ != I_STOP){

    switch(I->Inst_type){
      case I_LABEL:
        //navesti
        //zadna akce
        break;

      case I_IFGOTO:
        //podmineny skok
        //TODO
        break;

      case I_INC:
        break;

      case I_GOTO:
        list_goto(instrList, I->addr3);
        break;
      case I_ADD:


    }
  }



}
