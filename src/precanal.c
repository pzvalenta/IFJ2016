/** Prekladac jazyka IFJ16
 *  Projekt do predmetu IFJ a IAL
 *  VUT FIT Brno, 2016
 *
 *  Tym 051, varianta a/2/I
 *  Autori:
 *      Petr Valenta
 *      Eliska Kadlecova
 *      Daniel Doubek
 *      Martin Kovarik
 *      Petr Jares
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
///include s ostatnima

char token;

typedef struct item{
    char c;             //ID terminalu
    ///string value  //pokud bude terminal identifikator, int, float, string prida se hodnota
    bool terminal;      //pokud je terminal-> TRUE
    bool handle;        //pokud je to handle -> TRUE
    struct item *next;  //ukazatel na dalsi
    struct item *prev;  //ukazatel na predchozi
}tItem;

typedef struct {
    tItem *first;
    tItem *last;
    tItem *lastTerminal;
}tList;

///////////////////////////////////////////////////////////
///prace se zasobnikem(dvousmerny linearni seznam)

void init_list(tList *l) //ok
{
    l->first=NULL;
    l->last=NULL;
    l->lastTerminal=NULL;
}

void insert_terminal_last(tList *l, char c) //ok
{
    ///pokud je terminal identifikator, tak zjistit jeho typ a ulozit ho jako cislo nebo string
    if(l->first==NULL)
    {
        tItem *tmp;
        tmp=malloc(sizeof(tItem));
        tmp->c=c;
        tmp->terminal=true;
        tmp->handle=false;
        tmp->prev=NULL;
        tmp->next=NULL;
        l->first=tmp;
        l->last=tmp;
        l->lastTerminal=tmp;
    }
    else
    {
    tItem *tmp;
    tmp=malloc(sizeof(tItem));
    tmp->c=c;
    tmp->terminal=true;
    tmp->handle=false;
    tmp->next=NULL;
    tmp->prev=l->last;
    l->last->next=tmp;
    l->last=tmp;
    l->lastTerminal=tmp;
    }
}

void insert_handle(tList *l) //ok
{
    if(l->last==l->lastTerminal)
    {
        tItem *tmp;
        tmp=malloc(sizeof(tItem));
        tmp->c=NULL;
        tmp->terminal=false;
        tmp->handle=true;
        tmp->next=NULL;
        tmp->prev=l->last;
        l->last->next=tmp;
        l->last=tmp;
    }
    else
    {
        tItem *tmp;
        tmp=malloc(sizeof(tItem));
        tmp->c=NULL;
        tmp->terminal=false;
        tmp->handle=true;
        tmp->next=l->lastTerminal->next;
        l->lastTerminal->next->prev=tmp;
        tmp->prev=l->lastTerminal;
        l->lastTerminal->next=tmp;
    }
}


bool is_handle(tList *l) //ok
{
    tItem *tmp=l->last;

    while(tmp!=NULL)
    {
        if(tmp->handle==true)
            return true;

        tmp=tmp->prev;
    }

    return false;
}


int bracket_balance(tList *l)
{
    int i=0;
    tItem *tmp=l->first;

    while(tmp!=NULL)
    {
        if(tmp->c==T_LBRACKET)
            i++;
        if(tmp->c==T_RBRACKET)
            i--;

        tmp=tmp->next;
    }

    return i;
}

///////////////////////////////////////////////////
///redukce

tItem * get_last_handle(tList *l)
{
    tItem *tmp=l->last;

    while(tmp->handle==false)
    {
        tmp=tmp->prev;
    }
    if(tmp==NULL)
    {
        //nemelo by nastat, tato funkce bude zavolana v pripade ze je handle v zasobniku
    }
    return tmp;
}

void find_last_terminal(tList *l)
{
    tItem *tmp=l->last;
    while(tmp->terminal==false)
    {
        tmp=tmp->prev;
    }
    l->lastTerminal=tmp;
    //vzdy by melo najit aspon terminal $

}

tItem * cut_item(tList *l)
{
    tItem *tmp=get_last_handle(l);

    tmp=tmp->next;

    if(tmp==NULL)
    {
        // nemelo by nastat, po vkladani handle by mel byt dalsi prvek na zasobniku
    }

    tItem *tmpReturn=tmp;
    if(tmp==l->last)
    {
        l->last=l->last->prev;
        l->last->next=NULL;

            find_last_terminal(l);

        free(tmp);
        return tmpReturn;
    }
    else
    {
        tmp->prev->next=tmp->next;
        tmp->next->prev=tmp->prev;

            find_last_terminal(l);

        free(tmp);
        return tmpReturn;
    }

}

void reduce (tList *l)
{
    ///prozatimni implementace bez pocitani hodnoty neterminalu, jenom testovani funkcnosti redukce
    tItem *tmp;
    tmp=get_last_handle(l);
    while(tmp->next!=NULL)
    {
        ///z cut_item se budou brat operandy a operatory, vypocita se hodnota a vlozi se do neterminalu, ktery se vlozi na zasobnik po tom co se odstrani posledni handle
        cut_item(l);
    }

    ///zamena handle na pozdeji vypocitany neterminal
  //  tmp->c=T_STRING_L;
  //  tmp->c=T_NUMBER_D;
    tmp->handle=false;
    tmp->terminal=false;


}

int sem_correct (tList *l)
{
    tItem *tmp=get_last_handle(l);
    tmp=tmp->next;

    if(tmp->terminal==false && tmp->next->next->terminal==false)
    {
        if(tmp->c ==T_STRING_L || tmp->next->next->c==T_STRING_L)
        {
            if(tmp->next->c==T_PLUS)
            {
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

int is_rule (tList*l)
{
    tItem *tmp=get_last_handle(l);
    tmp=tmp->next;

    //pokud se redukuje jediny prvek, musi to byt operand
    if(tmp->next==NULL)
    {
        //redukce samotneho terminalu
        switch(tmp->c)
        {
            case T_IDENT: ///oddela se, identifikator se rouvnou bude ukladat jako cislo nebo string
            case T_NUMBER_I:
            case T_NUMBER_D:
            case T_STRING_L:
                    return 0;
                    break;
            default:
                    return 1;
        }

    }

    if(tmp->next->next==NULL)
    {
        //existuje pravidlo s jednim operandem, nebo dvouma a jednim operatorem
        return 1;
    }

    if(tmp->c==T_LBRACKET && tmp->next->terminal==false && tmp->next->next->c==T_RBRACKET)
    {
        //neterminal v zavorce
        return 0;
    }

    if(tmp->terminal==false && tmp->next->next->terminal==false)
    {
        switch(tmp->next->c)
        {
            case T_EQUAL:
            case T_PLUS:
            case T_GREAT:
            case T_GEQUAL:
            case T_MINUS:
            case T_LESS:
            case T_LEQUAL:
            case T_MUL:
            case T_EXCLAIM:
            case T_SLASH:
                return 0;
            default:
                return 1;
        }

    }

    return 1;
}

//////////////////////////////////////////////////////////
///prace s precedenci tabulkou


char index[14]={T_PLUS,T_MINUS,T_MUL,T_SLASH,T_LBRACKET,T_RBRACKET,
                T_GREAT,T_LESS,T_GEQUAL,T_LEQUAL,T_EQUAL,T_EXCLAIM,T_IDENT,'$'}; //ok

char prec_table[14][14]={
    {'>','>','<','<','<','>','>','>','>','>','>','>','<','>'},
    {'>','>','<','<','<','>','>','>','>','>','>','>','<','>'},
    {'>','>','>','>','<','>','>','>','>','>','>','>','<','>'},
    {'>','>','>','>','<','>','>','>','>','>','>','>','<','>'},
    {'<','<','<','<','<','=','<','<','<','<','>','>','<',' '},
    {'>','>','>','>',' ','>','>','>','>','>','>','>',' ','>'},
    {'<','<','<','<','<','>',' ',' ',' ',' ',' ',' ','<','>'},
    {'<','<','<','<','<','>',' ',' ',' ',' ',' ',' ','<','>'},
    {'<','<','<','<','<','>',' ',' ',' ',' ',' ',' ','<','>'},
    {'<','<','<','<','<','>',' ',' ',' ',' ',' ',' ','<','>'},
    {'<','<','<','<','<','>',' ',' ',' ',' ',' ',' ','<','>'},
    {'<','<','<','<','<','>',' ',' ',' ',' ',' ',' ','<','>'},
    {'>','>','>','>',' ','>','>','>','>','>','>','>',' ','>'},
    {'<','<','<','<','<',' ','<','<','<','<','<','<','<',' '},

};

int get_index(char c) //ok
{
    int i;

    if(c==T_IDENT || c==T_NUMBER_I || c==T_NUMBER_D || c==T_STRING_L)
        return 12;

    for(i=0;i<14;i++)
    {
        if(index[i]==c)
            return i;
    }

    //pokud nenalezne- ve vyrazu se vyskytl nepovoleny token- syntakticka chyba
}


char rule(tList *l)
{
    int i=get_index(l->lastTerminal->c);
    int j=get_index(token);
    return prec_table[i][j];
}

//////////////////////////////////////////////////////////////////////////////
///algoritmus precedencni analyzy

int prec_anal(char until)
{
    tList *l;
    l=malloc(sizeof(tList));
    init_list(l);
    insert_terminal_last(l,'$');

    print_list(l);
    token=getToken();

    char end=until;
    while(token!=end || l->lastTerminal->c!='$')
    {
        //
        if(token==end)
            {
                if(token==T_RBRACKET)
                {
                    if(bracket_balance(l)==0)
                    {
                        end='$';
                        token='$';
                    }
                }
                else
                {
                    end='$';
                    token='$';
                }
            }
            else
            {
                //kontrola zda token muze byt ve vyrazu
                if(token==11 || (token>40 && token<44 ) || (token>51 && token<66 ) ||(token>80 && token<83) ||token==36 )
                    {}
                else
                    {
                    return E_SYN;
                    }

            }



        switch(rule(l))
        {
        case '=':
            insert_terminal_last(l,token);
            token=getToken();
            break;

        case '<':
            insert_handle(l);
            insert_terminal_last(l,token);
            token=getToken();
            break;

        case '>':
            if(is_handle(l))
            {
                if(is_rule(l)==0)
                {
                    if(sem_correct(l)==0)
                    {
                        reduce(l);
                    }
                    else
                    {
                        return E_SEM;
                    }

                }
                else
                {
                    return E_SYN;
                }

            }
            else
            {
                return E_SYN;
            }

            break;

        default:
           return E_SYN;
        }
    }
    return 0;
}
