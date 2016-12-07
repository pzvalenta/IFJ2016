
// TODO list:
// TODO class Main { static void run() {...} }    --- check
// TODO pridat vestavene funkce
// TODO non static var ve tride neni error
#include "parser.h"
#include "precanal.h"

struct tListItem *token =
    NULL; // globalni promena, ukazatel na momentalni token v tokenlistu
struct classNode *CTRoot = NULL; // koren globalni tabulky trid
struct varNode *GVRoot = NULL;   // koren globalni tabulky promennych
struct funNode *FTRoot = NULL;   // koren glob tabulky funkci

struct classNode *CurrentClass = NULL;
struct funNode *CurrentMethod = NULL;
struct varNode *CurrentVar = NULL;

int SECOND_RUN = 0;

int createCompleteIdent();
int assign_rule();
int declaration_rule();
int static_rule();
int return_rule();
int void_func_call_rule();
int while_rule();
int statement_list();
int statement();
int method();
int class_body();
int class();
int program();
int body();
int param();
int buildIn();
void debugTablePrint();
int function_rule();



int isBuiltIn();
int builtInCall();
int checkMainRun();

int ifjprint();
int ifjsort();
int ifjcompare();
int ifjsubstr();
int ifjlength();
int ifjfind();
int ifjreadInt();
int ifjreadString();
int ifjreadDouble();


int isBuiltIn(){
  struct funNode *tmp = findFunction();
  if (tmp == NULL) return 0;

  if (tmp->name->len < 6) return 0;

  for (int i = 0; i < 6; i++){
    if (tmp->name->data[i] != "ifj16."[i]) return 0;
  }

  return 1;
}


int builtInCall() {
  if (strcmp(token->data->data, "ifj16.print") == 0)
    return ifjprint();

  if (strcmp(token->data->data, "ifj16.sort") == 0)
    return ifjsort();

  if (strcmp(token->data->data, "ifj16.compare") == 0)
    return ifjcompare();

  if (strcmp(token->data->data, "ifj16.substr") == 0)
    return ifjsubstr();

  if (strcmp(token->data->data, "ifj16.length") == 0)
    return ifjlength();

  if (strcmp(token->data->data, "ifj16.find") == 0)
    return ifjfind();

  if (strcmp(token->data->data, "ifj16.readInt") == 0)
    return ifjreadInt();

  if (strcmp(token->data->data, "ifj16.readString") == 0)
    return ifjreadString();

  if (strcmp(token->data->data, "ifj16.readDouble") == 0)
    return ifjreadDouble();


  fprintf(stderr, "pokus o volani neexistujici vestavene funkce: %s\n",
          token->data->data);
  return E_SEM;
}


// TODO TODO TODO resit secondrun v builtin funkcich
int ifjprint() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}


int ifjsort() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjcompare() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjsubstr() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjlength() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjfind() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjreadInt() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjreadString() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}
int ifjreadDouble() {
  // TODO placeholder
  while (token->id != T_SEMICLN && token->id != T_END) {
    token = token->next;
    dprint(token);
  }
  token = token->next;
  return E_OK;
}











////////////////////////////////////////////////////////



int function_rule() {
  fprintf(stderr, "entering function_rule()\n");
  int result = E_OK;
  struct String *params = NULL;
  int returnType = -1;

  dprint(token);

  // momentalni token by mel byt identifikator funkce

  if (isBuiltIn())
    return builtInCall();


  if (SECOND_RUN){
    if (!isFunction())
      return E_DEF;

    result = getFuncParams(&params);
    if (result != E_OK) return result;

    returnType = convertCharToType(params->data[0]);

    if (CurrentVar == NULL){ //musi to byt voidcall
      if(returnType != T_VOID) return E_INIT;
    }
    else {
      if(returnType != CurrentVar->type) return E_TYP;
    }
  }


  token = token->next;
  if (token->id != T_LBRACKET)
    return E_SYN;

  token = token->next;

  int paramPos = 1;
  result = param(params, &paramPos);
  if (result != E_OK)
    return result;

  if (SECOND_RUN){
    if (paramPos != params->len) return E_TYP;
  }

  token = token->next;
  if (token->id != T_SEMICLN)
    return E_SYN;

  token = token->next;
  return E_OK;
}

// STATEMENT --> id = EXPRESSION
// STATEMENT --> id = id() ;
int assign_rule() {
  fprintf(stderr, "entering assign_rule()\n");
  int result = E_OK;
  dprint(token);

  // momentalne je v tokenu id
  // TODO vytvoreni polozky v symtable
  if (SECOND_RUN){
    //set current var TODO
    result = setCurrentVar();
    if (result != E_OK) return result;
  }


  token = token->next; // id = EXPRESSION ;
  dprint(token);
  if (token->id != T_ADD)
    return E_SYN;
  token = token->next;
  dprint(token);

  if (isFunction(token))
    return function_rule();

  result = prec_anal(T_SEMICLN, 0); // id = expression ;
  if (result != E_OK)
    return result;

  token = token->next;
  return result;
}

// STATEMENT --> static TYPE id ;
// STATEMENT --> static TYPE id = EXPRESSION ;

int static_rule() {
  fprintf(stderr, "entering static_rule()\n");
  dprint(token);
  int result = E_OK;

  // momentalne je v tokenu static
  token = token->next;
  if (token->id != T_STRING && token->id != T_INT && token->id != T_DOUBLE)
    return E_SYN;

  // ted je v tokenu type
  int type = token->id;

  token = token->next;
  if (token->id != T_IDENT && token->id != T_C_IDENT)
    return E_SYN;
  // TODO vytvoreni polozky v symtable GLOBALNI
  if (SECOND_RUN) {
    result = newStaticVar();
    if (result != E_OK)
      return result;
    setVarType(type);
  }

  if (token->next->id == T_ADD)
    return assign_rule();
  else {
    token = token->next;
    if (token->id == T_SEMICLN) {
      token = token->next;
      return result;
    } else
      return E_SYN;
  }
}

// STATEMENT --> TYPE id ;
// STATEMENT --> TYPE id = EXPRESSION ;

// static TYPE id
int declaration_rule() {
  fprintf(stderr, "entering declaration_rule()\n");
  int result = E_OK;
  dprint(token);

  int type = token->id;

  // momentalne je v tokenu type
  // int type = token->id; TODO

  token = token->next;
  if (token->id != T_IDENT && token->id != T_C_IDENT)
    return E_SYN;

  if (SECOND_RUN) {
    result = newVar();
    if (result != E_OK)
      return result;
    setVarType(type);
  }

  if (token->next->id == T_ADD)
    return assign_rule();
  else {
    token = token->next;
    if (token->id == T_SEMICLN) {
      token = token->next;
      return result;
    } else
      return E_SYN;
  }
}

int return_rule() {
  fprintf(stderr, "entering return_rule()\n");
  dprint(token);
  int result = E_OK;
  // momentalni token by mel byt return

  token = token->next;
  if (token->id != T_SEMICLN) {
    result = prec_anal(T_SEMICLN, 0);
    if (result != E_OK)
      return result;
  }

  token = token->next;
  return result;
}


int void_func_call_rule() {
  fprintf(stderr, "entering void_func_call_rule()\n");
  dprint(token);
  CurrentVar = NULL;

  // momentalni token je ID

  if (token->id != T_IDENT && token->id != T_C_IDENT)
    return E_SYN;
  // TODO zknotrolovat symtable
  // TODO vygenerovat volani fce

  return function_rule();
}

// PARAM --> epsilon
// PARAM --> id PARAM
// PARAM --> , id PARAM
int param(struct String *params, int *paramPos) {
  fprintf(stderr, "entering param()\n");
  dprint(token);
  int result = E_OK;
  int paramType;

  if (token->id == T_RBRACKET)
    return result; // epsilon

  if (SECOND_RUN){
    if (*paramPos >= params->len) return E_TYP;
    if (token->id == T_IDENT || token->id == T_C_IDENT) {
      paramType = getType();
    } else if (token->id == T_NUMBER_D || token->id == T_NUMBER_I ||
               token->id == T_STRING_L) {
      paramType = token->id;
    } else
      return E_SYN; // id

    if (paramType != convertCharToType(params->data[*paramPos])){
      fprintf(stderr, "debug, implicitni konverze, paramType = %d, params[] = %s\n", paramType,params->data);
      if (paramType != T_NUMBER_I || convertCharToType(params->data[*paramPos]) != T_NUMBER_D) return E_TYP;
    }
    *paramPos = *paramPos + 1;
  } else { // FIRST RUN
    if (token->id == T_IDENT || token->id == T_C_IDENT) {
    } else if (token->id == T_NUMBER_D || token->id == T_NUMBER_I ||
               token->id == T_STRING_L) {
    } else
      return E_SYN; // id
  }



  token = token->next;
  if (token->id == T_COMMA) { // ,
    token = token->next;
    return param(params, paramPos);
  }

  if (token->id == T_RBRACKET)
    return E_OK;
  else
    return E_SYN;
}

// MPARAM --> epsilon
// MPARAM --> TYPE id MPARAM
// MPARAM --> , TYPE id MPARAM
int mparam() {
  fprintf(stderr, "entering mparam()\n");
  dprint(token);
  int result = E_OK;

  if (token->id == T_RBRACKET)
    return result; // epsilon

  // TYPE
  if (token->id == T_INT || token->id == T_DOUBLE || token->id == T_STRING) {
    if (!SECOND_RUN)
      addMparam(token->id);
    token = token->next;
    if (token->id != T_IDENT && token->id != T_C_IDENT)
      return E_SYN; // id
    if (!SECOND_RUN) {
      newVar();
      setVarType(token->prev->id);
    }

    token = token->next;
    if (token->id == T_COMMA) { // ,
      token = token->next;
      return mparam();
    }
    if (token->id == T_RBRACKET)
      return E_OK;
    else
      return E_SYN;
  } else
    return E_SYN;
}

// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }
int while_rule() {
  fprintf(stderr, "entering while_rule()\n");
  dprint(token);
  int result = E_OK;
  // momentalni token je urcite while         // while
  if (token->id != T_WHILE)
    return E_SYN;

  token = token->next;
  if (token->id != T_LBRACKET)
    return E_SYN; // (

  token = token->next;
  result = prec_anal(T_RBRACKET, 1);
  if (result != E_OK)
    return result;

  // nacteny token by mel byt )
  if (token->id != T_RBRACKET)
    return E_SYN; // )

  token = token->next;
  if (token->id != T_LCBRACKET)
    return E_SYN; // {

  token = token->next;
  result = statement_list(); // STATEMENT_LIST
  if (result != E_OK)
    return result;

  // nacteny token by mel byt }
  if (token->id != T_RCBRACKET)
    return E_SYN; // }
  token = token->next;

  return result;
}

// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }
int if_rule() {
  fprintf(stderr, "entering if_rule()\n");
  dprint(token);
  int result = E_OK;
  // momentalni token je urcite if            // if
  if (token->id != T_IF)
    return E_SYN;

  token = token->next;
  if (token->id != T_LBRACKET)
    return E_SYN; // (

  token = token->next;
  result = prec_anal(T_RBRACKET, 1);
  if (result != E_OK)
    return result;



  // nacteny token by mel byt )
  if (token->id != T_RBRACKET)
    return E_SYN; // )

  token = token->next;
  if (token->id != T_LCBRACKET)
    return E_SYN; // {

  token = token->next;
  result = statement_list(); // STATEMENT_LIST
  if (result != E_OK)
    return result;

  // nacteny token by mel byt }
  if (token->id != T_RCBRACKET)
    return E_SYN; // }

  token = token->next;
  if (token->id != T_ELSE)
    return E_SYN; // else

  token = token->next;
  if (token->id != T_LCBRACKET)
    return E_SYN; // {

  token = token->next;
  result = statement_list(); // STATEMENT_LIST
  if (result != E_OK)
    return result;

  // nacteny token by mel byt }
  if (token->id != T_RCBRACKET)
    return E_SYN; // }

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
int statement() {
  fprintf(stderr, "entering statement()\n");
  dprint(token);
  int result = E_OK;
  switch (token->id) {

  // STATEMENT --> id = id (PARAM) ;
  // STATEMENT --> id (PARAM) ;
  // STATEMENT --> id = EXPRESSION ;
  case T_IDENT: // co EXPRESSION --> id (PARAM) !!!?
  case T_C_IDENT:
    // // TODO nacist id, vyhledat v symtable
    // // vlozit do symtable jestli tam neni
    if (token->next->id == T_ADD)
      return assign_rule();
    else if (token->next->id == T_LBRACKET)
      return void_func_call_rule();
    else
      return E_SYN;
    break;

  // STATEMENT --> return EXPRESSION ; TODO
  case T_RETURN:
    return return_rule();
    break;

  // STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }
  // TODO
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

// STATEMENT_LIST --> epsilon | STATEMENT STATEMENT_LIST
int statement_list() {
  int result = E_OK;
  dprint(token);
  fprintf(stderr, "entering statement_list()\n");

  switch (token->id) {
  case T_INT:
  case T_DOUBLE:
  case T_STRING:
  case T_WHILE:
  case T_IF:
  case T_RETURN:
  case T_IDENT:
  case T_C_IDENT:

    // TODO check proti metodam
    fprintf(stderr, "going from statement_list() to statement()\n");
    result = statement();
    //dprint(token);
    if (result != E_OK)
      return result;

    return statement_list();
    // if (token->id != T_SEMICLN && token->id != T_RCBRACKET){ //TODO je to
    // nutne?
    //   return E_SYN;
    // }
    // else {
    //   token = token-> next;
    //   return statement_list();
    // }
    break;

  case T_STATIC:                                     // METHOD / STATEMENT ?
    if (token->next->next->next->id == T_LBRACKET) { // TODO errorcheck
      fprintf(stderr, "leaving statement_list() - found method\n");
      return E_OK;
    } else {
      fprintf(stderr, "going from statement_list() to statement()\n");
      result = statement();
      if (result != E_OK)
        return result;
      return statement_list();
    }
    break;

  default:
    fprintf(stderr, "leaving statement_list()\n");
    return E_OK;
  }
}

// METHOD --> static TYPE id ( PARAM ) { STATEMENT_LIST } // fce jsou vždy
// static
int method() {
  int result = E_OK;
  dprint(token);
  fprintf(stderr, "entering method()\n");

  // momentalni token je urcite static         // static
  if (token->id != T_STATIC)
    return E_SYN;

  token = token->next;
  if (token->id != T_INT && token->id != T_DOUBLE && token->id != T_STRING &&
      token->id != T_VOID)
    return E_SYN; // TYPE

  token = token->next;
  dprint(token);
  if (token->id != T_IDENT && token->id != T_C_IDENT)
    return E_SYN; // id

  if (!SECOND_RUN) {
    result = newFunction();
    if (result != E_OK)
      return result;
    addMparam(token->prev->id);
  } else {
    result = setCurrentMethod();
    if (result != E_OK)
      return result;
  }

  token = token->next;
  dprint(token);

  if (token->id != T_LBRACKET)
    return E_SYN; // (

  token = token->next;
  fprintf(stderr, "going from method() to mparam()\n");
  result = mparam(); // PARAM
  if (result != E_OK)
    return result;

  // nacteny token z prec. analyzy by mel byt  // )
  if (token->id != T_RBRACKET)
    return E_SYN;

  token = token->next;
  if (token->id != T_LCBRACKET)
    return E_SYN; // {

  token = token->next;
  fprintf(stderr, "going from method() to statement_list()\n");
  result = statement_list(); // STATEMENT_LIST
  if (result != E_OK)
    return result;

  // token nacteny statement listem by mel byt }
  if (token->id != T_RCBRACKET)
    return E_SYN; // }
  token = token->next;

  return result;
}

// CLASS_BODY --> epsilon | STATEMENT_LIST CLASS_BODY | METHOD CLASS_BODY
int class_body() {
  int result = E_OK;
  fprintf(stderr, "entering class_body()\n");
  dprint(token);

  switch (token->id) {
  case T_IDENT: // CLASS_BODY --> STATEMENT_LIST
  case T_C_IDENT:
  case T_RETURN:
  case T_IF:
  case T_WHILE:
  case T_INT:
  case T_STRING:
  case T_DOUBLE:
    fprintf(stderr, "going from class_body() to statement_list()\n");
    result = statement_list();
    if (result != E_OK)
      return result;

    return class_body();
    break;

  case T_STATIC:                                     // METHOD / STATEMENT ?
    if (token->next->next->next->id == T_LBRACKET) { // TODO errorcheck
      fprintf(stderr, "going from class_body() to method()\n");
      result = method();
      if (result != E_OK)
        return result;
      return class_body();
    } else {
      fprintf(stderr, "1going from class_body() to statement_list()\n");
      result = statement_list();
      if (result != E_OK)
        return result;

      return class_body();
    }
    break;

  case T_RCBRACKET: // nactena }, konec class_body
    fprintf(stderr, "leaving class_body()\n");
    return E_OK;
    break;

  default:
    return E_SYN;
  }
}

///////////^^^^^^^^^^TODO TODO TODO TODO^^^^^^^^^^^

// CLASS --> class id { CLASS_BODY }
int class() {
  int result = E_OK;
  fprintf(stderr, "entering class()\n");
  dprint(token);

  if (!SECOND_RUN)
    result = newClass();
  else
    result = setCurrentClass();
  if (result != E_OK)
    return result;

  token = token->next;
  if (token->id != T_LCBRACKET)
    return E_SYN;

  token = token->next;
  fprintf(stderr, "going from class() to classbody()\n");
  result = class_body();
  if (result != E_OK)
    return result;

  // token nacteny v class_body() by mel byt

  if (token->id != T_RCBRACKET)
    return E_SYN;

  fprintf(stderr, "leaving class()\n");

  return result;
}

// BODY --> epsilon | CLASS BODY
int body() {
  int result = E_OK;
  fprintf(stderr, "entering body()\n");
  dprint(token);

  switch (token->id) {
  case T_CLASS: // BODY --> CLASS
    token = token->next;
    fprintf(stderr, "going from body() to class()\n");
    result = class();
    if (result != E_OK)
      return result;
    token = token->next;
    result = body();
    break;

  case T_END: // BODY --> epsilon
    fprintf(stderr, "leaving body()\n");
    // TODO check for main void run here!
    return E_OK;
    break;

  default:
    result = E_SYN;
  }
  return result;
}

// PROGRAM --> BODY EOF
int program() {
  int result = E_OK;
  fprintf(stderr, "entering program()\n");
  dprint(token);

  // check for class
  fprintf(stderr, "going from program() to body()\n");
  result = body();
  if (result != E_OK)
    return result;

  fprintf(stderr, "back in program(), expecting EOF\n");
  if (token->id != T_END)
    return E_SYN;

  return result;
}

int buildIn() {
  int result = E_OK;

  token = malloc(sizeof(struct tListItem));
  token->data = newString();
  token->id = T_IDENT;

  for (int i = 0; i < 5; i++) {
    appendChar(token->data, "ifj16"[i]);
  }
  result = newClass();
  if (result != E_OK)
    return result;

  // vestavena funkce ifj16.print
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 5; i++) {
    appendChar(token->data, "print"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_VOID);



  // vestavena funkce ifj16.sort
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 4; i++) {
    appendChar(token->data, "sort"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_STRING);
  addMparam(T_STRING);

  // vestavena funkce ifj16.compare
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 7; i++) {
    appendChar(token->data, "compare"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_INT);
  addMparam(T_STRING);
  addMparam(T_STRING);

  // vestavena funkce ifj16.substr
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 6; i++) {
    appendChar(token->data, "substr"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_STRING);
  addMparam(T_STRING);
  addMparam(T_INT);
  addMparam(T_INT);


  // vestavena funkce ifj16.length
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 6; i++) {
    appendChar(token->data, "length"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_STRING);
  addMparam(T_INT);

  // vestavena funkce ifj16.find
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 4; i++) {
    appendChar(token->data, "find"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  // TODO ! pridat parametry
  addMparam(T_INT);
  addMparam(T_STRING);
  addMparam(T_STRING);


  // vestavena funkce ifj16.readInt
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 7; i++) {
    appendChar(token->data, "readInt"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_INT);


  // vestavena funkce ifj16.readString
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 10; i++) {
    appendChar(token->data, "readString"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_STRING);


  // vestavena funkce ifj16.readDouble
  token->id = T_IDENT;
  token->data = newString();
  for (int i = 0; i < 10; i++) {
    appendChar(token->data, "readDouble"[i]);
  }
  result = newFunction();
  if (result != E_OK)
    return result;
  addMparam(T_DOUBLE);


  fprintf(stderr, "#######FINISHED ADDING BUILTIN FUNCTIONS#########\n");

  return E_OK;
}

int parse(struct tListItem *head) {
  int result = E_OK;
  if (!SECOND_RUN) {
    result = buildIn();
    if (result != E_OK)
      return result;
  }
  else{ // second run
    result = checkMainRun();
    if (result != E_OK) return result;
  }

  CurrentClass = NULL;
  CurrentMethod = NULL;
  CurrentVar = NULL;
  fprintf(stderr, "entering parse()\n");
  token = head;
  dprint(token); // DEBUG
  result = program();

  debugTablePrint();

  return result;
}

void debugTablePrint() {
  if (!SECOND_RUN) {
    fprintf(stderr, "///////////END OF FIRST RUN/////////\n");

  } else {
    fprintf(stderr, "///////////END OF SECOND RUN/////////\n");
  }
  fprintf(stderr, "####################################\n");
  fprintf(stderr, "#   current state of class table   #\n");
  fprintf(stderr, "####################################\n\n");
  fprintf(stderr, "class\n");
  fprintf(stderr, "\ttype\tvar\n");
  fprintf(stderr, "_______________________________\n\n");
  printSpecialC(CTRoot);
  fprintf(stderr, "\n");

  fprintf(stderr, "####################################\n");
  fprintf(stderr, "#  current state of function table #\n");
  fprintf(stderr, "####################################\n");
  fprintf(stderr, "type\tfunc\t(params)\n");
  fprintf(stderr, "\ttype\tvar\n");
  fprintf(stderr, "_______________________________\n\n");

  printSpecialF(FTRoot);
  fprintf(stderr, "\n");

  fprintf(stderr, "####################################\n");
  fprintf(stderr, "#  current state of global var     #\n");
  fprintf(stderr, "####################################\n");
  fprintf(stderr, "\ttype\tvar\n");
  fprintf(stderr, "_______________________________\n\n");
  printSpecialV(GVRoot);
  fprintf(stderr, "\n");
}

int checkMainRun(){
  struct classNode *tmpC = searchCT(CTRoot, "Main");
  if (tmpC == NULL){
    fprintf(stderr, "ERROR, Main doesn't exist\n");
  return E_DEF;
  }


  struct funNode *tmpF = searchFT(FTRoot, "Main.run");
  if (tmpF == NULL) {
    fprintf(stderr, "ERROR, Main.run() doesn't exist\n");
  return E_DEF;
  }

  if (tmpF->types == NULL){
    fprintf(stderr, "ERROR, Main.run() has no params\n");
  return E_DEF;
  }

  if (tmpF->types->len != 1){
    fprintf(stderr, "ERROR, Main.run() has too many params\n");
    return E_DEF;
  }

  if (tmpF->types->data[0] != 'v'){
    fprintf(stderr, "ERROR, Main.run() has nonvoid return type\n");
    return E_DEF;
  }

  return E_OK;
}
