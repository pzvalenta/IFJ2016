#include "scannerTestMain.h"

int main(void){

  String *test = newString();
  destroyString(test);
  printf("No  ID\n");
  FILE *file = fopen("C:\\Users\\justr\\Documents\\GitHub\\IFJ2016\\testing\\input\\example1.java", "r");
  for(int i = 0; 1; i++){
    Token *token = getToken(file);
    if (token->id == 1) break;
    printf("%d  %d\n",i, token->id);

  }


  printf("Press ENTER key to Continue\n");
  getchar();

  return 0;
}
