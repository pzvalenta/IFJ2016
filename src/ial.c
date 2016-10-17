#include "ial.h"
// Symbol Table implementation



SymTableNode *newSymTableNode(Token *token, String *str){
	SymTableNode *ret = malloc(sizeof(SymTableNode));
	if (ret == NULL){
		fprintf(stderr, "Not enought memory, can't alloc.\n");
		return NULL;
	}

	ret->name = str;
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
	else { //already in table
		printf("%s already in table, root->name->data = %s, root pointer %p, node pointer %p\n", node->name->data, root->name->data, root, node);
		destroySymTableNode(node);
	}
	return root;
}


void deleteSymTableNode(SymTableNode *root, SymTableNode *node){
	if (root == NULL || node == NULL) return NULL;
	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		deleteSymTableNode(root->right, node);
	else if (cmp < 0)
		deleteSymTableNode(root->left, node);
	else { //root == node
		if (node->right == NULL && node->left == NULL){
			destroySymTableNode(node);
			root = NULL;
		}
		else if (node->right != NULL && node->left == NULL){
			replaceSymTableNode(node, node->right);
		}
		else if (node->right == NULL && node->left != NULL){
			replaceSymTableNode(node, node->left);
		}
		else if (node->right != NULL && node->left != NULL){
			SymTableNode *tmp = findMaxNode(node->left);
			tmp->right = node->right;
			replaceSymTableNode(node, tmp);
			deleteSymTableNode(root, tmp);
		}
	}
	// if (node == NULL) return NULL;
	//
	// if (node->right == NULL && node->left == NULL){
	// 	destroySymTableNode(node);
	// 	node = NULL;
	// }
	// else if (node->right != NULL && node->left == NULL){
	// 	replaceSymTableNode(node, node->right);
	// }
	// else if (node->right == NULL && node->left != NULL){
	// 	replaceSymTableNode(node, node->left);
	// }
	// else if (node->right != NULL && node->left != NULL){
	// 	SymTableNode *tmp = findMaxNode(node->left);
	// 	tmp->right = node->right;
	// 	replaceSymTableNode(node, tmp);
	// 	deleteSymTableNode(tmp);
	// }
	// return;
}

void destroySymTableNode(SymTableNode *node){
	if (node->id == T_STRING)
		destroyString(node->data.s);
	destroyString(node->name);
	free(node);
	node = NULL;
}

void destroySymTable(SymTableNode *root){
	if (root->left != NULL)
		destroySymTable(root->left);
	if (root->right != NULL)
		destroySymTable(root->right);
	destroySymTableNode(root);
}

void replaceSymTableNode(SymTableNode *out, SymTableNode *in){
	if (out->id == T_STRING)
		destroyString(out->data.s);
	destroyString(out->name);

	out->data = in->data;
	out->name = in->name;
	out->id = in->id;
	out->left = in->left;
	out->right = in->right;
	free(in);
	in = NULL;
}

void printInorder(SymTableNode *node){
	if (node == NULL) return;
	printInorder(node->left);
	printf("%s\n", node->name->data);
	printInorder(node->right);
}

SymTableNode *findMaxNode(SymTableNode *root){
	if (root == NULL) return NULL;

	if (root->right != NULL) return findMaxNode(root->right);
	else return root;
}

SymTableNode *searchSymTable(SymTableNode *root, char *exp){
	if (root == NULL) return NULL;

	int a = strcmp(exp, root->name->data);
	if (a == 0) return root;
	else if (a > 0) return searchSymTable(root->right, exp);
	else return searchSymTable(root->left, exp);

	return NULL; // not found
}

SymTableNode *findParent(SymTableNode *root, SymTableNode *node){
	if (root == NULL || node == NULL) return NULL;

	if (root == node) return NULL; //no parent, it is root
	else if (root->left == node) return root;
	else if (root->right == node) return root;

	int a = strcmp(node->name->data, root->name->data);
	if (a > 0) return findParent(root->right, node);
	else return findParent(root->left, node);
}

// Pomocny zasobnik
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
	if (stack == NULL) return NULL;
	SymStackItem *ret = stack;
	stack = ret->next;
	ret->next = NULL;
	return ret;
}

void destroySymStack(SymStackItem *stack){
	if (stack->next != NULL)
		destroySymStack(stack->next);
	else
		destroySymStackItem(stack);
}

void destroySymStackItem(SymStackItem *item){
	destroySymTable(item->table);
	free(item);
	item = NULL;
}
