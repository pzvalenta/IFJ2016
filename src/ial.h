#ifndef HEADER_IAL
#define HEADER_IAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "token.h"

typedef struct SymTableNode SymTableNode;

struct SymTableNode{
	String *name; // identifikator a zaroven klic
	char id; // na to nase id nam staci jeden byte

	union{ // union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; // int
		double f; // float
		String * s; // string
	} data;

	SymTableNode *left;
	SymTableNode *right;
};

typedef struct SymStackItem SymStackItem;

struct SymStackItem{
	SymTableNode *table;
	SymStackItem *next;
};




//////////////EXTERNAL FUNCTIONS//////////////
SymTableNode *newSymTableNode(Token *token, String *str);

SymTableNode *insertSymTableNode(SymTableNode *root, SymTableNode *node);

void deleteSymTableNode(SymTableNode *root, SymTableNode *node);

void replaceSymTableNode(SymTableNode *out, SymTableNode *in);

void printInorder(SymTableNode *node);

SymTableNode *findMaxNode(SymTableNode *root);

SymTableNode *searchSymTable(SymTableNode *root, char *exp);

SymStackItem *newSymStackItem();

SymStackItem *pushSymStackItem(SymStackItem *item, SymStackItem *stack);

SymStackItem *popSymStackItem(SymStackItem *stack);

void destroySymStack(SymStackItem *stack);

void destroySymStackItem(SymStackItem *item);

//////////////INTERNAL FUNCTIONS//////////////
void destroySymTableNode(SymTableNode *node);

void destroySymTable(SymTableNode *root);


#endif
