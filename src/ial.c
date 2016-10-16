#include "ial.h"
// Symbol Table implementation

struct _SymTableNode{
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

SymTableNode *newSymTableNode(Token *token, String *str){
	SymTableNode *ret = malloc(sizeof(SymTableNode));
	if (ret == NULL){
		fprintf(stderr, "Not enought memory, can't alloc.\n");
		return NULL;
	}

	ret->name = copyString(str);
	ret->id = token->id;
	ret->data.s = NULL;

	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

// returns new root
SymTableNode *insertSymTableNode(SymTableNode *root, SymTableNode *node){
	if (root == NULL){
		root = node;
		return root;
	}

	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		root->right = insertSymTableNode(root->right, node);
	else if (cmp < 0)
		root->left = insertSymTableNode(root->left, node);
	else
		fprintf(stderr,"Error, equal node keys.\n");

	return root;
}

void printInorder(SymTableNode *node){
	if (node == NULL) return;
	printInorder(node->left);
	printf("%s\n", node->name->data);
	printInorder(node->right);
}

SymTableNode *searchSymTable(SymTableNode *root, char *exp){
	int a = strcmp(exp, root->name->data);
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
		fprintf(stderr,"Not enought memory, can't alloc.\n");
		return NULL;
	}

	ret->table = NULL;
	ret->next = NULL;
	return ret;
}

SymStackItem *pushSymStackItem(SymStackItem *item, SymStackItem *stack){
	item->next = stack;
	return item;
}

SymStackItem *popSymStackItem(SymStackItem *stack){
	SymStackItem *ret = stack;
	stack = ret->next;
	ret->next = NULL;
	return ret;
}
