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


void list_init (tInstrList *L){
  /*
  * Inicializace seznamu pred prvnim pouzitim
  */
  L->first  = NULL;
  L->last   = NULL;
  L->act    = NULL;
}

void list_free (tInstrList *L){
  /*
  * Dealokace seznamu instrukci
  */
  tListItem *ptr;
  while (L->first != NULL)
  {
    ptr = L->first;
    L->first = L->first->nextItem;
    // uvolnime celou polozku
    free(ptr);
  }

}

int list_insert_last (tInstrList *L, int i_type, void* adresa1, void* adresa2, void* adresa3){
  /*
  * vkladani nove instrukce na konec listu
  */
  tInstr new_instruction;
  new_instruction.Inst_type = i_type;
  new_instruction.addr1 = adresa1;
  new_instruction.addr2 = adresa2;
  new_instruction.addr3 = adresa3;

  tList_item *new;
  new = malloc (sizeof(tList_item));
  if(new == NULL){
    return E_INTERNAL; //chyba alokace
  }
  new->instruct = new_instruction;      //ulozeni novych dat
  new->next_item = NULL;  //next_item == new, tudiz ukazatel nikam ukazovat nemuze
  if (L->first == NULL){  //pokud je list prazdny == prvni vlozeni
    L->first = new;       //prvni prvek je new
  }
  else{                   //pokud nebyl prazdny
    L->last->next_item = new;
  }

  L->last = new;          //ulozeni noveho prvku na konec
  return E_OK;
}

void list_first (tInstrList *L){
  /*
  * nastaveni aktivity na prvni polozku seznamu
  */
  L->act = L->first;
}

void list_next (tInstrList *L){
  /*
  * z nasledujici instrukce se stane aktivni instrukce
  */
  if (L->act != NULL){
    L->act = L->act->next_item;
  }
}

void list_goto (tInstrList *L, void *goto_instr){
  /*
  * aktivni instrukce se nastavi podle ukazatele *goto_instr
  * POZOR, z hlediska predmetu IAL tato funkce narusuje strukturu
  * abstraktniho datoveho typu
  */
  L->act = (tList_item*) goto_instr;
}

void *GetLastPointer (tInstrList *L){
  /*
  * vraci ukazatel na posledni instrukci
  * POZOR, z hlediska predmetu IAL tato funkce narusuje strukturu
  * abstraktniho datoveho typu
  */
  return (void*) L->last;
}

tInstr *GetData (tList_item *L){
  /*
  * vraci aktivni instrukci, pokud zadna neni, vraci chybu
  */
  if (L->act == NULL){
    printf("Chyba, zadna instrukce neni aktivni\n");
    return NULL;
  }
  else {
    return &(L->act->instruct);
  }
}
