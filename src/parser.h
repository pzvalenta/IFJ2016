#ifndef HEADER_PARSER
#define HEADER_PARSER

#include "ial.h"
#include "scanner.h"
#include "str.h"
#include "main.h"
#include "debug.h"


//TODO WARNING
struct tListItem;
struct TableNode;
int parse(struct TableNode *CTRoot, struct TableNode *GTRoot, struct tListItem *head);

#endif
