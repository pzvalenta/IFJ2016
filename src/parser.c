
//TODO list:
//TODO nahradit token = getToken() + error check nejakym onelinerem
// if (!isok(token = getToken()))
//TODO class Main { static void run() {...} }    --- check
//TODO pridat vestavene funkce
#include "parser.h"
#include "precanal.h"

struct tListItem *token = NULL;    // globalni promena, ukazatel na momentalni token v tokenlistu
TableNode *CTRoot = NULL; //koren globalni tabulky trid
TableNode *GTRoot = NULL; //koren globalni tabulky funkci a promennych

TableNode *CurrentClass = NULL;
TableNode *CurrentMethod = NULL;


int ifjfind();
int ifjprint();
int assign_rule();
int declaration_rule();
int static_rule();
int return_rule();
int void_func_call_rule();
int func_call_rule();
int while_rule();
int statement_list();
int statement();
int method();
int class_body();
int class();
int program();
int body();
int param();



int ifjfind(){
  printf("entering ifjfind()\n");
  int result = E_OK;

  //TODO placeholder
  while (token->id != T_RBRACKET && token->id != T_END){
    token = token->next;
    dprint(token);
  }

  return result;
}


int ifjprint(){
  printf("entering ifjprint()\n");
  int result = E_OK;

  //TODO placeholder
  while (token->id != T_RBRACKET && token->id != T_END){
    token = token->next;
    dprint(token);
  }

  return result;
}

int assign_rule(){
  printf("entering assign_rule()\n");
  int result = E_OK;
  dprint(token);

  // momentalne je v tokenu id
  //TODO vytvoreni polozky v symtable

  token = token->next;  // id = EXPRESSION ;
  if (token->id != T_ADD) return E_SYN;


  if (strcmp("ifj16.print", token->data->data) == 0){
    result = ifjprint();
    token = token->next;
    return result;
  }
  if (strcmp("ifj16.find", token->data->data) == 0){
    result = ifjfind();
    token = token->next;
    return result;
  }

  //TODO volani precedencni
  token = token->next;

  result = prec_anal(T_SEMICLN);
  if (result != E_OK) return result;

  dprint(token);

  token = token->next;
  dprint(token);
  return result;
}




//STATEMENT --> static TYPE id ;
//STATEMENT --> static TYPE id = EXPRESSION ;

int static_rule(){
  printf("entering static_rule()\n");
  int result = E_OK;

  // momentalne je v tokenu static
  token = token->next;
  if (token->id != T_STRING && token->id != T_INT && token->id != T_DOUBLE)
  return E_SYN;

  //ted je v tokenu type
  //int type = token->id; TODO

  token = token->next;
  if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;
  //TODO vytvoreni polozky v symtable GLOBALNI

  token = token->next;
  if (token->id == T_SEMICLN){
    token = token->next;
    return result;
  }

  //TYPE id = EXPRESSION ;

  if (token->id != T_ADD) return E_SYN;

  //TODO volani precedencni
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_SEMICLN && token->id != T_END){
    token = token->next;
    dprint(token);
  }

  token = token->next;
  return result;
}


//STATEMENT --> TYPE id ;
//STATEMENT --> TYPE id = EXPRESSION ;
int declaration_rule(){
  printf("entering declaration_rule()\n");
  int result = E_OK;
  dprint(token);

  // momentalne je v tokenu type
  //int type = token->id; TODO

  token = token->next;
  if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;
  //TODO vytvoreni polozky v symtable

  token = token->next;
  if (token->id == T_SEMICLN){
    token = token->next;
    return result;
  }

  //TYPE id = EXPRESSION ;

  if (token->id != T_ADD) return E_SYN;

  //TODO volani precedencni
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_SEMICLN && token->id != T_END){
    token = token->next;
    dprint(token);
  }

  token = token->next;
  return result;
}

int return_rule(){
  printf("entering return_rule()\n");
  int result = E_OK;
  //momentalni token by mel byt return

  token = token->next;
  //TODO volani precedencni
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_SEMICLN && token->id != T_END){
    token = token->next;
    dprint(token);
  }

  token = token->next;
  return result;
}


int func_call_rule(){
  printf("entering func_call_rule()\n");
  int result = E_OK;

  //momentalni token je ID

  //TODO zknotrolovat symtable

  token = token->next;
  if (token->id != T_ADD)return E_SYN;

  token = token->next;
  if (token->id != T_IDENT && token->id != T_C_IDENT )return E_SYN;
  //TODO zknotrolovat symtable
  //TODO vygenerovat volani fce

  token = token->next;
  result = param();  //generace parametru
  if(result != E_OK) return result;
  //token by mel byt )

  token = token->next;
  if (token->id != T_SEMICLN)return E_SYN;

  token = token->next;
  return result;
}


int void_func_call_rule(){
  printf("entering void_func_call_rule()\n");
  int result = E_OK;

  //momentalni token je ID


  if (token->id != T_IDENT && token->id != T_C_IDENT)return E_SYN;
  //TODO zknotrolovat symtable
  //TODO vygenerovat volani fce
  if (strcmp("ifj16.print", token->data->data) == 0){
    result = ifjprint();
    token = token->next;
    return result;
  }
  if (strcmp("ifj16.find", token->data->data) == 0){
    result = ifjfind();
    token = token->next;
    return result;
  }



  token = token->next;
  if (token->id != T_LBRACKET)return E_SYN;


  token = token->next;
  result = param();  //generace parametru

  if(result != E_OK) return result;
  //token by mel byt )

  token = token->next;
  if (token->id != T_SEMICLN)return E_SYN;

  dprint(token);
  token = token->next;
  return result;
}


// PARAM --> epsilon
// PARAM --> id PARAM
// PARAM --> , id PARAM
int param(){
  printf("entering param()\n");
  int result = E_OK;

  if (token->id == T_RBRACKET) return result;  //epsilon


  if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;    // id
  //TODO zpracovani

  token = token->next;
  if(token->id == T_COMMA){                  // ,
    token = token->next;
    return param();
  }


  if (token->id == T_RBRACKET) return E_OK;
  else return E_SYN;
}

// MPARAM --> epsilon
// MPARAM --> TYPE id MPARAM
// MPARAM --> , TYPE id MPARAM
int mparam(){
  printf("entering mparam()\n");
  int result = E_OK;

  if (token->id == T_RBRACKET) return result;  //epsilon

                                               // TYPE
  if (token->id == T_INT || token->id == T_DOUBLE || token->id == T_STRING){
    token = token->next;
    if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;    // id
    //TODO zpracovani

    token = token->next;
    if(token->id == T_COMMA){                  // ,
      token = token->next;
      return mparam();
    }
    if (token->id == T_LBRACKET) return E_OK;
    else return E_SYN;
  }
  else return E_SYN;
}

// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }
int while_rule(){
  printf("entering while_rule()\n");
  int result = E_OK;
  //momentalni token je urcite while         // while
  if (token->id != T_WHILE) return E_SYN;

  token = token->next;
  if(token->id != T_LBRACKET) return E_SYN;  // (

  token = token->next;
  // TODO precedencni analyza                // EXPRESSION
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_RBRACKET && token->id != T_END){
    token = token->next;
    dprint(token);
  }

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

  return result;
}


// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }
int if_rule(){
  printf("entering if_rule()\n");
  int result = E_OK;
  //momentalni token je urcite if            // if
  if (token->id != T_IF) return E_SYN;

  token = token->next;
  if(token->id != T_LBRACKET) return E_SYN;  // (

  token = token->next;
  // TODO precedencni analyza                // EXPRESSION
  // TODO // placeholder pro precedencni analyzu
  while(token->id != T_RBRACKET && token->id != T_END){
    token = token->next;
    dprint(token);
  }

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

  token = token->next;
  return result;
}


// STATEMENT --> epsilon
// STATEMENT --> id = EXPRESSION ;
// STATEMENT --> return EXPRESSION ;
// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }
// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }
// STATEMENT --> id = id (PARAM) ;
// STATEMENT --> id (PARAM) ;

// STATEMENT --> static TYPE id ;
// STATEMENT --> TYPE id ;
// STATEMENT --> TYPE id = EXPRESSION ;
int statement(){
  printf("entering statement()\n");
  int result = E_OK;
  switch (token->id) {
    // STATEMENT --> id = id (PARAM) ;
    // STATEMENT --> id (PARAM) ;
    // STATEMENT --> id = EXPRESSION ;
    case T_IDENT: // co EXPRESSION --> id (PARAM)
    case T_C_IDENT:
      // // TODO nacist id, vyhledat v symtable
      // // vlozit do symtable jestli tam neni
      if (token->next->id == T_ADD){
        if (token->next->next->id == T_IDENT && token->next->next->next->id == T_LBRACKET)
        return func_call_rule(); // id = id (PARAM) ;
        else // id = EXPRESSION ; TODO
        return assign_rule();


      }
      else if (token->next->id == T_LBRACKET){
        //       id (PARAM) ;
        result = void_func_call_rule();
        token = token->next;
        return result;
      }

      return result;
    break;


    // STATEMENT --> return EXPRESSION ; TODO
    case T_RETURN:
      result = return_rule();
      //placeholder
      while(token->id != T_SEMICLN && token->id != T_END){
        token = token->next;
        dprint(token);
      }
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
    case T_STATIC: // nejedna se o method, bylo to vylouceno v statement_list()
      return static_rule();
    break;

    // STATEMENT --> TYPE id ;
    // STATEMENT --> TYPE id = EXPRESSION ;
    case T_INT:
    case T_DOUBLE:
    case T_STRING:
      return declaration_rule();
    break;

    default:
      return result;

  }
  return E_SYN;
}

//STATEMENT_LIST --> epsilon | STATEMENT STATEMENT_LIST
int statement_list(){
  int result = E_OK;
  printf("entering statement_list()\n");

  switch (token->id){
    case T_INT:
    case T_DOUBLE:
    case T_STRING:
    case T_WHILE:
    case T_IF:
    case T_RETURN:
    case T_IDENT:
    case T_C_IDENT:

    // TODO check proti metodam
      printf("going from statement_list() to statement()\n");
      result = statement();
      dprint(token);
      if (result != E_OK) return result;

      return statement_list();
      // if (token->id != T_SEMICLN && token->id != T_RCBRACKET){ //TODO je to nutne?
      //   return E_SYN;
      // }
      // else {
      //   token = token-> next;
      //   return statement_list();
      // }
    break;

    case T_STATIC:  // METHOD / STATEMENT ?
      if (token->next->next->next->id == T_LBRACKET){ //TODO errorcheck
        printf("leaving statement_list() - found method\n");
        return E_OK;
      }
      else {
        printf("going from statement_list() to statement()\n");
        result = statement();
        if (result != E_OK) return result;
        return statement_list();
      }
    break;



    default:
      printf("leaving statement_list()\n");
      return E_OK;
  }
}

//METHOD --> static TYPE id ( PARAM ) { STATEMENT_LIST } // fce jsou vždy static
int method(){
  int result = E_OK;
  printf("entering method()\n");


  //momentalni token je urcite static         // static
  if (token->id != T_STATIC) return E_SYN;

  token = token->next;
  if (token->id != T_INT && token->id != T_DOUBLE && token->id != T_STRING && token->id != T_VOID)
  return E_SYN;                               // TYPE

  token = token->next;
  if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;     // id

  // TODO newTN GTable

  token = token->next;
  if (token->id != T_LBRACKET) return E_SYN;  // (

  token = token->next;
  printf("going from method() to mparam()\n");
  result = mparam();                           // PARAM
  if (result != E_OK) return result;

  //nacteny token z prec. analyzy by mel byt  // )
  if (token->id != T_RBRACKET) return E_SYN;

  token = token->next;
  if (token->id != T_LCBRACKET) return E_SYN; // {

  token = token->next;
  printf("going from method() to statement_list()\n");
  result = statement_list();                  // STATEMENT_LIST

  // token nacteny statement listem by mel byt }
  if (token->id != T_RCBRACKET) return E_SYN; // }


  return result;
}

//CLASS_BODY --> epsilon | STATEMENT_LIST CLASS_BODY | METHOD CLASS_BODY
int class_body(){
  int result = E_OK;
  printf("entering class_body()\n");
  dprint(token);

  switch (token->id){
    case T_IDENT:  // CLASS_BODY --> STATEMENT_LIST
    case T_C_IDENT:
    case T_RETURN:
    case T_IF:
    case T_WHILE:
    case T_INT:
    case T_STRING:
    case T_DOUBLE:
      printf("going from class_body() to statement_list()\n");
      result = statement_list();
      if (result != E_OK) return result;

      return class_body();
    break;

    case T_STATIC:  // METHOD / STATEMENT ?
      if (token->next->next->next->id == T_LBRACKET){ //TODO errorcheck
        printf("going from class_body() to method()\n");
        result = method();
        if (result != E_OK) return result;
        return class_body();
      }
      else {
        printf("1going from class_body() to statement_list()\n");
        result = statement_list();
        if (result != E_OK) return result;

        dprint(token);
        return class_body();
      }
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

  if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;
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

  dprint(token); //DEBUG
  printf("leaving class()\n");

  return result;
}

//BODY --> epsilon | CLASS BODY
int body(){
  int result = E_OK;
  printf("entering body()\n");

  dprint(token);

  switch (token->id){
    case T_CLASS: //BODY --> CLASS
      token = token->next;
      dprint(token); //DEBUG

      printf("going from body() to class()\n");
      result = class();
      if (result != E_OK) return result;

      token = token->next;
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
