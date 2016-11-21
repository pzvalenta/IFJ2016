#ifndef HEADER_MAIN
#define HEADER_MAIN

/*
• 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexé-
mu).
• 2 - chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu).
• 3 - sémantická chyba v programu – nedefinovaná tˇrída/funkce/promenná, pokus o re- ˇ
definici tˇrídy/funkce/promenné, atd. ˇ
• 4 - sémantická chyba typové kompatibility v aritmetických, ˇretezcových a rela ˇ cních ˇ
výrazech, pˇríp. špatný pocet ˇ ci typ parametr ˚u u volání funkce. ˇ
• 6 - ostatní sémantické chyby.
• 7 - behová chyba p ˇ ˇri nacítání ˇ císelné hodnoty ze vstupu. ˇ
• 8 - behová chyba p ˇ ˇri práci s neinicializovanou promennou. ˇ
• 9 - behová chyba d ˇ elení nulou. ˇ
• 10 - ostatní behové chyby. ˇ
• 99 - interní chyba interpretu tj. neovlivnená vstupním programem (nap ˇ ˇr. chyba alokace
pameti, chyba p ˇ ˇri otvírání souboru s ˇrídicím programem, špatné parametry
pˇríkazové ˇrádky atd.).
*/

#define E_OK    0
#define E_LEX   1
#define E_SYM   2
#define E_DEF   3
#define E_TYP   4
#define E_SEM   6
#define E_INPT  7
#define E_INIT  8
#define E_ZERO  9
#define E_OTHR  10
#define E_INTERNAL  99

#include "scanner.h"
#include "parser.h"
#include "ial.h"
#include "ilist.h"

#endif
