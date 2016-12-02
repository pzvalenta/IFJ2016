
//TODO list:
//TODO nahradit token = getToken() + error check nejakym onelinerem
// if (!isok(token = getToken()))
//TODO class Main { static void run() {...} }    --- check
//TODO pridat vestavene funkce
#include "parser.h"
#include "precanal.h"

struct tListItem *token = NULL;    // globalni promena, ukazatel na momentalni token v tokenlistu
struct classNode *CTRoot = NULL; //koren globalni tabulky trid
struct varNode *GVRoot = NULL; //koren globalni tabulky promennych
struct funNode *FTRoot = NULL; // koren glob tabulky funkci

struct classNode *CurrentClass = NULL;
struct funNode *CurrentMethod = NULL;

int createCompleteIdent();
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



// void createCompleteIdent(){
//   String *tmp = newString();
//   for(int i = 0; i < CurrentClass->name->data->len){
//     appendChar(tmp, CurrentClass->data->data[i]);
//   }
//
//   appendChar(tmp, '.');
//
//   for(int i = 0; i < token->data->len){
//     appendChar(tmp, token->data->data[i]);
//   }
//
//   destroyString(token->data);
//   token->data = tmp;
// }

int ifjfind(){
        fprintf(stderr,"entering ifjfind()\n");
        dprint(token);
        int result = E_OK;

        //TODO placeholder
        while (token->id != T_RBRACKET && token->id != T_END) {
                token = token->next;
                dprint(token);
        }
        token = token->next;


        return result;
}


int ifjprint(){
        fprintf(stderr,"entering ifjprint()\n");
        dprint(token);
        int result = E_OK;

        //TODO placeholder
        while (token->id != T_RBRACKET && token->id != T_END) {
                token = token->next;
                dprint(token);
        }
        token = token->next;
        dprint(token);


        return result;
}

int assign_rule(){
        fprintf(stderr,"entering assign_rule()\n");
        int result = E_OK;
        dprint(token);

        // momentalne je v tokenu id
        //TODO vytvoreni polozky v symtable

        token = token->next; // id = EXPRESSION ;
        if (token->id != T_ADD) return E_SYN;
        token = token->next;

        if (strcmp("ifj16.print", token->data->data) == 0) {
                result = ifjprint();
                token = token->next;
                return result;
        }
        if (strcmp("ifj16.find", token->data->data) == 0) {
                result = ifjfind();
                token = token->next;
                dprint(token);
                return result;
        }



        result = prec_anal(T_SEMICLN);
        if (result != E_OK) return result;

        token = token->next;
        return result;
}




//STATEMENT --> static TYPE id ;
//STATEMENT --> static TYPE id = EXPRESSION ;

int static_rule(){
        fprintf(stderr,"entering static_rule()\n");
        dprint(token);
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
        if (token->id == T_SEMICLN) {
                token = token->next;
                return result;
        }

        //TYPE id = EXPRESSION ;

        if (token->id != T_ADD) return E_SYN;

        result = prec_anal(T_SEMICLN);
        if (result != E_OK) return result;

        token = token->next;
        return result;
}


//STATEMENT --> TYPE id ;
//STATEMENT --> TYPE id = EXPRESSION ;
int declaration_rule(){
        fprintf(stderr,"entering declaration_rule()\n");
        int result = E_OK;
        dprint(token);

        // momentalne je v tokenu type
        //int type = token->id; TODO

        token = token->next;
        if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;
        //TODO vytvoreni polozky v symtable

        token = token->next;
        if (token->id == T_SEMICLN) {
                token = token->next;
                return result;
        }

        //TYPE id = EXPRESSION ;

        if (token->id != T_ADD) return E_SYN;

        result = prec_anal(T_SEMICLN);
        if (result != E_OK) return result;

        token = token->next;
        return result;
}

int return_rule(){
        fprintf(stderr,"entering return_rule()\n");
        dprint(token);
        int result = E_OK;
        //momentalni token by mel byt return

        token = token->next;
        result = prec_anal(T_SEMICLN);
        if (result != E_OK) return result;

        token = token->next;
        return result;
}


int func_call_rule(){
        fprintf(stderr,"entering func_call_rule()\n");
        dprint(token);
        int result = E_OK;

        //momentalni token je ID

        //TODO zknotrolovat symtable

        token = token->next;
        if (token->id != T_ADD) return E_SYN;

        token = token->next;
        if (token->id != T_IDENT && token->id != T_C_IDENT ) return E_SYN;
        //TODO zknotrolovat symtable
        //TODO vygenerovat volani fce

        token = token->next;
        result = param(); //generace parametru
        if(result != E_OK) return result;
        //token by mel byt )

        token = token->next;
        if (token->id != T_SEMICLN) return E_SYN;

        token = token->next;
        return result;
}


int void_func_call_rule(){
        fprintf(stderr,"entering void_func_call_rule()\n");
        dprint(token);
        int result = E_OK;

        //momentalni token je ID


        if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;
        //TODO zknotrolovat symtable
        //TODO vygenerovat volani fce
        if (strcmp("ifj16.print", token->data->data) == 0) {
                result = ifjprint();
                token = token->next;
                return result;
        }
        if (strcmp("ifj16.find", token->data->data) == 0) {
                result = ifjfind();
                token = token->next;
                return result;
        }



        token = token->next;
        if (token->id != T_LBRACKET) return E_SYN;


        token = token->next;
        result = param(); //generace parametru

        if(result != E_OK) return result;
        //token by mel byt )

        token = token->next;
        if (token->id != T_SEMICLN) return E_SYN;

        dprint(token);
        token = token->next;
        return result;
}


// PARAM --> epsilon
// PARAM --> id PARAM
// PARAM --> , id PARAM
int param(){
        fprintf(stderr,"entering param()\n");
        dprint(token);
        int result = E_OK;

        if (token->id == T_RBRACKET) return result;  //epsilon


        if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;  // id
        //TODO zpracovani

        token = token->next;
        if(token->id == T_COMMA) {           // ,
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
        fprintf(stderr,"entering mparam()\n");
        dprint(token);
        int result = E_OK;

        if (token->id == T_RBRACKET) return result;  //epsilon

        // TYPE
        if (token->id == T_INT || token->id == T_DOUBLE || token->id == T_STRING) {
                token = token->next;
                if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;  // id
                //TODO zpracovani

                token = token->next;
                if(token->id == T_COMMA) {     // ,
                        token = token->next;
                        return mparam();
                }
                if (token->id == T_RBRACKET) return E_OK;
                else return E_SYN;
        }
        else return E_SYN;
}

// STATEMENT --> while ( EXPRESSION ) { STATEMENT_LIST }
int while_rule(){
        fprintf(stderr,"entering while_rule()\n");
        dprint(token);
        int result = E_OK;
        //momentalni token je urcite while         // while
        if (token->id != T_WHILE) return E_SYN;

        token = token->next;
        if(token->id != T_LBRACKET) return E_SYN;  // (

        token = token->next;
        result = prec_anal(T_SEMICLN);
        if (result != E_OK) return result;

        //nacteny token by mel byt )
        if(token->id != T_RBRACKET) return E_SYN;  // )

        token = token->next;
        if(token->id != T_LCBRACKET) return E_SYN;  // {

        token = token->next;
        result = statement_list();           // STATEMENT_LIST
        if(result != E_OK) return result;

        //nacteny token by mel byt }
        if(token->id != T_RCBRACKET) return E_SYN;  // }
        token = token->next;

        return result;
}


// STATEMENT --> if ( EXPRESSION ) { STATEMENT_LIST } else { STATEMENT_LIST }
int if_rule(){
        fprintf(stderr,"entering if_rule()\n");
        dprint(token);
        int result = E_OK;
        //momentalni token je urcite if            // if
        if (token->id != T_IF) return E_SYN;

        token = token->next;
        if(token->id != T_LBRACKET) return E_SYN;  // (

        token = token->next;
        result = prec_anal(T_SEMICLN);
        if (result != E_OK) return result;

        //nacteny token by mel byt )
        if(token->id != T_RBRACKET) return E_SYN;  // )

        token = token->next;
        if(token->id != T_LCBRACKET) return E_SYN;  // {

        token = token->next;
        result = statement_list();           // STATEMENT_LIST
        if(result != E_OK) return result;

        //nacteny token by mel byt }
        if(token->id != T_RCBRACKET) return E_SYN;  // }

        token = token->next;
        if(token->id != T_ELSE) return E_SYN;  // else

        token = token->next;
        if(token->id != T_LCBRACKET) return E_SYN;  // {

        token = token->next;
        result = statement_list();           // STATEMENT_LIST
        if(result != E_OK) return result;

        //nacteny token by mel byt }
        if(token->id != T_RCBRACKET) return E_SYN;  // }

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
        fprintf(stderr,"entering statement()\n");
        dprint(token);
        int result = E_OK;
        switch (token->id) {
        // STATEMENT --> id = id (PARAM) ;
        // STATEMENT --> id (PARAM) ;
        // STATEMENT --> id = EXPRESSION ;
        case T_IDENT: // co EXPRESSION --> id (PARAM)
        case T_C_IDENT:
                // // TODO nacist id, vyhledat v symtable
                // // vlozit do symtable jestli tam neni
                if (token->next->id == T_ADD) {
                        if (token->next->next->id == T_IDENT && token->next->next->next->id == T_LBRACKET)
                                return func_call_rule();  // id = id (PARAM) ;
                        else // id = EXPRESSION ; TODO
                                return assign_rule();


                }
                else if (token->next->id == T_LBRACKET) {
                        //       id (PARAM) ;
                        result = void_func_call_rule();
                        //token = token->next;
                        return result;
                }

                return result;
                break;


        // STATEMENT --> return EXPRESSION ; TODO
        case T_RETURN:
                result = return_rule();
                //placeholder
                while(token->id != T_SEMICLN && token->id != T_END) {
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
        dprint(token);
        fprintf(stderr,"entering statement_list()\n");

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
                fprintf(stderr,"going from statement_list() to statement()\n");
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

        case T_STATIC: // METHOD / STATEMENT ?
                if (token->next->next->next->id == T_LBRACKET) { //TODO errorcheck
                        fprintf(stderr,"leaving statement_list() - found method\n");
                        return E_OK;
                }
                else {
                        fprintf(stderr,"going from statement_list() to statement()\n");
                        result = statement();
                        if (result != E_OK) return result;
                        return statement_list();
                }
                break;



        default:
                fprintf(stderr,"leaving statement_list()\n");
                return E_OK;
        }
}

//METHOD --> static TYPE id ( PARAM ) { STATEMENT_LIST } // fce jsou vždy static
int method(){
        int result = E_OK;
        dprint(token);
        fprintf(stderr,"entering method()\n");


        //momentalni token je urcite static         // static
        if (token->id != T_STATIC) return E_SYN;

        token = token->next;
        if (token->id != T_INT && token->id != T_DOUBLE && token->id != T_STRING && token->id != T_VOID)
        return E_SYN;                 // TYPE

        token = token->next;
        if (token->id != T_IDENT && token->id != T_C_IDENT) return E_SYN;  // id

        result = newFunction();
        if (result != E_OK) return result;

        token = token->next;
        if (token->id != T_LBRACKET) return E_SYN;  // (

        token = token->next;
        fprintf(stderr,"going from method() to mparam()\n");
        result = mparam();                     // PARAM
        if (result != E_OK) return result;

        //nacteny token z prec. analyzy by mel byt  // )
        if (token->id != T_RBRACKET) return E_SYN;

        token = token->next;
        if (token->id != T_LCBRACKET) return E_SYN;  // {

        token = token->next;
        fprintf(stderr,"going from method() to statement_list()\n");
        result = statement_list();            // STATEMENT_LIST

        // token nacteny statement listem by mel byt }
        if (token->id != T_RCBRACKET) return E_SYN;  // }
        token = token->next;

        return result;
}

//CLASS_BODY --> epsilon | STATEMENT_LIST CLASS_BODY | METHOD CLASS_BODY
int class_body(){
        int result = E_OK;
        fprintf(stderr,"entering class_body()\n");
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
                fprintf(stderr,"going from class_body() to statement_list()\n");
                result = statement_list();
                if (result != E_OK) return result;

                return class_body();
                break;

        case T_STATIC: // METHOD / STATEMENT ?
                if (token->next->next->next->id == T_LBRACKET) { //TODO errorcheck
                        fprintf(stderr,"going from class_body() to method()\n");
                        result = method();
                        if (result != E_OK) return result;
                        return class_body();
                }
                else {
                        fprintf(stderr,"1going from class_body() to statement_list()\n");
                        result = statement_list();
                        if (result != E_OK) return result;

                        return class_body();
                }
                break;


        case T_RCBRACKET: //nactena }, konec class_body
                fprintf(stderr,"leaving class_body()\n");
                return E_OK;
                break;

        default: return E_SYN;
        }
}

///////////^^^^^^^^^^TODO TODO TODO TODO^^^^^^^^^^^

//CLASS --> class id { CLASS_BODY }
int class(){
        int result = E_OK;
        fprintf(stderr,"entering class()\n");
        dprint(token);

        result = newClass();
        if (result != E_OK) return result;

        token = token->next;
        if (token->id != T_LCBRACKET) return E_SYN;


        token = token->next;
        fprintf(stderr,"going from class() to classbody()\n");
        result = class_body();
        if (result != E_OK) return result;

        // token nacteny v class_body() by mel byt

        if (token->id != T_RCBRACKET) return E_SYN;

        fprintf(stderr,"leaving class()\n");

        return result;
}

//BODY --> epsilon | CLASS BODY
int body(){
        int result = E_OK;
        fprintf(stderr,"entering body()\n");
        dprint(token);

        switch (token->id) {
        case T_CLASS: //BODY --> CLASS
                token = token->next;
                fprintf(stderr,"going from body() to class()\n");
                result = class();
                if (result != E_OK) return result;
                token = token->next;
                result = body();
                break;

        case T_END: //BODY --> epsilon
                fprintf(stderr,"leaving body()\n");
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
        fprintf(stderr,"entering program()\n");
        dprint(token);


        //check for class
        fprintf(stderr,"going from program() to body()\n");
        result = body();
        if (result != E_OK) return result;

        fprintf(stderr,"back in program(), expecting EOF\n");
        if (token->id != T_END) return E_SYN;

        return result;
}


int parse(struct tListItem *head){
        int result = E_OK;
        fprintf(stderr,"entering parse()\n");
        token = head;
        dprint(token); //DEBUG
        result = program();

        return result;
}
