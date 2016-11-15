//predpokladam zmenu vystupu scanneru na pouhe ID + data pres globalni promennou

char token;

// vraci 0 kdyz je token ERROR
char isok(char token){
  if (token > 100)
    return 0;
  else
    return 1;
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
  void * data; // takto budeme predavat data
  //malloc

  token = getToken();
  if (isok(token)) result = program();

  //free
  return result;
}
