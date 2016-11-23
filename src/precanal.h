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
///includnout ostatni soubory

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

void init_list(tList *l);
void insert_terminal_last(tList *l, char c);
void insert_handle(tList *l);
bool is_handle(tList *l);
int bracket_balance(tList *l);
tItem * get_last_handle(tList *l);
void find_last_terminal(tList *l);
tItem * cut_item(tList *l);
void reduce (tList *l);
int sem_correct (tList *l);
int is_rule (tList*l);
int get_index(char c);
char rule(tList *l);
int prec_anal(char until);

#endif // PRECANAL_H_INCLUDED
