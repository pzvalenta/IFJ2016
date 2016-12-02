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
#include "interpret.h"
#include "main.h"

//TODO dodelat push a pop funkce v ramci jednotlivych instrukci ?

int interpret(tInstrList *instrList){
  list_first(instrList);    //aktivita na prvni polozku seznamu
  tInstr *I;      // instrukce I
  int type = 0; //typ data
  void* value1 = NULL; //hodnota dat
  void* value2 = NULL;
  void* value3 = NULL;

//TODO pamatovat si kde jsem byla predtim (ukazatel)

stack = Init_stack(); //Inicializace zasobniku
if(stack == NULL){
  return E_INTERNAL; //error - chyba pri inicializaci zasobniku
}

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
        if(address1->data->data != 0){
          list_goto(instrList, address2->data); //??? bude ukazatel address2->data
        }
        break;

      case I_GOTO:
        list_goto(instrList, I->addr3); //???
        break;
/*................BINARNI OPERACE.................*/
      case I_ADD:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;

          //destroyStringData();
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          address3->data->data = value1 + value2; //scitani ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->data->type != T_NUMBER_D){ //address1->type ?
            //pretypovani
            double val1 = (double *)value1;
            address3->data->data = val1 + value2;
          }
          if(address2->data->type != T_NUMBER_D){
            //pretypovani
            double val = (double *)value2;
            address3->data->data = value1 + val2;
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            address3->data->data = value1 + value2; //nasobeni ulozeno do address3
          }
        }
        else if(address1->id == T_STRING_L || address2->id == T_STRING_L){ //alespon jeden operator je string
          address3->id = T_STRING_L;
          address3->data->data = concatenate(address1->data->data, address2->data->data);
        //chyba Inicializace??
      break;

      case I_SUB:
      //TODO test na incializaci
        if(address1->id == T_NUMBER_I && address2->id == T_NUMBER_I){ //oba operatory jsou int
          address3->id = T_NUMBER_I;

          //destroyStringData();
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          address3->data->data = value1 - value2; //odcitani ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->id != T_NUMBER_D){
            //pretypovani
            double val1 = (double *)value1;
            address3->data->data = val1 - value2;
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
            double val = (double *)value2;
            address3->data->data = value1 - val2;
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            address3->data->data = value1 - value2; //nasobeni ulozeno do address3
          }
          //uvolneni stringu (destroyStringData)
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
          //destroyStringData();
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          address3->data->data = value1 * value2; //nasobeni ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->id != T_NUMBER_D){
            //pretypovani
            double val1 = (double *)value1;
            address3->data->data = val1 * value2;
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
            double val = (double *)value2;
            address3->data->data = value1 * val2;
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            address3->data->data = value1 * value2; //nasobeni ulozeno do address3
          }
          //uvolneni stringu (destroyStringData)

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
          //destroyStringData();
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          address3->data->data = value1 / value2; //deleni ulozeno do address3
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_D;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->id != T_NUMBER_D){
            //pretypovani
            double val1 = (double *)value1;
            address3->data->data = val1 / value2;
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
            double val = (double *)value2;
            address3->data->data = value1 / val2;
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            address3->data->data = value1 / value2; //nasobeni ulozeno do address3
          }
          //uvolneni stringu (destroyStringData)
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
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if((value1) == (value2)){
            address3->data->data = 1;  // !0 TRUE
          }
          else{
            address3->data->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->id != T_NUMBER_D){
            //pretypovani
            double val1 = (double *)value1;
            if((val1) == (value2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
            double val2 = (double *)value2;
            if((value1) == (val2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            if((value1) == (value2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
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
        value1 = GetDataofString(address1->data);
        value2 = GetDataofString(address2->data);
        if((value1) != (value2)){
          address3->data->data = 1;  // !0 TRUE
        }
        else{
          address3->data->data = 0;  // 0 FALSE
        }
      }
      else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
        address3->id = T_NUMBER_I;
        value1 = GetDataofString(address1->data);
        value2 = GetDataofString(address2->data);
        if(address1->id != T_NUMBER_D){
          //pretypovani
          double val1 = (double *)value1;
          if((val1) != (value2)){
            address3->data->data = 1;  // !0 TRUE
          }
          else{
            address3->data->data = 0;  // 0 FALSE
          }
        }
        if(address2->id != T_NUMBER_D){
          //pretypovani
          double val2 = (double *)value2;
          if((value1) != (val2)){
            address3->data->data = 1;  // !0 TRUE
          }
          else{
            address3->data->data = 0;  // 0 FALSE
          }
        }
        if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
          if((value1) != (value2)){
            address3->data->data = 1;  // !0 TRUE
          }
          else{
            address3->data->data = 0;  // 0 FALSE
          }
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
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if((value1) >= (value2)){
            address3->data->data = 1;  // !0 TRUE
          }
          else{
            address3->data->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->id != T_NUMBER_D){
            //pretypovani
            double val1 = (double *)value1;
            if((val1) >= (value2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
            double val2 = (double *)value2;
            if((value1) >= (val2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            if((value1) >= (value2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
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
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if((value1) <= (value2)){
            address3->data->data = 1;  // !0 TRUE
          }
          else{
            address3->data->data = 0;  // 0 FALSE
          }
        }
        else if(address1->id == T_NUMBER_D || address2->id == T_NUMBER_D){ //alespon jeden operator je double
          address3->id = T_NUMBER_I;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          if(address1->id != T_NUMBER_D){
            //pretypovani
            double val1 = (double *)value1;
            if((val1) <= (value2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }
          if(address2->id != T_NUMBER_D){
            //pretypovani
            double val2 = (double *)value2;
            if((value1) <= (val2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }
          if(address1->id == T_NUMBER_D && address2->id == T_NUMBER_D){
            if((value1) <= (value2)){
              address3->data->data = 1;  // !0 TRUE
            }
            else{
              address3->data->data = 0;  // 0 FALSE
            }
          }

        }
        else{
          return E_TYP; //pokud neprojde pres podminky -> chyba kompatibility
        }
        //chyba Inicializace??
        break;

      case I_PUSH:
        if (address1->id == T_NUMBER_I){
          value1 = GetDataofString(address1->data);
          type = T_NUMBER_I;
        }
        else if(address1->id == T_NUMBER_D){
          value1 = GetDataofString(address1->data);
          type = T_NUMBER_D;
        }
        else if(address1->id == T_STRING_L){
          value1 = GetDataofString(address1->data);
          type = T_STRING_L;
        }
        else{
          return E_TYP;
        }
        Push_stack(stack, value, type);
        break;

      case I_POP:
      if (address1->id == T_NUMBER_I){
        value1 = GetDataofString(address1->data);
        type = T_NUMBER_I;
      }
      else if(address1->id == T_NUMBER_D){
        value1 = GetDataofString(address1->data);
        type = T_NUMBER_D;
      }
      else if(address1->id == T_STRING_L){
        value1 = GetDataofString(address1->data);
        type = T_STRING_L;
      }
      else{
        return E_TYP;
      }
      Pop_stack(stack, value, type); //??? ukazatele
      break;

      case I_MOV:
        if(address1->id == T_NUMBER_I){
          value1 = GetDataofString(address1->data);
          address3->id = T_NUMBER_I;
          address3->data->data = value1;
        }
        else if(address1->id == T_NUMBER_D){
          value1 = GetDataofString(address1->data);
          address3->id = T_NUMBER_D;
          address3->data->data = value1;
        }
        else if(address1->id == T_STRING_L){
          value1 = GetDataofString(address1->data);
          address3->id = T_STRING_L;
          address3->data->data = value1;
        }
        else{
          return E_TYP; //ERROR
        }
        break;

      case I_INPUT: //jen treti adresa

      case I_CALL:
      case I_RETURN:
//TODO print, read,
      case I_CMP_STR:
        if (address1->id == T_STRING_L && address2->id == T_STRING_L){
          address3->id = T_STRING_L;
          value1 = GetDataofString(address1->data);
          value2 = GetDataofString(address2->data);
          int ret_c = NULL; //sem se ulozi navratova hodnota strcmp
          ret_c = strcmp(value1, value2);
          if (ret_c == 0){
            address3->data->data = 0;  // 0 TRUE stringy se rovnaji
          }
          else if (ret_c > 0){
            address3->data->data = 1; // prvni string je vetsi nez druhy string
          }
          else{
            address3->data->data = -1; // jine, resp. druhy je vetsi nez prvni
          }
        }
        else{
          return E_TYP;
        }
        break;

    } //konec switch

    if (instrList->act->instruct.Inst_type == I_GOTO || instrList->act->instruct.Inst_type == I_IFGOTO){

    }
    else list_next(*instrList); //nacteni dalsi instrukce pokud to neni skok
  } // konec while

  Free_stack(*stack); // uvolneni stacku
  return E_OK; //uspesne projiti
} //konec funkce

/*...............FUNKCE ZASOBNIKU..............*/

//Inicializace zasobniku
Stack Init_stack(){
  Stack *stack = (Stack *) malloc(sizeof(Stack));
  if(stack == NULL){
    return NULL;
  }
  stack->data = (*St_data) malloc(BASE_STACK_SIZE*sizeof(St_data));
  if (stack->data == NULL){
    Free_stack(*stack);
    return NULL; //TODO handle error
  }
  stack->size = BASE_STACK_SIZE;
  stack->next = NULL;
  return stack;
}

//push zasobniku, parametry:
//nazev zasobniku
//hodnota vkladanych dat
//typ vkladanych dat
void Push_stack(Stack stack, void *value, int type){
  if(stack->size <= stack->topof){
    ResizeStack(stack);
  }
  stack->data[stack->topof].val = value;
  stack->data[stack->topof].type = type;
  stack->topof++; // navyseni vrcholu zasobniku
}

void Pop_stack(Stack stack, void ** value, int * type){
  stack->topof--; // snizeni pocitadla vrcholu zasobniku
  *value = stack->data[stack->topof].val;
  *type  = stack->data[stack->topof].type;
}

//uvolneni zasobniku
void Free_stack(Stack * stack){
  free(stack->data);
  free(stack);
}

//zvetsi velikost zasobniku
void ResizeStack(Stack *stack){
  stack->data = realloc(stack->data, 5* sizeof(St_data));
  if(stack->data == NULL){
    free(stack);
    //TODO ERROR
  }
  stack->size = 5*(stack->size);
}
