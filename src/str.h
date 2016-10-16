#ifndef HEADER_STRING
#define HEADER_STRING

typedef struct _String String;

String *newString(void);

void resizeString(String *string);

void appendChar(String *str, char c);

void destroyStringData(String *string);

void destroyString(String *string);





#endif
