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

#include "precanal.h"


///////////////////////////////////////////////////////////
///prace se zasobnikem(dvousmerny linearni seznam)

void init_list(tList *l) //ok
{
    l->first=NULL;
    l->last=NULL;
    l->lastTerminal=NULL;
}

void insert_terminal_last(tList *l, int c) //ok
{
    ///pokud je terminal identifikator, tak zjistit jeho typ a ulozit ho jako cislo nebo string
    if(l->first==NULL)
    {
        tItem *tmp;
        tmp=malloc(sizeof(tItem));
        if(c==T_IDENT || c==T_C_IDENT)
        {
            tmp->c=T_NUMBER_I;///pridat z tabulky symbolu
        }
        else
        {
            tmp->c=c;
        }
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
    if(c==T_IDENT || c==T_C_IDENT)
    {
        tmp->c=T_NUMBER_I;//pridat z tabulky symbolu
    }
    else
    {
        tmp->c=c;
    }
    tmp->terminal=true;
    tmp->handle=false;
    tmp->next=NULL;
    tmp->prev=l->last;
    l->last->next=tmp;
    l->last=tmp;
    l->lastTerminal=tmp;
    }
}
/** handle slouzi jako vnoreni, co se bude jako prvni pocitat ve vyrazu*/
void insert_handle(tList *l) //ok
{
    if(l->last==l->lastTerminal)
    {
        tItem *tmp;
        tmp=malloc(sizeof(tItem));
        tmp->c=-1; //TODO
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
        tmp->c=-1; //TODO
        tmp->terminal=false;
        tmp->handle=true;
        tmp->next=l->lastTerminal->next;
        l->lastTerminal->next->prev=tmp;
        tmp->prev=l->lastTerminal;
        l->lastTerminal->next=tmp;
    }
}

/** testovani zda je handle na zasobniku, musi byt vzdy pokud probehne redukce*/
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

/**pokud ma byt ukoncovaci symbol prava zavorka, zkontroluje se jestli ma byt zakoncovaci, nebo jestli ma byt nejakou vnorenou casti vyrazu*/
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
/**ukazatel na nejvnorenejsi handle, od neho dal se bude provadet redukce*/
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
/** hledani posledniho terminalu, aby bylo mozne zjistit jake pravidlo z prec. tabulky se ma pouzit*/
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
/** vyjmuti operandu nebo operatoru pro posladni instrukce na spocitani vyrazu*/
tItem * cut_item(tList *l, int *typ)
{
    tItem *tmp=get_last_handle(l);

    tmp=tmp->next;

    if(tmp==NULL)
    {
        // nemelo by nastat, po vkladani handle by mel byt dalsi prvek na zasobniku
    }

    tItem *tmpReturn=tmp; //tmp se uvolni ze asobniku, tmpReturn se vrati dany operand/operator
    *typ=tmp->c;
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
/** samotne redukovani podvyrazu na jeden neterminal*/
void reduce (tList *l)
{
     ///prozatimni implementace bez pocitani hodnoty neterminalu, jenom testovani funkcnosti redukce
    tItem *tmp;
    tmp=get_last_handle(l);
    int typ[3];
    int i=0;
    while(tmp->next!=NULL)
    {
        ///z cut_item se budou brat operandy a operatory, vypocita se hodnota a vlozi se do neterminalu, ktery se vlozi na zasobnik po tom co se odstrani posledni handle
        cut_item(l,&typ[i]);
        i++;
    }

    bool s=false, d=false, in=false;
    int j;
    for(j=0;j<i;j++)
    {
        if(typ[j]==T_STRING_L)
        {
            s=true;
            break;
        }
        else if(typ[j]==T_NUMBER_D)
        {
            d=true;
        }
        else if(typ[j]==T_NUMBER_I)
        {
            in=true;
        }
    }

    if(s) tmp->c=T_STRING_L;
    else if(d) tmp->c=T_NUMBER_D;
        else if(in) tmp->c=T_NUMBER_I;
            else tmp->c=-1; //TODO


  ///zamena handle na pozdeji vypocitany neterminal

    tmp->handle=false;
    tmp->terminal=false;


}
/**kontrola semantiky (pokud je jeden z neterminalu string, muze se provest pouze + ->konkatenace)*/
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
/** syntakticka kontrola, zda je dany podvyraz vysledkem nejakeho pravidla*/
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
    /** pravidla maji za vysledek pouze 1 nebo 3 prvky*/
    if(tmp->next->next==NULL)
    {
        //existuje pravidlo s jednim operandem, nebo dvouma a jednim operatorem
        return 1;
    }
    /** pripad uz zredukovaneho vyrazu v zavorkach*/
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

/** indexy precedenci tabulky*/
int t_index[14]={T_PLUS,T_MINUS,T_MUL,T_SLASH,T_LBRACKET,T_RBRACKET,
                T_GREAT,T_LESS,T_GEQUAL,T_LEQUAL,T_EQUAL,T_EXCLAIM,T_IDENT,'$'}; //ok

/** pravidla pro analyzu v tabulce*/
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
/** zjisteni indexu daneho terminalu*/
int get_index(int c) //ok
{
    int i;

    if(c==T_C_IDENT || c==T_IDENT || c==T_NUMBER_I || c==T_NUMBER_D || c==T_STRING_L)
        return 12;

    for(i=0;i<14;i++)
    {
        if(t_index[i]==c)
            return i;
    }

    return -1;
    //pokud nenalezne- ve vyrazu se vyskytl nepovoleny token- syntakticka chyba
}

/** zjisteni co je posledni terminal na zasobniku a co je na vstupu*/
char rule(tList *l)
{
    int i=get_index(l->lastTerminal->c);
    int j=get_index(token->id);
    return prec_table[i][j];
}

//////////////////////////////////////////////////////////////////////////////
///algoritmus precedencni analyzy

int prec_anal(int until)
{
    tList *l;
    l=malloc(sizeof(tList));
    if(l==NULL)
    {
        return E_INTERNAL;
    }
    init_list(l);
    insert_terminal_last(l,'$'); //na spodek zasobniku se dava terminal $

    //token=token->next; //nacte se prvni vstup
    if(token->id==until) //expession nemuze byt prazdny
    {
        return E_SYN;
    }

    int end=until;
    int vratit=token->id; //timto prepsat posledni token z $ zpet na puvodni
    while(token->id!=end || l->lastTerminal->c!='$') //dokud neni na vstupu zakoncujici znak a na zasobniku je pouze jede terminal $
    {
        //kontrola posledniho znaku
        if(token->id==end)
            {
                if(token->id==T_RBRACKET)
                {
                    if(bracket_balance(l)==0)
                    {
                        end='$';
                        token->id='$';
                    }
                }
                else
                {
                    end='$';
                    token->id='$';
                }
            }
            else
            {
                //kontrola zda token muze byt ve vyrazu
                if(token->id==T_C_IDENT ||token->id==T_IDENT || (token->id>=T_NUMBER_I && token->id<=T_STRING_L ) ||
                   (token->id>=T_EQUAL && token->id<=T_SLASH ) ||(token->id>=T_LBRACKET && token->id<=T_RBRACKET) ||token->id==36 ) //36 ascii $
                    {}
                else
                    {
                    return E_SYN;
                    }

            }


        //jednotlive algoritmy pravidel u precedencni analyzy
        switch(rule(l))
        {
        case '=':
            insert_terminal_last(l,token->id);
            token=token->next;
            vratit=token->id;
            break;

        case '<':
            insert_handle(l);
            insert_terminal_last(l,token->id);
            token=token->next;
            vratit=token->id;
            break;

        case '>':  //pokud je handle na zasobniku a existuje pravidlo ze ktereho je vysledek za handlem
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
                        return E_TYP;  //semanticka chyba, nepovolede operace s retezcem
                    }

                }
                else //spatne zapsany vyraz
                {
                    return E_SYN;
                }

            }
            else //neni handle na zasobniku, zase spatne zapsany vyraz
            {
                return E_SYN;
            }

            break;

        default: //pokud je pravidlo ' ' taky spatne zapsany vyraz
           return E_SYN;
        }
    }
    token->id=vratit;
    return 0;
}
