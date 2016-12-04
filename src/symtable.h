#ifndef HEADER_SYMTABLE
#define HEADER_SYMTABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "token.h"


extern struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu

extern struct classNode *CTRoot; //koren globalni tabulky trid
extern struct varNode *GVRoot; //koren globalni tabulky promennych
extern struct funNode *FTRoot; // koren glob tabulky funkci


extern struct classNode *CurrentClass;
extern struct funNode *CurrentMethod;
extern struct varNode *CurrentVar;


struct TableNode;

struct tListItem;


void setVarType(int type);
int newFunction();  // vytvori novou polozku v globalni tabulce funkci, name = token->data
int newClass();     //                                          trid
int newStaticVar(); //                                          promennych + v lokalni tabulce
int newVar();       //                         lokalni tabulce, podle CurrentMethod/CurrentClass
void addMparam();

int setCurrentMethod();
int setCurrentClass();

int isFunction();
int getType(); //TODO predelat na getType(tListItem *token)

#endif
