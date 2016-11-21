
//TODO list:
//TODO nahradit token = getToken() + error check nejakym onelinerem
// if (!isok(token = getToken()))
//TODO class Main { static void run() {...} }    --- check
//TODO pridat vestavene funkce

char token;    // globalni promena, do ktere se bude vkladat navratova hodnota z getToken
String *data;  // globalni promenna, ve ktere budou ulozena data tokenu
TableNode *CTRoot = NULL; //koren globalni tabulky trid
TableNode *GTRoot = NULL; //koren globalni tabulky funkci a promennych

TableNode *CurrentClass = NULL;
TableNode *CurrentMethod = NULL;


// vraci 0 kdyz je token ERROR
int isok(char token){
  if (token > 1 && token < 11)
    return 0;
  else
    if (token == 99) return 0;
    else return 1;
}


// STATEMENT --> epsilon     TODO
// STATEMENT --> id = EXPRESSION ;  TODO
// STATEMENT --> return EXPRESSION ; TODO
// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }  TODO
// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }   TODO
// STATEMENT --> id = id (PARAM) ;   TODO
// STATEMENT --> id (PARAM) ;        TODO
int statement(){
  int result = E_OK;
  switch (token) {
    case T_IDENT: // co EXPRESSION --> id (PARAM)   TODO TODO TODO
      // TODO nacist id, vyhledat v symtable
      // TODO predat rizeni precedencni analyze
    break;


  }
}

//STATEMENT_LIST --> epsilon | STATEMENT STATEMENT_LIST
int statement_list(){
  int result = E_OK;
  switch (token){
    case STATEMENT:  //TODO
      result = statement();
      if (result != E_OK) return result;
      return statement_list();
    break;

    case cokoliv cim nezacina statement: //TODO
      return E_OK;
    break;

    case default:
      return E_SYN;
    break;
  }
}

int method(){
  //cast martinoveho kodu TODO
}

//CLASS_BODY --> epsilon | STATEMENT_LIST CLASS_BODY | METHOD CLASS_BODY
int class_body(){
  int result = E_OK;
  switch (token){
    case T_IDENT:  // CLASS_BODY --> STATEMENT_LIST
    case T_RETURN:
    case T_IF:
    case T_WHILE:
      result = statement_list();
      if (result != E_OK) return result;
      return class_body();
    break;


    case T_INT:  //CLASS_BODY --> METHOD
    case T_STRING:
    case T_VOID:
    case T_STATIC:
      result = method();
      if (result != E_OK) return result;
      return class_body();
    break;

    case T_RCBRACKET: //nactena }, konec class_body
      return E_OK;
    break;

    default: return E_SYN;
  }
}

//CLASS --> class id { CLASS_BODY }
int class(){
  int result = E_OK;
  if (token != T_IDENT) return E_SYN;
  else {
      /// vytvorit novou node v globalni tabulce trid
      /// error check
      CurrentClass = newTN(data, token);
      if (CurrentClass == NULL) return E_INTERNAL;

      // vlozi novou node do tabulky, data = jmeno, token = id
      CTRoot = insertTN(CTRoot, newNode);
  }

  token = getToken();
  if (token != T_LCBRACKET) return E_SYN;

  token = getToken();
  if (!isok(token)) return LEX_ERROR; // error check

  result = class_body();
  if (result != E_OK) return result;

  // token nacteny v class_body() by mel byt
  if (token != T_RCBRACKET) return E_SYN;

  token = getToken();
  if (!isok(token)) return LEX_ERROR;

  return result;
}

//BODY --> epsilon | CLASS BODY
int body(){
  int result = E_OK;
  switch (token){
    case T_CLASS: //BODY --> CLASS
      token = getToken();
      if (!isok(token)) return LEX_ERROR;

      result = class();
      if (result != E_OK) return result;

      result = body()

    break;

    case T_END: //BODY --> epsilon
      //TODO check for main void run here!
      return E_OK;
    break;

    case default:
      result = SYNTAX_ERROR;
    break;
  }
  return result;
}

//PROGRAM --> BODY EOF
int program(){
  int result = E_OK;

  result = body();
  if (result != E_OK) return result;

  if (token != T_END) return E_SYN;

  return result;
}


int parse(){
  int result = E_OK;
  if ((data = newString()) == NULL) return E_INTERNAL;
  //malloc

  token = getToken();
  if (isok(token)) result = program();

  //free TODO
  return result;
}
