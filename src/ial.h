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
};
//TODO zmenit state a global na flags

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

struct TableNode{
	String *name; // identifikator / klic
	char id; //typ (funkce/char/string ...)
	char state; // DEFINED / INITIALIZED

	struct TableNode *global; // pokud je global != NULL, je v nem odkaz do global table, na prislusnou polozku

	struct TableNode *localTable; // pokud je to funkce nebo class, je tu odkaz na lokalni tabulku
	String *data; //data

	//pokud je definovana lokalni promenna i pres to, ze uz je definovana globalni, vytvori se novy string

	struct TableNode *left;
  struct TableNode *right;
};
typedef struct TableNode TableNode;



TableNode *newTN(String *str, char token_id);
TableNode *insertTN(TableNode *root, TableNode *node);
void deleteTN(TableNode *root, TableNode *node);
void replaceTN(TableNode *out, TableNode *in);
TableNode *findMaxTN(TableNode *root);
TableNode *searchT(TableNode *root, char *exp);
void destroyTN (TableNode *node);
void destroyT (TableNode *root);

void printInorder(TableNode *node);

#endif
