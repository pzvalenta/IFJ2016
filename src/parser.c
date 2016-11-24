
//TODO list:
//TODO nahradit token = getToken() + error check nejakym onelinerem
// if (!isok(token = getToken()))
//TODO class Main { static void run() {...} }    --- check
//TODO pridat vestavene funkce
#include "parser.h"

struct tListItem *token;    // globalni promena, ukazatel na momentalni token v tokenlistu
String *data;  // globalni promenna, ve ktere budou ulozena data tokenu
TableNode *CTRoot = NULL; //koren globalni tabulky trid
TableNode *GTRoot = NULL; //koren globalni tabulky funkci a promennych

TableNode *CurrentClass = NULL;
TableNode *CurrentMethod = NULL;


int while_rule();
int statement_list();
int statement();
int method();
int class_body();
int class();
int program();
int body();

// nemelo by to byt s novou formou tokenu potreba
// // vraci 0 kdyz je token ERROR
// int isok(char token){
//   if (token > 1 && token < 11)
//     return 0;
//   else
//     if (token == 99) return 0;
//     else return 1;
// }





// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }
int while_rule(){
  printf("entering while_rule()\n");
  int result = E_OK;
  //momentalni token je urcite while         // while

  token = token->next;
  if(token->id != T_LBRACKET) return E_SYN;  // (

  token = token->next;
  // TODO precedencni analyza                // EXPRESSION
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_RBRACKET && token->id != T_END) token = token->next;

  //nacteny token by mel byt )
  if(token->id != T_RBRACKET) return E_SYN;  // )

  token = token->next;
  if(token->id != T_LCBRACKET) return E_SYN; // {

  token = token->next;
  result = statement_list();                 // STATEMENT_LIST
  if(result != E_OK) return result;

  //nacteny token by mel byt }
  if(token->id != T_RCBRACKET) return E_SYN; // }

  return result;
}


// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }
int if_rule(){
  printf("entering if_rule()\n");
  int result = E_OK;
  //momentalni token je urcite if            // if

  token = token->next;
  if(token->id != T_LBRACKET) return E_SYN;  // (

  token = token->next;
  // TODO precedencni analyza                // EXPRESSION
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_RBRACKET && token->id != T_END) token = token->next;


  //nacteny token by mel byt )
  if(token->id != T_RBRACKET) return E_SYN;  // )

  token = token->next;
  if(token->id != T_LCBRACKET) return E_SYN; // {

  token = token->next;
  result = statement_list();                 // STATEMENT_LIST
  if(result != E_OK) return result;

  //nacteny token by mel byt }
  if(token->id != T_RCBRACKET) return E_SYN; // }

  token = token->next;
  if(token->id != T_ELSE) return E_SYN;      // else

  token = token->next;
  if(token->id != T_LCBRACKET) return E_SYN; // {

  token = token->next;
  result = statement_list();                 // STATEMENT_LIST
  if(result != E_OK) return result;

  //nacteny token by mel byt }
  if(token->id != T_RCBRACKET) return E_SYN; // }
  return result;
}


// STATEMENT --> epsilon     TODO
// STATEMENT --> id = EXPRESSION ;  TODO
// STATEMENT --> return EXPRESSION ; TODO
// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }  TODO
// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }   TODO
// STATEMENT --> id = id (PARAM) ;   TODO
// STATEMENT --> id (PARAM) ;        TODO

// STATEMENT --> static TYPE id ;
// STATEMENT --> TYPE id ;
// STATEMENT --> TYPE id = EXPRESSION ;
int statement(){
  printf("entering statement()\n");
  int result = E_OK;
  switch (token->id) {
    // STATEMENT --> id = id (PARAM) ;   TODO
    // STATEMENT --> id (PARAM) ;        TODO
    // STATEMENT --> id = EXPRESSION ;  TODO
    case T_IDENT: // co EXPRESSION --> id (PARAM)   TODO TODO TODO
      // // TODO nacist id, vyhledat v symtable
      // // vlozit do symtable jestli tam neni
      //
      // token = getToken();
      // if (!isok(token)) return E_LEX;
      // dprint(token); //DEBUG
      //
      //
      // switch (token) {
      //   // STATEMENT --> id = EXPRESSION
      //   // STATEMENT --> id = id(PARAM)
      //   case T_ADD:
      //     token = getToken();
      //     if (!isok(token)) return E_LEX;
      //     dprint(token); //DEBUG
      //
      //
      //     switch (token) {
      //       // STATEMENT --> id = id(PARAM)
      //       case T_IDENT:
      //       break;
      //
      //       //case : // EXPRESSION
      //
      //       default:
      //         return E_SYN;
      //     }
      //   break;
      //
      //   default:
      //     return E_SYN;
      // }
      //
      // // TODO predat rizeni precedencni analyze

      //placeholder
      while(token->id != T_SEMICLN && token->id != T_END) token = token->next;
      return result;
    break;


    // STATEMENT --> return EXPRESSION ; TODO
    case T_RETURN:
      //result = return_rule();
      //placeholder
      while(token->id != T_SEMICLN && token->id != T_END) token = token->next;
      return result;
    break;

    // STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }  TODO
    case T_IF:
      return if_rule();
    break;

    // STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }   TODO
    case T_WHILE:
      return while_rule();
    break;

    // STATEMENT --> static TYPE id ;
    // STATEMENT --> static TYPE id = EXPRESSION;
    case T_STATIC:
      //result = static_rule();
      //placeholder
      while(token->id != T_SEMICLN && token->id != T_END) token = token->next;
      return result;
    break;

    // STATEMENT --> TYPE id ;
    // STATEMENT --> TYPE id = EXPRESSION ;
    case T_INT:
    case T_DOUBLE:
    case T_STRING:
      //result = assing_rule();
      //placeholder
      while(token->id != T_SEMICLN && token->id != T_END) token = token->next;
      return result;
    break;

    default:
      return E_SYN;

  }
  return E_SYN;
}

//STATEMENT_LIST --> epsilon | STATEMENT STATEMENT_LIST
int statement_list(){
  int result = E_OK;
  printf("entering statement_list()\n");

  return result;
  switch (token->id){
    case T_INT:
    case T_DOUBLE:
    case T_STRING:
    case T_STATIC:
    case T_WHILE:
    case T_IF:
    case T_RETURN:
    case T_IDENT:

    // TODO check proti metodam
      result = statement();
      if (result != E_OK) return result;

      if (token->id != T_SEMICLN || token->id != T_RCBRACKET){ //TODO je to nutne?
        return E_SYN;
      }
      else {
        token = token-> next;
        return statement_list();
      }
    break;

    case T_SEMICLN:
    case T_RCBRACKET:
      token = token->next;
      return statement_list();
    break;

    default:
      return E_OK;
  }
}

//METHOD --> static TYPE id ( PARAM ) { STATEMENT_LIST } // fce jsou vždy static
int method(){
  int result = E_OK;
  //cast martinoveho kodu TODO
  // TODO placeholder
  while(token->id != T_RCBRACKET && token->id != T_END) token = token->next;
  return result;
}

//CLASS_BODY --> epsilon | STATEMENT_LIST CLASS_BODY | METHOD CLASS_BODY
int class_body(){
  int result = E_OK;
  printf("entering class_body()\n");

  switch (token->id){
    case T_IDENT:  // CLASS_BODY --> STATEMENT_LIST
    case T_RETURN:
    case T_IF:
    case T_WHILE:
      printf("going from class_body() to statement_list()\n");
      result = statement_list();
      if (result != E_OK) return result;
      return class_body();
    break;


    case T_INT:  //CLASS_BODY --> METHOD
    case T_STRING:
    case T_VOID:
    case T_STATIC:
      printf("going from class_body() to method()\n");
      result = method();
      if (result != E_OK) return result;
      return class_body();
    break;

    case T_RCBRACKET: //nactena }, konec class_body
      printf("leaving class_body()\n");
      return E_OK;
    break;

    default: return E_SYN;
  }
}

///////////^^^^^^^^^^TODO TODO TODO TODO^^^^^^^^^^^

//CLASS --> class id { CLASS_BODY }
int class(){
  int result = E_OK;
  printf("entering class()\n");

  if (token->id != T_IDENT) return E_SYN;
  else {
      /// vytvorit novou node v globalni tabulce trid
      /// error check
      CurrentClass = newTN(token);
      if (CurrentClass == NULL) return E_INTERNAL;
      CurrentMethod = NULL; // nejsme v zadne funkci

      // vlozi novou node do tabulky, data = jmeno, token = id
      CTRoot = insertTN(CTRoot, CurrentClass);
  }

  token = token->next;
  if (token->id != T_LCBRACKET) return E_SYN;
  dprint(token); //DEBUG


  token = token->next;
  dprint(token); //DEBUG
  printf("going from class() to classbody()\n");
  result = class_body();
  if (result != E_OK) return result;

  // token nacteny v class_body() by mel byt
  if (token->id != T_RCBRACKET) return E_SYN;

  token = token->next;
  dprint(token); //DEBUG
  printf("leaving class()\n");

  return result;
}

//BODY --> epsilon | CLASS BODY
int body(){
  int result = E_OK;
  printf("entering body()\n");

  switch (token->id){
    case T_CLASS: //BODY --> CLASS
      token = token->next;
      dprint(token); //DEBUG

      printf("going from body() to class()\n");
      result = class();
      if (result != E_OK) return result;

      result = body();
    break;

    case T_END: //BODY --> epsilon
      printf("leaving body()\n");

      //TODO check for main void run here!
      return E_OK;
    break;

    default:
      result = E_SYN;
  }
  return result;
}

//PROGRAM --> BODY EOF
int program(){
  int result = E_OK;
  printf("entering program()\n");


  //check for class
  printf("going from program() to body()\n");
  result = body();
  if (result != E_OK) return result;

  printf("back in program(), expecting EOF\n");
  if (token->id != T_END) return E_SYN;

  return result;
}


int parse(TableNode *CTRoot, TableNode *GTRoot, struct tListItem *head){
  int result = E_OK;
  printf("entering parse()\n");

  token = head;
  dprint(token); //DEBUG
  result = program();

  return result;
}
