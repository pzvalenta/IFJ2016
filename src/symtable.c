#include "symtable.h"


// extern struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu

//
// extern struct TableNode *CurrentClass;
// extern struct TableNode *CurrentMethod;
//
// extern struct varNode *GVRoot; //koren globalni tabulky promennych
// extern struct funNode *GFRoot; //koren globalni tabulky funkci
// extern struct classNode *GCRoot; //koren globalni tabulky trid

int newFunction();  // vytvori novou polozku v globalni tabulce funkci, name = token->data
int newClass();     //                                          trid
int newStaticVar(); //                                          promennych + v lokalni tabulce
int newVar();       //                         lokalni tabulce, podle CurrentMethod/CurrentClass

int completize(String *s); // predela string->name z neuplneho identifikatoru na uplny, pomoci CurrentClass


int newFunction(){
  struct funNode *tmp = newFN(token);
  if (tmp == NULL) return E_INTERNAL;

  if(completize(tmp->name) != E_OK){
    destroyFN(tmp);
    return E_INTERNAL;
  }

  if (searchFT(FTRoot, tmp->name->data) != NULL) {
    destroyFN(tmp);
    return E_SEM;  // TODO uz byla deklarovana, je v tabulce
  }

  GVRoot = insertFN(tmp);
  return E_OK;
}

int newClass(){
  struct classNode *tmp = newCN(token);
  if (tmp == NULL) return E_INTERNAL;

  if (searchCT(CTRoot, tmp->name->data) != NULL) {
    destroyCN(tmp);
    return E_SEM;  // TODO uz byla deklarovana, je v tabulce
  }

  GCRoot = insertCN(tmp);
  return E_OK;
}

int newStaticVar(){
  struct varNode *tmp = newVN(token);
  if (tmp == NULL) return E_INTERNAL;

  if (CurrentMethod != NULL){
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus o deklaraci static promenne ve funkci\n");
    return E_SYN;
  }

  if (CurrentClass == NULL){
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus o deklaraci static promenne mimo tridu\n");
    return E_SYN;
  }

  if (searchVT(CurrentClass->lVarTable, tmp->name->data) != NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus o deklaraci static var, ktera uz byla deklarovana jako lokalni\n");
    return E_SEM;  // uz byla deklarovana, je v lokalni tabulce tridy
  }

  if (searchVT(GVRoot, tmp->name->data) != NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, redeklarace globalni promenne\n");
    return E_SEM;  // uz byla deklarovana, je v globalni tabulce promennych
  }

  //vytvoreni polozky v lokalni tabulce
  CurrentClass->lVarTable = insertVN(tmp);

  //vytvoreni polozky v glob. tabulce
  struct varNode *tmp = newVN(token);
  if (tmp == NULL) return E_INTERNAL;
  if(completize(tmp->name) != E_OK){
    destroyVN(tmp);
    return E_INTERNAL;
  }

  GVRoot = insertVN(tmp);

  return E_OK;
}

int newVar(){
  struct varNode *tmp = newVN(token);
  if (tmp == NULL) return E_INTERNAL;

  if (CurrentClass == NULL){
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus promenne mimo tridu\n");
    return E_SYN;
  }

  if (CurrentMethod == NULL){
    if (searchVT(CurrentClass->lVarTable, tmp->name->data) != NULL) {
      destroyVN(tmp);
      fprintf(stderr, "ERROR, redeklarace lokalni promenne\n");
      return E_SEM;  // uz byla deklarovana, je v lokalni tabulce tridy
    }
    else{
      CurrentClass->lVarTable = insertVN(tmp);
    }
  }
  else {
    if (searchVT(CurrentMethod->lVarTable, tmp->name->data) != NULL) {
      destroyVN(tmp);
      fprintf(stderr, "ERROR, redeklarace lokalni promenne\n");
      return E_SEM;  // uz byla deklarovana, je v lokalni tabulce funkce
    }
    else{
      CurrentMethod->lVarTable = insertVN(tmp);
    }
  }

  return E_OK;
}


int completize(String *s){   // predela string s na uplny identifikator
  String *tmp = newString();
  for(int i = 0; i < CurrentClass->name->data->len){
    appendChar(tmp, CurrentClass->data->data[i]);
  }

  appendChar(tmp, '.');

  for(int i = 0; i < s->data->len){
    appendChar(tmp, s->data->data[i]);
  }

  destroyString(s);
  s = tmp;
}









//////////////////////////////////////STARE FUNKCE

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
