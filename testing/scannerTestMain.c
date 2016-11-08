#include "scannerTestMain.h"
#include <stdbool.h>


void printIdent (Token * token)
{

  //TODO prvne se prohleda tabulka symbolu
    SymTableNode * node= (SymTableNode *) token->data.s;
    if(node->name!=NULL)
    {
      printf("node->name->data: \'%s\'", node->name->data);
      return;
    }
    
    printf("prohleda se tabulka symbolu");
    
    //printf("token->data.s: \'%s\'",token->data.s);

}

void printInt (Token *token)
{

   printf("token->data.i :\"%ld\"",token->data.i);
}

void printFloat (Token *token)
{
   printf("token->data.f :\"%f\"",token->data.f);
}

void printString (Token *token)
{
  printf("tady bude retezec");
  // printf("token->data.s :\"%s\"",token->data.s->data); tohle haze segmentation fault
}

//argument -jmeno souboru
int main(int argc, char *argv[]){


  printf("No\t ID\n");
  FILE *file = fopen(argv[1], "r");
  set_file(file);

  for(int i = 1; 1; i++)
    {
      Token *token = getToken();
      if (token->id == 1) break;
      
      printf("%d\t %d\t",i, token->id);
      
      switch (token->id)
	{
	case T_IDENT: printIdent(token);
	  break;
	case T_NUMBER_I: printInt(token);
	  break;
	case T_NUMBER_D: printFloat(token);
	  break;
	case T_STRING: printString(token);
	  break;
	default: printf("N/A");
	}

      printf("\n");
    }

  return 0;
}
