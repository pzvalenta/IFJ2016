#ifndef HEADER_SYMTABLE
#define HEADER_SYMTABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "token.h"


extern struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu
extern struct TableNode *CTRoot; //koren globalni tabulky trid
extern struct TableNode *GTRoot; //koren globalni tabulky funkci a promennych

extern struct TableNode *CurrentClass;
extern struct TableNode *CurrentMethod;


// //typedef struct tableNode TableNode;
//
// struct TableNode{
// 	String *name; // identifikator / klic
// 	char id; //typ (funkce/char/string ...)
// 	char state; // DEFINED / INITIALIZED
//
// 	TableNode *global; // pokud je global != NULL, je v nem odkaz do global table, na prislusnou polozku
//
// 	TableNode *localTable; // pokud je to funkce nebo class, je tu odkaz na lokalni tabulku
// 	String *data; //data
//
// 	//pokud je definovana lokalni promenna i pres to, ze uz je definovana globalni, vytvori se novy string
//
// 	TableNode *left;
//   TableNode *right;
// };

struct TableNode;

struct tListItem;


int addToTable(tListItem token);

TableNode *newTN(struct tListItem *token);
TableNode *insertTN(TableNode *root, TableNode *node);
void deleteTN(TableNode *root, TableNode *node);
void replaceTN(TableNode *out, TableNode *in);
TableNode *findMaxTN(TableNode *root);
TableNode *searchT(TableNode *root, char *exp);
void destroyTN (TableNode *node);
void destroyT (TableNode *root);

void printInorder(TableNode *node);

#endif
