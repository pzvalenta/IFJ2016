#include "symtable.h"


// extern struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu
// extern struct TableNode *CTRoot; //koren globalni tabulky trid
// extern struct TableNode *GTRoot; //koren globalni tabulky funkci a promennych
//
// extern struct TableNode *CurrentClass;
// extern struct TableNode *CurrentMethod;


String *createCompleteIdent(){
  String *tmp = newString();
  for(int i = 0; i < CurrentClass->name->data->len){
    appendChar(tmp, CurrentClass->data->data[i]);
  }

  appendChar(tmp, '.');

  for(int i = 0; i < token->data->len){
    appendChar(tmp, token->data->data[i]);
  }

  destroyString(token->data);
  token->data = tmp;
}

int addToTable(tListItem *token){
  createCompleteIdent(token);

  switch (token->id) {
    case T_CLASS:
    break;

    case T_IDENT:
    break;
  }
  if (searchT(GTRoot, token->data->data) == NULL){
          /// vytvorit novou node v globalni tabulce trid
          /// error check
          CurrentMethod = newTN(token);
          if (CurrentMethod == NULL) return E_INTERNAL;

          // vlozi novou node do tabulky, jmeno, id
          GTRoot = insertTN(GTRoot, CurrentMethod);

          //TODO vytvorit lokalni tabulku
  }
}

TableNode *findInTable(tListItem *token){
  switch (token->id){
    case T_CLASS:
      return searchT(CTRoot, token->data->data);
    case T_IDENT:
      if (isCompleteIdent()){
        return searchT(GTRoot->localTable, token->data->data);
      }
      if (CurrentMethod == NULL){
        if (CTRoot->localTable == NULL) return NULL;
        return searchT(CTRoot->localTable, token->data->data);
      }
      else
      {
        if (CurrentClass->localTable == NULL) return NULL;
        return searchT(CurrentClass->localTable, token->data->data);
      }
    break;

    default: return NULL;
  }
}


int getType(tListItem *token){

  return T_INT;

}

int get




struct {
  int type;
  union{
    String *s;
    int i;
    double d;
  } data;
}


                operace op1 op2   vysledek
insertInstruction(MUL, , , );


insertInstruction(assign, , , );
