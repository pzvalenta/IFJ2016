#ifndef HEADER_PARSER
#define HEADER_PARSER

#include "ial.h"
#include "scanner.h"
#include "str.h"
#include "main.h"
#include "debug.h"

struct TableNode;
struct tListItem;


extern struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu
extern struct TableNode *CTRoot; //koren globalni tabulky trid
extern struct TableNode *GTRoot; //koren globalni tabulky funkci a promennych

extern struct TableNode *CurrentClass;
extern struct TableNode *CurrentMethod;


int parse(struct TableNode *CTRoot, struct TableNode *GTRoot, struct tListItem *head);


#endif
