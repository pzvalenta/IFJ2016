#ifndef HEADER_IAL
#define HEADER_IAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "token.h"


////////////////////////VARIABLES
//struktura pro lokalni tabulky / globalni tabulku promennych
struct varNode{
	String *name;
	int type;   // TODO pridat type "ukazatel", data.s pak bude ukazatelem do prislusne globalni tabulky
	int offset;
	int declared;
	int initialized;
	
	struct varNode *global;

	struct varNode *left;
	struct varNode *right;
}

//funkce pro praci s lok / glob tabulkami promennych
struct varNode *newVN(struct tListItem *token);
struct varNode *insertVN(struct varNode *root, struct varNode *node);
void deleteVN(struct varNode *root, struct varNode *node);
void replaceVN(struct varNode *out, struct varNode *in);
struct varNode *findMaxVN(struct varNode *root);
struct varNode *searchVT(struct varNode *root, char *exp);
void destroyVN (struct varNode *node);
void destroyVT (struct varNode *root);



////////////////////////FUNCTIONS
//struktura pro glob. tabulku funkci
struct funNode{
	String *name;

	String types; // void func(int a, double b)   =  "vid"
	int varc; //pocet lok. promennych
	varNode *lVarTable;
	// TODO ukazatel na prvni instrukci
	// TODO deklarace, definice?

	struct funNode *left;
	struct funNode *right;
}

//funkce pro praci s glob. tabulkou funkci
struct funNode *newFN(struct tListItem *token);
struct funNode *insertFN(struct funNode *root, struct funNode *node);
void deleteFN(struct funNode *root, struct funNode *node);
void replaceFN(struct funNode *out, struct funNode *in);
struct funNode *findMaxFN(struct funNode *root);
struct funNode *searchFT(struct funNode *root, char *exp);
void destroyFN (struct funNode *node);
void destroyFT (struct funNode *root);


////////////////////////CLASSES
//struktura pro  glob. tabulku trid
struct classNode{
	String *name;

	varNode *lVarTable;

	struct classNode *left;
	struct classNode *right;
}

//funkce pro praci s glob. tabulkou trid
struct classNode *newCN(struct tListItem *token);
struct classNode *insertCN(struct classNode *root, struct classNode *node);
void deleteCN(struct classNode *root, struct classNode *node);
void replaceCN(struct classNode *out, struct classNode *in);
struct classNode *findMaxCN(struct classNode *root);
struct classNode *searchCT(struct classNode *root, char *exp);
void destroyCN (struct classNode *node);
void destroyCT (struct classNode *root);





//void printInorder(TableNode *node);

#endif
