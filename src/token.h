#ifndef HEADER_TOKEN
#define HEADER_TOKEN

typedef struct _Token Token;

Token *newToken();

void destroyToken(Token *token);

#endif