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
#ifndef PRECANAL_H_INCLUDED
#define PRECANAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//potrebne hlavickove soubory
#include "scanner.h"
#include "main.h"
#include "parser.h"

extern int SECOND_RUN;

typedef struct item{
    int c;             //ID terminalu
    //tady bude offset zasobniku interpetu kde bude hodnota
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

void init_list(tList *l);
void dispose_list(tList *l);
int insert_terminal_last(tList *l, int c);
int insert_handle(tList *l);
bool is_handle(tList *l);
int bracket_balance(tList *l);
tItem * get_last_handle(tList *l);
void find_last_terminal(tList *l);
tItem * cut_item(tList *l, int *typ);
void reduce (tList *l);
int sem_correct (tList *l);
int is_rule (tList*l);
int get_index(int c);
char rule(tList *l);
int prec_anal(int until);
int expr(int until);

#endif // PRECANAL_H_INCLUDED
