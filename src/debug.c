#include "debug.h"


void dprint(struct tListItem *token){

  String *data = token->data;
  int id = token->id;

  fprintf(stderr, "current token is: ");
  switch (id) {
    case START:
    fprintf(stderr, "WARNING! pocatecni hodnota tokenu");
    break;

    case T_IDENT:
    fprintf(stderr, "identifikator: ");
    fprintf(stderr, "%s", data->data);

    break;


    case T_C_IDENT:
    fprintf(stderr, "uplny identifikator: ");
    fprintf(stderr, "%s", data->data);

    break;

    case T_KEY:
    fprintf(stderr, "WARNING! pocatecni hodnota pro keyword");
    break;

    case T_BOOL:
    fprintf(stderr, "bool");
    break;

    case T_BREAK:
    fprintf(stderr, "break");
    break;

    case T_CLASS:
    fprintf(stderr, "class");
    break;

    case T_CONTINUE:
    fprintf(stderr, "continue");
    break;

    case T_DO:
    fprintf(stderr, "do");
    break;

    case T_DOUBLE:
      fprintf(stderr, "double");
    break;


    case T_ELSE:
      fprintf(stderr, "else");
    break;

    case T_FOR:
      fprintf(stderr, "for");
    break;

    case T_IF:
      fprintf(stderr, "if");
    break;


    case T_INT:
      fprintf(stderr, "int");
    break;

    case T_RETURN:
      fprintf(stderr, "return");
    break;


    case T_STRING:
      fprintf(stderr, "string");
    break;

    case T_STATIC:
      fprintf(stderr, "static");
    break;

    case T_TRUE:
      fprintf(stderr, "true");
    break;


    case T_VOID:
      fprintf(stderr, "void");
    break;

    case T_WHILE:
      fprintf(stderr, "while");
    break;

    case T_NUMBER_I:
      fprintf(stderr, "celociselny literal: %s", data->data);
    break;


    case T_NUMBER_D:
      fprintf(stderr, "desetinny literal: %s", data->data);
    break;

    case T_STRING_L:
      fprintf(stderr, "retezcovy literal: %s", data->data);
    break;


    case T_END:
      fprintf(stderr, "EOF");
    break;




    case T_ADD:
      fprintf(stderr, "=");
    break;

    case T_EQUAL:
      fprintf(stderr, "==");
    break;

    case T_PLUS:
      fprintf(stderr, "+");
    break;

    case T_GREAT:
      fprintf(stderr, ">");
    break;

    case T_GEQUAL:
      fprintf(stderr, ">=");
    break;

    case T_MINUS:
      fprintf(stderr, "-");
    break;

    case T_LESS:
      fprintf(stderr, "<");
    break;

    case T_LEQUAL:
      fprintf(stderr, "<=");
    break;

    case T_MUL:
      fprintf(stderr, "*");
    break;

    case T_SLASH:
      fprintf(stderr, "/");
    break;

    case T_EXCLAIM:
      fprintf(stderr, "!=");
    break;



    case T_LBRACKET:
      fprintf(stderr, "(");
    break;

    case T_RBRACKET:
      fprintf(stderr, ")");
    break;

    case T_LCBRACKET:
      fprintf(stderr, "{");
    break;

    case T_RCBRACKET:
      fprintf(stderr, "}");
    break;

    case T_LSBRACKET:
      fprintf(stderr, "[");
    break;

    case T_RSBRACKET:
      fprintf(stderr, "]");
    break;

    case T_SEMICLN:
      fprintf(stderr, ";");
    break;

    case T_COMMA:
      fprintf(stderr, ",");
    break;


    case T_DOT:
      fprintf(stderr, ".");
    break;

    default:
      fprintf(stderr, "??? not recognized by debugger, token No.: %d", id);

  }

  fprintf(stderr, "\n");
}


void eprint(int value){
  switch (value) {
    case E_OK:
     fprintf(stderr, "ERROR %d: No Error", value);
    break;

    case E_LEX:
      fprintf(stderr, "ERROR %d: Lexical Analysis Error", value);
    break;

    case E_SYN:
      fprintf(stderr, "ERROR %d: Syntax Analysis Error", value);
    break;

    case E_DEF:
      fprintf(stderr, "ERROR %d: No Definition/ReDefinition Error", value);
    break;

    case E_TYP:
      fprintf(stderr, "ERROR %d: Type Error", value);
    break;

    case E_SEM:
      fprintf(stderr, "ERROR %d: Other Semantical Error", value);
    break;

    case E_INPT:
      fprintf(stderr, "ERROR %d: Input Error", value);
    break;

    case E_INIT:
      fprintf(stderr, "ERROR %d: Not Initialized Error", value);
    break;

    case E_ZERO:
      fprintf(stderr, "ERROR %d: Zero Division Error", value);
    break;

    case E_OTHR:
      fprintf(stderr, "ERROR %d: Other Runtime Error", value);
    break;

    case E_INTERNAL:
      fprintf(stderr, "ERROR %d: Internal Error", value);
    break;

    default: fprintf(stderr, "ERROR %d: Unrecognized Error Value", value);

  }
  fprintf(stderr, "\n");

}
