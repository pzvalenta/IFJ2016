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
#include "ial.h"

int interpret(tInstrList *instrList);

int interpret(tInstrList *instrList){
  list_first(instrList);    //aktivita na prvni polozku seznamu
  tInstr *I;      // instrukce I


//TODO Inicializace zasobniku??

  while(instrList->act->instruct.Inst_type != I_STOP && instrList->act != NULL){
  //cyklus dokud typ instrukce neni ukoncovaci instrukce programu nebo
  //dokud aktivni instrukce neni NULL

    //I = GetData(instrList);
    TableNode *address1 = (TableNode*) instrList->act->instruct.addr1;
    TableNode *address2 = (TableNode*) instrList->act->instruct.addr2;
    TableNode *address3 = (TableNode*) instrList->act->instruct.addr3;

    switch(instrList->act->instruct.Inst_type){
      case I_LABEL:
        //navesti
        //zadna akce
        break;

      case I_IFGOTO:
        //podmineny skok
        //TODO if()
        list_goto(instrList, I->addr3);
        break;

      case I_GOTO:
        list_goto(instrList, I->addr3);
        break;
/*................BINARNI OPERACE.................*/
      case I_ADD:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) + (address2->data); //scitani ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) + (address2->data); //scitani ulozeno do address3
        }
        else if(address1->id == STRING || address2->id == STRING){ //alespon jeden operator je string
          address3->id = STRING;
          if(address1->id != STRING){
            //pretypovani
          }
          if(address2->id != STRING){
            //pretypovani
          }
          //uvolneni stringu (destroyStringData)
          address3->data = strcat(mem, address2->data); //konkatenace ulozena do address3
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

      case I_SUB:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) - (address2->data); //odcitani ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) - (address2->data); //odcitani ulozeno do address3
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;
      case I_MUL:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) * (address2->data); //nasobeni ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) * (address2->data); //nasobeni ulozeno do address3
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

      case I_DIV:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) / (address2->data); //deleni ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }
          //uvolneni stringu (destroyStringData)
          address3->data = (address1->data) / (address2->data); //deleni ulozeno do address3
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

/*................RELACNI OPERACE.................*/

      case I_EQUAL:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          if((address1->data) == (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }

          if((address1->data) == (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

      case I_NEQUAL:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          if((address1->data) != (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }

          if((address1->data) != (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

      case I_GREQ:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          if((address1->data) >= (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }

          if((address1->data) >= (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

      case I_LESEQ:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;
          //uvolneni stringu (destroyStringData)
          if((address1->data) <= (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          if(address1->id != T_NUMBER_D){
            //pretypovani
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
          }

          if((address1->data) <= (address2->data)){
            address3->data = 1;  // !0 TRUE
          }
          else{
            address3->data = 0;  // 0 FALSE
          }
        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;



    } //konec switch

    //TODO - podminka pro skok
    list_next(*instrList); //nacteni dalsi instrukce
  } // konec while

// TODO uvolnit zasobnik
  return E_OK; //uspesne projiti
} //konec funkce
