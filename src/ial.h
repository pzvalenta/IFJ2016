#ifndef HEADER_IAL
#define HEADER_IAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "token.h"

typedef struct _SymTableNode SymTableNode;

typedef struct _SymStackItem SymStackItem;

SymTableNode *newSymTableNode(Token *token, String *str);

SymTableNode *insertSymTableNode(SymTableNode *root, SymTableNode *node);

void printInorder(SymTableNode *node);

SymTableNode *searchSymTable(SymTableNode *root, char *exp);

SymStackItem *newSymStackItem();

SymStackItem *pushSymStackItem(SymStackItem *item, SymStackItem *stack);

SymStackItem *popSymStackItem(SymStackItem *stack);


#endif
