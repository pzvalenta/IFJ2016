#ifndef HEADER_PARSER
#define HEADER_PARSER

#include "ial.h"
#include "scanner.h"
#include "str.h"
#include "main.h"
#include "debug.h"
#include "symtable.h"


struct tListItem;


extern struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu

extern struct classNode *CTRoot; //koren globalni tabulky trid
extern struct varNode *GVRoot; //koren globalni tabulky promennych
extern struct funNode *FTRoot; // koren glob tabulky funkci


extern struct classNode *CurrentClass;
extern struct funNode *CurrentMethod;


int parse(struct tListItem *head);


#endif
