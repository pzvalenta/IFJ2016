#include "ial.h"
// Symbol Table implementation
//TODO ERRORS



// ////////////////////////VARIABLES
// //struktura pro lokalni tabulky / globalni tabulku promennych
// struct varNode{
// 	String *name;
// 	int type;   // TODO pridat type "ukazatel", data.s pak bude ukazatelem do prislusne globalni tabulky
// 	int offset;
//  int declared;
//  int initialized;
//
//  struct varNode *global;
// 	struct varNode *left;
// 	struct varNode *right;
// }
//
// //funkce pro praci s lok / glob tabulkami promennych
// struct varNode *newVN(struct tListItem *token);
// struct varNode *insertVN(struct varNode *root, struct varNode *node);
// void deleteVN(struct varNode *root, struct varNode *node);
// void replaceVN(struct varNode *out, struct varNode *in);
// struct varNode *findMaxVN(struct varNode *root);
// struct varNode *searchVT(struct varNode *root, char *exp);
// void destroyVN (struct varNode *node);
// void destroyVT (struct varNode *root);

struct varNode *newVN(struct tListItem *token){
	struct varNode *ret = malloc(sizeof(struct varNode));
	if (ret == NULL){
		fprintf(stderr, "Not enough memory, can't alloc.\n");
		return NULL;
	}

	ret->name = token->data;
	ret->type = -1;
	ret->offset = -1;
	ret->declared = 0;
	ret->initialized = 0;

	ret->global = NULL;
	ret->left = NULL;
	ret->right = NULL;

	return ret;
}

struct varNode *insertVN(struct varNode *root, struct varNode *node){
	if (root == NULL){
		root = node;
		return root;
	}

	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		root->right = insertVN(root->right, node);
	else if (cmp < 0)
		root->left = insertVN(root->left, node);
	else { //already in table
		destroyVN(node);
	}
	return root;
}

void deleteVN(struct varNode *root, struct varNode *node){
	if (root == NULL || node == NULL) return;
	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		deleteVN(root->right, node);
	else if (cmp < 0)
		deleteVN(root->left, node);
	else { //root == node
		if (node->right == NULL && node->left == NULL){
			destroyVN(node);
			root = NULL;
		}
		else if (node->right != NULL && node->left == NULL){
			replaceVN(node, node->right);
		}
		else if (node->right == NULL && node->left != NULL){
			replaceVN(node, node->left);
		}
		else if (node->right != NULL && node->left != NULL){
			struct varNode *tmp = findMaxVN(node->left);
			tmp->right = node->right;
			replaceVN(node, tmp);
			deleteVN(root, tmp);
		}
	}
}

void replaceVN(struct varNode *out, struct varNode *in){
	destroyString(out->name);

	out->name = in->name;
	out->type = in->type;
	out->offset = in->offset;
	out->declared = in->declared;
	out->initialized = in->initialized;

	out->global = in->global;
	out->left = in->left;
	out->right = in->right;

	free(in);
	in = NULL;
}


struct varNode *findMaxVN(struct varNode *root){
	if (root == NULL) return NULL;

	if (root->right != NULL) return findMaxVN(root->right);
	else return root;
}

struct varNode *searchVT(struct varNode *root, char *exp){
	if (root == NULL) return NULL;

	int a = strcmp(exp, root->name->data);
	if (a == 0) return root;
	else if (a > 0) return searchVT(root->right, exp);
	else return searchVT(root->left, exp);

	return NULL; // not found
}

void destroyVN (struct varNode *node){
	if (node == NULL) return;
	destroyString(node->name);
	free(node);
	node = NULL;
}

void destroyVT (struct varNode *root){
	if (root == NULL) return;
	if (root->left != NULL)
		destroyVT(root->left);
	if (root->right != NULL)
		destroyVT(root->right);
	destroyVN(root);
}
//////////////////////////



// ////////////////////////FUNCTIONS
// //struktura pro glob. tabulku funkci
// struct funNode{
// 	String *name;
//
// 	String types; // void func(int a, double b)   =  "vid"
// 	int varc; //pocet lok. promennych
// 	varNode *lVarTable;
// 	// TODO ukazatel na prvni instrukci
// 	// TODO deklarace, definice?
//
// 	struct funNode *left;
// 	struct funNode *right;
// }
//
// //funkce pro praci s glob. tabulkou funkci
// struct funNode *newFN(struct tListItem *token);
// struct funNode *insertFN(struct funNode *root, struct funNode *node);
// void deleteFN(struct funNode *root, struct funNode *node);
// void replaceFN(struct funNode *out, struct funNode *in);
// struct funNode *findMaxFN(struct funNode *root);
// struct funNode *searchFT(struct funNode *root, char *exp);
// void destroyFN (struct funNode *node);
// void destroyFT (struct funNode *root);


struct funNode *newFN(struct tListItem *token){
	struct funNode *ret = malloc(sizeof(struct funNode));
	if (ret == NULL){
		fprintf(stderr, "Not enough memory, can't alloc.\n");
		return NULL;
	}

	ret->name = token->data;

	ret->types = newString();
	if (ret->types == NULL) return NULL;

	ret->lVarTable = NULL;
	ret-> varc = 0;

	// TODO ukazatel na prvni instrukci
	// TODO deklarace, definice?	ret->offset = 0;


	ret->left = NULL;
	ret->right = NULL;

	return ret;
}

struct funNode *insertFN(struct funNode *root, struct funNode *node){
	if (root == NULL){
		root = node;
		return root;
	}

	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		root->right = insertFN(root->right, node);
	else if (cmp < 0)
		root->left = insertFN(root->left, node);
	else { //already in table
		destroyFN(node);
	}
	return root;
}

void deleteFN(struct funNode *root, struct funNode *node){
	if (root == NULL || node == NULL) return;
	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		deleteFN(root->right, node);
	else if (cmp < 0)
		deleteFN(root->left, node);
	else { //root == node
		if (node->right == NULL && node->left == NULL){
			destroyFN(node);
			root = NULL;
		}
		else if (node->right != NULL && node->left == NULL){
			replaceFN(node, node->right);
		}
		else if (node->right == NULL && node->left != NULL){
			replaceFN(node, node->left);
		}
		else if (node->right != NULL && node->left != NULL){
			struct funNode *tmp = findMaxFN(node->left);
			tmp->right = node->right;
			replaceFN(node, tmp);
			deleteFN(root, tmp);
		}
	}
}

void replaceFN(struct funNode *out, struct funNode *in){
	destroyString(out->name);
	destroyString(out->types);

	// TODO ukazatel na prvni instrukci
	// TODO deklarace, definice?	ret->offset = 0;

	out->name = in->name;
	out->types = in->types;

	out->lVarTable = in->lVarTable;
	out->varc = in->varc;

	out->left = in->left;
	out->right = in->right;

	free(in);
	in = NULL;
}

struct funNode *findMaxFN(struct funNode *root){
	if (root == NULL) return NULL;

	if (root->right != NULL) return findMaxFN(root->right);
	else return root;
}

struct funNode *searchFT(struct funNode *root, char *expression){
	if (root == NULL) return NULL;
	if (expression == NULL) return NULL;

	int a = strcmp(expression, root->name->data);
	if (a == 0) return root;
	else if (a > 0) return searchFT(root->right, expression);
	else return searchFT(root->left, expression);

	return NULL; // not found
}

void destroyFN (struct funNode *node){
	if (node == NULL) return;
	destroyString(node->name);
	destroyVT(node->lVarTable);
	free(node);
	node = NULL;
}

void destroyFT (struct funNode *root){
	if (root == NULL) return;
	if (root->left != NULL)
		destroyFT(root->left);
	if (root->right != NULL)
		destroyFT(root->right);
	destroyFN(root);
}





// ////////////////////////CLASSES
// //struktura pro  glob. tabulku trid
// struct classNode{
// 	String *name;
//
// 	varNode *lVarTable;
//
// 	struct classNode *left;
// 	struct classNode *right;
// }
//
// //funkce pro praci s glob. tabulkou trid
// struct classNode *newCN(struct tListItem *token);
// struct classNode *insertCN(struct classNode *root, struct classNode *node);
// void deleteCN(struct classNode *root, struct classNode *node);
// void replaceCN(struct classNode *out, struct classNode *in);
// struct classNode *findMaxCN(struct classNode *root);
// struct classNode *searchCT(struct classNode *root, char *exp);
// void destroyCN (struct classNode *node);
// void destroyCT (struct classNode *root);

struct classNode *newCN(struct tListItem *token){
	struct classNode *ret = malloc(sizeof(struct classNode));
	if (ret == NULL){
		fprintf(stderr, "Not enough memory, can't alloc.\n");
		return NULL;
	}

	ret->name = token->data;


	ret->lVarTable = NULL;
	ret->varc = 0;

	// TODO ukazatel na prvni instrukci
	// TODO deklarace, definice?	ret->offset = 0;

	ret->left = NULL;
	ret->right = NULL;

	return ret;
}

struct classNode *insertCN(struct classNode *root, struct classNode *node){
	if (root == NULL){
		root = node;
		return root;
	}

	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		root->right = insertCN(root->right, node);
	else if (cmp < 0)
		root->left = insertCN(root->left, node);
	else { //already in table
		destroyCN(node);
	}
	return root;
}

void deleteCN(struct classNode *root, struct classNode *node){
	if (root == NULL || node == NULL) return;
	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		deleteCN(root->right, node);
	else if (cmp < 0)
		deleteCN(root->left, node);
	else { //root == node
		if (node->right == NULL && node->left == NULL){
			destroyCN(node);
			root = NULL;
		}
		else if (node->right != NULL && node->left == NULL){
			replaceCN(node, node->right);
		}
		else if (node->right == NULL && node->left != NULL){
			replaceCN(node, node->left);
		}
		else if (node->right != NULL && node->left != NULL){
			struct classNode *tmp = findMaxCN(node->left);
			tmp->right = node->right;
			replaceCN(node, tmp);
			deleteCN(root, tmp);
		}
	}
}

void replaceCN(struct classNode *out, struct classNode *in){
	destroyString(out->name);

	// TODO ukazatel na prvni instrukci
	// TODO deklarace, definice?	ret->offset = 0;

	out->name = in->name;

	out->lVarTable = in->lVarTable;
	out->varc = in->varc;

	out->left = in->left;
	out->right = in->right;

	free(in);
	in = NULL;
}

struct classNode *findMaxCN(struct classNode *root){
	if (root == NULL) return NULL;

	if (root->right != NULL) return findMaxCN(root->right);
	else return root;
}

struct classNode *searchCT(struct classNode *root, char *exp){
	if (root == NULL) return NULL;

	int a = strcmp(exp, root->name->data);
	if (a == 0) return root;
	else if (a > 0) return searchCT(root->right, exp);
	else return searchCT(root->left, exp);

	return NULL; // not found
}

void destroyCN (struct classNode *node){
	if (node == NULL) return;
	destroyString(node->name);
	destroyVT(node->lVarTable);

	free(node);
	node = NULL;
}

void destroyCT (struct classNode *root){
	if (root == NULL) return;
	if (root->left != NULL)
		destroyCT(root->left);
	if (root->right != NULL)
		destroyCT(root->right);
	destroyCN(root);
}











// STARE FUNKCE:
// void printInorder(TableNode *node){
// 	if (node == NULL) return;
// 	printInorder(node->left);
// 	printf("%s\n", node->name->data);
// 	printInorder(node->right);
// }

// NEFUNKCNI:
//  TableNode *findParent(TableNode *root, TableNode *node){
// 	if (root == NULL || node == NULL) return NULL;
//
// 	if (root == node) return NULL; //no parent, it is root
// 	else if (root->left == node) return root;
// 	else if (root->right == node) return root;
//
// 	int a = strcmp(node->name->data, root->name->data);
// 	if (a > 0) return findParent(root->right, node);
// 	else return findParent(root->left, node);
// }
