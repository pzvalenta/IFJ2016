#include "symtable.h"

// extern struct tListItem *token;    // globalni promena, ukazatel na
// momentalni token v tokenlistu

//
// extern struct TableNode *CurrentClass;
// extern struct TableNode *CurrentMethod;
//
// extern struct varNode *GVRoot; //koren globalni tabulky promennych
// extern struct funNode *FTRoot; //koren globalni tabulky funkci
// extern struct classNode *CTRoot; //koren globalni tabulky trid

String *completize(String *s); // predela string->name z neuplneho
                               // identifikatoru na uplny, pomoci CurrentClass

int getOffset(); // najde offset z tabulky symbolu podle tokenu
struct varNode *findVar();
int isCompleteIdent(String *str);



void setVarType(int type){
  CurrentVar->type = type;
}

void addMparam(int type) {
  char c;
  switch (type) {
  case T_INT:
    c = 'i';
    break;
  case T_DOUBLE:
    c = 'd';
    break;
  case T_STRING_L:
    c = 's';
    break;
  case T_VOID:
    c = 'v';
    break;
  }
  appendChar(CurrentMethod->types, c);
}

struct funNode *findFunction() {
  String *tmp = completize(token->data);
  struct funNode *result = searchFT(FTRoot, tmp->data);
  destroyString(tmp);
  return result;
}

struct classNode *findClass() {
  return searchCT(CTRoot, token->data->data);
}

int isFunction() {
  int result;
  printf("token->data %p \n", token->data);

  String *tmp = completize(token->data);
  printf("token->data %p   completized %p\n", token->data, tmp);
  if (findFunction(FTRoot, tmp->data) == NULL)
    result = 0;
  else
    result = 1;
  printf("\n PREDESTROY\n");
  destroyString(tmp);
  printf("\n POSTDESTROY\n");

  return result;
}

int isCompleteIdent(String *str) {
  for (int i = 0; str->data[i] != '\0'; i++) {
    if (str->data[i] == '.')
      return 1;
  }
  return 0;
}

int getOffset() {
  struct varNode *tmp = findVar();
  if (tmp == NULL)
    return -1;
  else
    return tmp->offset;
}

int getType() {
  struct varNode *tmp = findVar();
  if (tmp == NULL)
    return -1;
  else
    return tmp->type;
}


struct varNode *findVar() {
  if (isCompleteIdent(token->data))
    return searchVT(GVRoot, token->data->data);

  struct varNode *tmp;

  if (CurrentMethod != NULL){
    tmp = searchVT(CurrentMethod->lVarTable, token->data->data);
    if (tmp->global != NULL) {// toto by nikdy nemelo nastat
      fprintf(stderr,"THIS SHOULD NEVER HAPPEN! method variable has global pointer\n");
      return tmp->global;
    }
    else return tmp;
  }


  if (CurrentClass != NULL) {
    struct varNode *tmp = searchVT(CurrentClass->lVarTable, token->data->data);
    if (tmp->global != NULL) return tmp->global;
    else return tmp;
  }

  return NULL;
}

int newFunction() {
  if (CurrentClass == NULL)
    return E_SYN;

  struct funNode *tmp = newFN(token);
  if (tmp == NULL)
    return E_INTERNAL;

  if (!isCompleteIdent(tmp->name)) {
    printf("not complete, %p\n", tmp->name);
    tmp->name = completize(tmp->name);
    if (tmp->name == NULL) {
      destroyFN(tmp);
      return E_INTERNAL;
    }
    printf("complete, %p\n", tmp->name);
  }

  printf("ABOUT TO SEARCH FTRoot with %s\n", tmp->name->data);
  if (searchFT(FTRoot, tmp->name->data) != NULL) {
    destroyFN(tmp);
    return E_SEM; // TODO uz byla deklarovana, je v tabulce
  }

  if (searchVT(GVRoot, tmp->name->data) != NULL) {
    destroyFN(tmp);
    fprintf(
        stderr,
        "ERROR, deklarace funkce se jmenem totoznym jako globalni promenna \n");
    return E_SEM;
  }

  FTRoot = insertFN(FTRoot, tmp);
  CurrentMethod = tmp;

  return E_OK;
}

int setCurrentMethod(){
  int result = E_OK;
  String *s = completize(token->data);
  struct funNode *tmp = searchFT(FTRoot, s->data);
  if (tmp == NULL) result = E_INTERNAL;
  CurrentMethod = tmp;
  CurrentVar = NULL;
  destroyString(s);
  return result;
}

int setCurrentClass(){
  struct classNode *tmp = searchCT(CTRoot, token->data->data);
  if (tmp == NULL) return E_INTERNAL;
  CurrentClass = tmp;
  CurrentMethod = NULL;
  CurrentVar = NULL;
  return E_OK;
}

int newClass() {
  struct classNode *tmp = newCN(token);
  if (tmp == NULL)
    return E_INTERNAL;

  if (searchCT(CTRoot, tmp->name->data) != NULL) {
    destroyCN(tmp);
    return E_SEM; // TODO uz byla deklarovana, je v tabulce
  }

  CTRoot = insertCN(CTRoot, tmp);
  CurrentClass = tmp;
  return E_OK;
}

int newStaticVar() {
  struct varNode *tmp = newVN(token);
  if (tmp == NULL)
    return E_INTERNAL;

  if (CurrentMethod != NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus o deklaraci static promenne ve funkci\n");
    return E_SYN;
  }

  if (CurrentClass == NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus o deklaraci static promenne mimo tridu\n");
    return E_SYN;
  }

  if (searchVT(CurrentClass->lVarTable, tmp->name->data) != NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus o deklaraci static var, ktera uz byla "
                    "deklarovana jako lokalni\n");
    return E_SEM; // uz byla deklarovana, je v lokalni tabulce tridy
  }

  if (searchVT(GVRoot, tmp->name->data) != NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, redeklarace globalni promenne\n");
    return E_SEM; // uz byla deklarovana, je v globalni tabulce promennych
  }

  if (searchFT(FTRoot, tmp->name->data) != NULL) {
    destroyVN(tmp);
    fprintf(
        stderr,
        "ERROR, deklarace globalni promenne se jmenem totoznym jako funkce\n");
    return E_SEM;
  }
  // vytvoreni polozky v lokalni tabulce
  CurrentClass->lVarTable = insertVN(CurrentClass->lVarTable, tmp);

  // vytvoreni polozky v glob. tabulce
  struct varNode *tmp2 = newVN(token);
  if (tmp2 == NULL)
    return E_INTERNAL;

  tmp2->name = completize(tmp2->name);
  if (tmp2->name == NULL) {
    destroyVN(tmp2);
    return E_INTERNAL;
  }

  tmp->global = tmp2;

  CurrentVar = tmp2;
  GVRoot = insertVN(GVRoot, tmp2);

  return E_OK;
}

int newVar() {
  struct varNode *tmp = newVN(token);
  if (tmp == NULL)
    return E_INTERNAL;

  if (CurrentClass == NULL) {
    destroyVN(tmp);
    fprintf(stderr, "ERROR, pokus promenne mimo tridu\n");
    return E_SYN;
  }

  if (CurrentMethod == NULL) {
    if (searchVT(CurrentClass->lVarTable, tmp->name->data) != NULL) {
      destroyVN(tmp);
      fprintf(stderr, "ERROR, redeklarace lokalni promenne\n");
      return E_SEM; // uz byla deklarovana, je v lokalni tabulce tridy
    } else {
      CurrentClass->lVarTable = insertVN(CurrentClass->lVarTable, tmp);
    }
  } else {
    if (searchVT(CurrentMethod->lVarTable, tmp->name->data) != NULL) {
      destroyVN(tmp);
      fprintf(stderr, "ERROR, redeklarace lokalni promenne\n");
      return E_SEM; // uz byla deklarovana, je v lokalni tabulce funkce
    } else {
      CurrentMethod->lVarTable = insertVN(CurrentMethod->lVarTable, tmp);
    }
  }

  CurrentVar = tmp;
  return E_OK;
}

String *completize(String *s) { // predela string s na uplny identifikator
  if (isCompleteIdent(s))
    return copyString(s);
  String *tmp = newString();
  for (int i = 0; i < CurrentClass->name->len; i++) {
    appendChar(tmp, CurrentClass->name->data[i]);
  }

  appendChar(tmp, '.');

  for (int i = 0; i < s->len; i++) {
    appendChar(tmp, s->data[i]);
  }

  return tmp;
}

//////////////////////////////////////STARE FUNKCE

// String *createCompleteIdent(){
//   String *tmp = newString();
//   for(int i = 0; i < CurrentClass->name->data->len){
//     appendChar(tmp, CurrentClass->data->data[i]);
//   }
//
//   appendChar(tmp, '.');
//
//   for(int i = 0; i < token->data->len){
//     appendChar(tmp, token->data->data[i]);
//   }
//
//   destroyString(token->data);
//   token->data = tmp;
// }
//
// int addToTable(tListItem *token){
//   createCompleteIdent(token);
//
//   switch (token->id) {
//     case T_CLASS:
//     break;
//
//     case T_IDENT:
//     break;
//   }
//   if (searchT(GTRoot, token->data->data) == NULL){
//           /// vytvorit novou node v globalni tabulce trid
//           /// error check
//           CurrentMethod = newTN(token);
//           if (CurrentMethod == NULL) return E_INTERNAL;
//
//           // vlozi novou node do tabulky, jmeno, id
//           GTRoot = insertTN(GTRoot, CurrentMethod);
//
//           //TODO vytvorit lokalni tabulku
//   }
// }
//
// TableNode *findInTable(tListItem *token){
//   switch (token->id){
//     case T_CLASS:
//       return searchT(CTRoot, token->data->data);
//     case T_IDENT:
//       if (isCompleteIdent(token->data)){
//         return searchT(GTRoot->localTable, token->data->data);
//       }
//       if (CurrentMethod == NULL){
//         if (CTRoot->localTable == NULL) return NULL;
//         return searchT(CTRoot->localTable, token->data->data);
//       }
//       else
//       {
//         if (CurrentClass->localTable == NULL) return NULL;
//         return searchT(CurrentClass->localTable, token->data->data);
//       }
//     break;
//
//     default: return NULL;
//   }
// }
//

// int getType(tListItem *token){
//
//   return T_INT;
//
// }
//
// int get
//
//
//
//
// struct {
//   int type;
//   union{
//     String *s;
//     int i;
//     double d;
//   } data;
// }
//
//
//                 operace op1 op2   vysledek
// insertInstruction(MUL, , , );
//
//
// insertInstruction(assign, , , );
