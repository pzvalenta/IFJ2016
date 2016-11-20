#include "scannerTestMain.h"

//symtabletest

int main(void){

  TableNode *classTableRoot = NULL;

  //TableNode *globalTableRoot = NULL;


  String *str1 = newString();
  appendChar(str1, 'c');
  appendChar(str1, 'l');
  appendChar(str1, 's');
  appendChar(str1, '1');
  classTableRoot = insertTN(classTableRoot, newTN(str1, T_CLASS));


  String *str2 = newString();
  appendChar(str2, 'c');
  appendChar(str2, 'l');
  appendChar(str2, 's');
  appendChar(str2, '2');
  classTableRoot = insertTN(classTableRoot, newTN(str2, T_CLASS));

  String *str3 = newString();
  appendChar(str3, 'c');
  appendChar(str3, 'l');
  appendChar(str3, 's');
  appendChar(str3, '3');
  classTableRoot = insertTN(classTableRoot, newTN(str3, T_CLASS));

  String *str4 = newString();
  appendChar(str4, 'c');
  appendChar(str4, 'l');
  appendChar(str4, 's');
  appendChar(str4, '4');
  classTableRoot = insertTN(classTableRoot, newTN(str4, T_CLASS));

  printf("test\n");

  TableNode * s = searchT(classTableRoot, str3->data);
  deleteTN(classTableRoot, s);

  String *str5 = newString();
  appendChar(str5, 'c');
  appendChar(str5, 'l');
  appendChar(str5, 's');
  appendChar(str5, '5');
  classTableRoot = insertTN(classTableRoot, newTN(str5, T_CLASS));

  printInorder(classTableRoot);


  printf("Press ENTER key to Continue\n");
  getchar();

  return 0;
}
