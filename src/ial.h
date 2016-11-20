#ifndef HEADER_IAL
#define HEADER_IAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "token.h"

enum {
	DEFINED = 1,
	INITIALIZED
}

//TODO zmenit state a global na flags

typedef struct tableNode TableNode;

struct TableNode{
	String *name; // identifikator / klic
	char id; //typ (funkce/char/string ...)
	char state; // DEFINED / INITIALIZED

	TableNode *global; // pokud je global != NULL, je v nem odkaz do global table, na prislusnou polozku

	TableNode *localTable; // pokud je to funkce nebo class, je tu odkaz na lokalni tabulku
	String *data; //data

	//pokud je definovana lokalni promenna i pres to, ze uz je definovana globalni, vytvori se novy string

	TableNode *left;
  TableNode *right;
}

TableNode *newTN(String *str);
TableNode *insertTN(TableNode *root, TableNode *node);
char deleteTN(TableNode *root, TableNode *node);
char replaceTN(TableNode *out, TableNode *in);
TableNode *findMaxTN(TableNode *root);
TableNode *searchT(TableNode *root, char *exp);
char destroyTN (TableNode *node);
char destroyT (TableNode *root);

void printInorder(TableNode *node);

#endif
