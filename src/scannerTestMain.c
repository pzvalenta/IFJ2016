#include "scannerTestMain.h"

int main(void){


  printf("No  ID\n");

  FILE *file = fopen("/home/petr/Code/IFJ2016/testing/input/example10.java", "r");
  set_file(file);

  String *string = newString();
  set_data(string);

  for(int i = 0; 1; i++){
    int token = getToken(file);
    if (token == T_END) break;
    if (token == T_IDENT){
      printf("identifikator: %s\n", string->data);
    }
    printf("%d  %d\n",i, token);

  }


  printf("Press ENTER key to Continue\n");
  getchar();

  destroyString(string);

  return 0;
}
