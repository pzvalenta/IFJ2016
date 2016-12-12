#ifndef HEADER_IAL
#define HEADER_IAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"


////////////////////////VARIABLES
//struktura pro lokalni tabulky / globalni tabulku promennych
struct String;

struct varNode{
	struct String *name;
	int type;   // TODO pridat type "ukazatel", data.s pak bude ukazatelem do prislusne globalni tabulky
	int offset;
	int declared;
	int initialized;

	struct varNode *global;

	struct varNode *left;
	struct varNode *right;
};

struct tListItem;

//funkce pro praci s lok / glob tabulkami promennych
struct varNode *newVN(struct tListItem *token);
struct varNode *insertVN(struct varNode *root, struct varNode *node);
void deleteVN(struct varNode *root, struct varNode *node);
void replaceVN(struct varNode *out, struct varNode *in);
struct varNode *findMaxVN(struct varNode *root);
struct varNode *searchVT(struct varNode *root, char *exp);
void destroyVN (struct varNode *node);
void destroyVT (struct varNode *root);
void printSpecialV(struct varNode *node);



////////////////////////FUNCTIONS
//struktura pro glob. tabulku funkci
struct funNode{
	struct String *name;

	struct String *types; // void func(int a, double b)   =  "vid"
	int varc; //pocet lok. promennych
	struct varNode *lVarTable;
	// TODO ukazatel na prvni instrukci
	// TODO deklarace, definice?

	struct funNode *left;
	struct funNode *right;
};

//funkce pro praci s glob. tabulkou funkci
struct funNode *newFN(struct tListItem *token);
struct funNode *insertFN(struct funNode *root, struct funNode *node);
void deleteFN(struct funNode *root, struct funNode *node);
void replaceFN(struct funNode *out, struct funNode *in);
struct funNode *findMaxFN(struct funNode *root);
struct funNode *searchFT(struct funNode *root, char *expression);
void destroyFN (struct funNode *node);
void destroyFT (struct funNode *root);
void printInOrderF(struct funNode *node);
void printSpecialF(struct funNode *node);


////////////////////////CLASSES
//struktura pro  glob. tabulku trid
struct classNode{
	struct String *name;

	struct varNode *lVarTable;
	int varc;

	struct classNode *left;
	struct classNode *right;
};

//funkce pro praci s glob. tabulkou trid
struct classNode *newCN(struct tListItem *token);
struct classNode *insertCN(struct classNode *root, struct classNode *node);
void deleteCN(struct classNode *root, struct classNode *node);
void replaceCN(struct classNode *out, struct classNode *in);
struct classNode *findMaxCN(struct classNode *root);
struct classNode *searchCT(struct classNode *root, char *exp);
void destroyCN (struct classNode *node);
void destroyCT (struct classNode *root);
void printInOrderC(struct classNode *node);
void printSpecialC(struct classNode *node);

//kmp a heap sort
void kmpTabulka(char *text, int* tabulka);
int kmp(char *text, char *prohledano);
	
void sift(char *str, int levy, int pravy);
char *sort(char *trash);



//void printInorder(TableNode *node);

#endif
