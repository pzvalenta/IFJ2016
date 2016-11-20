//predpokladam zmenu vystupu scanneru na pouhe ID + data pres globalni promennou
// TODO zapomnel jsem na - class Main { static void run() {...} }

//TODO list:
//TODO nahradit token = getToken() + error check nejakym onelinerem
//TODO getToken(&data) by mel vracet char TOKEN_ID a pres odkaz data jako string(i v pripade integeru atd.)
//TODO predelat scanner a parser, tak aby scanner nepouzival tabulku symbolu
//TODO class Main { static void run() {...} }


char token;    // globalni promena, do ktere se bude vkladat navratova hodnota z getToken
String *data;  // globalni promenna, ve ktere budou ulozena data tokenu

// vraci 0 kdyz je token ERROR
char isok(char token){
  if (token > 100)
    return 0;
  else
    return 1;
}

//CLASS_BODY --> epsilon | STATEMENT_LIST CLASS_BODY | METHOD CLASS_BODY
char class_body(){
  char result;
  switch (token){
    case STATEMENT:
    break;

    case METHOD:
    break;

    case T_RCBRACKET: //nactena }, konec class_body
      return E_OK;
    break;

    default: return E_SYN;
  }
}

//CLASS --> class id { CLASS_BODY }
char class(){
  char result;
  if (token != T_IDENT) return E_SYN;
  else {
      /// vytvorit novou node v globalni tabulce symbolu
      /// error check
  }

  token = getToken();
  if (token != T_LCBRACKET) return E_SYN;

  token = getToken(); // error check
  result = class_body();
  if (result != E_OK) return result;

  // token nacteny class_body() by mel byt
  if (token != T_RCBRACKET) return E_SYN;


}

//BODY --> epsilon | STATEMENT BODY | METHOD BODY | CLASS BODY
char body(){
  char result;
  switch (token){
    //BODY --> STATEMENT BODY // petr j
    case T_IDENT:
    case T_RETURN:
    case T_IF:
    case T_WHILE:

    break;

    //BODY --> CLASS BODY // petr v
    case T_CLASS:
      token = getToken();
      if (!isok(token)) return LEX_ERROR;
      result = class();
      if (result != E_OK)
    break;

    //BODY --> METHOD BODY // martin
    case T_INT:
    case T_STRING:
    case T_VOID:
    case T_STATIC:

    break;

    //TODO BODY --> epsilon

    case default:
      result = SYNTAX_ERROR;
    break;
  }
  return result;
}

//PROGRAM --> BODY EOF
char program(){
  char result;

  switch (token){
    case T_IDENT:
    case T_RETURN:
    case T_IF:
    case T_WHILE:

    case T_CLASS:

    case T_INT:
    case T_STRING:
    case T_VOID:
    case T_STATIC:

      result = body();       // BODY
      if (result != E_OK) return result;


      token = getToken();    //EOF
      if (token != T_END) return E_SYN;

      return E_OK;
    break;

    case default:
      result = E_SYN;
    break;
  }
    return result;
}


char parse(){
  char result;
  if ((data = newString()) == NULL) return E_ALL;
  //malloc



  token = getToken();
  if (isok(token)) result = program();

  //free
  return result;
}
