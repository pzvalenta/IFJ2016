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

#ifndef SCANNER
#define SCANNER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "str.h"
#include "token.h"
#include "ial.h"


#define START       		 255 // pocatecni nastaveni tokenu (id)

#define T_IDENT          11
#define T_C_IDENT        12

//klicova slova
#define T_KEY            20
#define T_BOOL           21 //rozsireni
#define T_BREAK          22
#define T_CLASS          23
#define T_CONTINUE       24 //rozsireni
#define T_DO             25
#define T_DOUBLE         26
#define T_ELSE           27
#define T_FALSE          28 //rozsireni
#define T_FOR            29 //rozsireni
#define T_IF             30
#define T_INT            31
#define T_RETURN         32
#define T_STRING         33
#define T_STATIC         34 //rozsireni ?
#define T_TRUE           35 //rozsireni
#define T_VOID           36
#define T_WHILE          37



#define T_NUMBER_I       41 //celociselny literal
#define T_NUMBER_D       42 //desetinny literal
#define T_STRING_L       43 //retezcovy literal


#define T_END            10

#define T_ADD            51 // =
#define T_EQUAL          52 // ==
#define T_PLUS           53 // +
#define T_GREAT          55 // >
#define T_GEQUAL         56 // >=
#define T_MINUS          57 // -
#define T_LESS           59 // <
#define T_LEQUAL         60 // <=
#define T_MUL            61 // *
#define T_EXCLAIM        64 // !=
#define T_SLASH          65 // /

#define T_LBRACKET      81 // (
#define T_RBRACKET      82 // )
#define T_LCBRACKET     83 // {
#define T_RCBRACKET     84 // }
#define T_LSBRACKET     85 // [
#define T_RSBRACKET     86 // ]
#define T_SEMICLN       87 // ;
#define T_COMMA         88 // ,
#define T_DOT           89 // .




int getToken();
void set_data(String *addr);
void set_file(FILE *source);

#endif // SCANNER
