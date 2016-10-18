#ifndef HEADER_TOKEN
#define HEADER_TOKEN

#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "scanner.h"




Token *newToken();

void destroyToken(Token *token);

#endif
