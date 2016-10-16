#include <stdio.h>
#include <stdlib.h>

#include "ial.h"
#include "str.h"
#include "token.h"

// Symbol Table implementation

struct _SymTableNode{
	char *name; // identifikator a zaroven klic
	char id; // na to nase id nam staci jeden byte

	union{ // union zabira tolik mista v pameti jako jeho nejvetsi prvek, smi se pouzit jenom jeden
		long i; // int
		double f; // float
		char * s; // string
	} data;

	SymTableNode *left;
	SymTableNode *right;
};

SymTableNode *newSymTableNode(Token *token, char *str){
	SymTableNode *ret = malloc(sizeof(SymTableNode));
	if (ret == NULL){
		fprintf(stderr, "Not enought memory, can't alloc.\n");
		return NULL;
	}

	ret->name = copyString(str);
	ret->id = token->id;
	ret->data = NULL;

	ret->left = NULL;
	ret->right = NULL;
}

// returns new root
SymTableNode *insertSymTableNode(SymTableNode *root, SymTableNode *node){
	if (root == NULL){
		root = node;
		return root;
	}

	if (strcmp(node->name, root->name) > 0)
		root->right = insert(root->right, node)
	else if (strcmp(node->name, root->name) < 0)
		root->left = insert(root->left, node)
	else
		fprintf("Error, equal node keys.\n",stderr)

	return root;
}

void printInorder(SymTableNode *node){
	if (node == NULL) return;
	printInorder(node->left);
	printf("%s\n", node->name);
	printInorder(node->right;)
}

SymTableNode *searchSymTable(SymTableNode *root, char *exp){
	int a = strcmp(exp, root->name);
	if (a == 0) return root;
	else if (a > 0) return searchSymTable(root->right, exp);
	else return searchSymTable(root->left, exp);

	return NULL; // not found
}

// Pomocny zasobnik

struct _SymStackItem{
	SymTableNode *table;
	SymStackItem *next;
};

SymStackItem *newSymStackItem(){
	SymStackItem *ret = malloc(sizeof(SymStackItem));
	if (ret == NULL){
		fprintf("Not enought memory, can't alloc.\n");
		return NULL;
	}

	ret->table = NULL;
	ret->next = NULL;
}

SymStackItem *pushSymStackItem(SymStackItem *item, SymSackItem *stack){
	item->next = stack;
	return item;
}

SymStackItem *popSymStackItem(SymSackItem *stack){
	SymStackItem *ret = stack;
	stack = ret->next;
	ret->next = NULL;
	return ret;
}
