#include "ial.h"
// Symbol Table implementation
//TODO ERRORS

TableNode *newTN(String *str, int token_id){
	TableNode *ret = malloc(sizeof(TableNode));
	if (ret == NULL){
		fprintf(stderr, "Not enough memory, can't alloc.\n");
		return NULL;
	}

	ret->name = str;
	ret->id = token_id;
	ret->state = 0;
	ret->data = NULL;
	ret->global = NULL;
	ret->localTable = NULL;
	ret->funcStart = NULL;

	ret->left = NULL;
	ret->right = NULL;
	return ret;
}


TableNode *insertTN(TableNode *root, TableNode *node){
	if (root == NULL){
		root = node;
		return root;
	}

	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		root->right = insertTN(root->right, node);
	else if (cmp < 0)
		root->left = insertTN(root->left, node);
	else { //already in table
		destroyTN(node);
	}
	return root;
}


void deleteTN(TableNode *root, TableNode *node){
	if (root == NULL || node == NULL) return;
	int cmp = strcmp(node->name->data, root->name->data);
	if (cmp > 0)
		deleteTN(root->right, node);
	else if (cmp < 0)
		deleteTN(root->left, node);
	else { //root == node
		if (node->right == NULL && node->left == NULL){
			destroyTN(node);
			root = NULL;
		}
		else if (node->right != NULL && node->left == NULL){
			replaceTN(node, node->right);
		}
		else if (node->right == NULL && node->left != NULL){
			replaceTN(node, node->left);
		}
		else if (node->right != NULL && node->left != NULL){
			TableNode *tmp = findMaxTN(node->left);
			tmp->right = node->right;
			replaceTN(node, tmp);
			deleteTN(root, tmp);
		}
	}
}



void replaceTN(TableNode *out, TableNode *in){
	destroyString(out->data);
	destroyString(out->name);
	destroyT(out->localTable);
//DONE pokud je localTable != NULL, destroy LT

	out->name = in->name;
	out->id = in->id;
	out->state = in->state;
	out->data = in->data;
	out->global = in->global;
	out->localTable = in->localTable;

	out->left = in->left;
	out->right = in->right;
	free(in);
	in = NULL;
}


TableNode *findMaxTN(TableNode *root){
	if (root == NULL) return NULL;

	if (root->right != NULL) return findMaxTN(root->right);
	else return root;
}


TableNode *searchT(TableNode *root, char *exp){
	if (root == NULL) return NULL;

	int a = strcmp(exp, root->name->data);
	if (a == 0) return root;
	else if (a > 0) return searchT(root->right, exp);
	else return searchT(root->left, exp);

	return NULL; // not found
}


void destroyTN (TableNode *node){
	if (node == NULL) return;
	destroyString(node->data);

	destroyString(node->name);

	destroyT(node->localTable);



	free(node);
	node = NULL;
}

void destroyT (TableNode *root){
	if (root == NULL) return;
	if (root->left != NULL)
		destroyT(root->left);
	if (root->right != NULL)
		destroyT(root->right);
	destroyTN(root);
}


void printInorder(TableNode *node){
	if (node == NULL) return;
	printInorder(node->left);
	printf("%s\n", node->name->data);
	printInorder(node->right);
}





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
