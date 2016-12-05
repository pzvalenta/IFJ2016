#include "scannerTestMain.h"
#include <stdbool.h>


void printIdent (Token * token)
{

  //TODO prvne se prohleda tabulka symbolu
    SymTableNode * node= (SymTableNode *) token->data.s;
    if(node->name!=NULL)
    {
      fprintf(stderr,"node->name->data: \'%s\'", node->name->data);
      return;
    }

    fprintf(stderr,"prohleda se tabulka symbolu");

    //fprintf(stderr,
("token->data.s: \'%s\'",token->data.s);

}

void printInt (Token *token)
{

   fprintf(stderr,"token->data.i :\"%ld\"",token->data.i);
}

void printFloat (Token *token)
{
   fprintf(stderr,"token->data.f :\"%f\"",token->data.f);
}

void printString (Token *token)
{
  fprintf(stderr,"tady bude retezec");
  // fprintf(stderr,"token->data.s :\"%s\"",token->data.s->data); tohle haze segmentation fault
}

//argument -jmeno souboru
int main(int argc, char *argv[]){


  fprintf(stderr,"No\t ID\n");
  FILE *file = fopen(argv[1], "r");
  set_file(file);

  for(int i = 1; 1; i++)
    {
      Token *token = getToken();
      if (token->id == 1) break;

      fprintf(stderr,
("%d\t %d\t",i, token->id);

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
	default: fprintf(stderr,"N/A");
	}

      fprintf(stderr,"\n");
    }

  return 0;
}
