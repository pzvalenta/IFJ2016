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

#include "str.h"

#define START       		255 // pocatecni nastaveni tokenu (id)

#define T_IDENT          11
#define T_KEY            20

#define T_NUMBER_I       41
#define T_NUMBER_D       42
#define T_STRING         43


#define T_END             1

#define T_ADD            51
#define T_EQUAL          52
#define T_PLUS           53
#define T_GREAT          55
#define T_GEQUAL         56
#define T_MINUS          57
#define T_LESS           59
#define T_LEQUAL         60
#define T_MUL            61
#define T_EXCLAIM        64
#define T_SLASH          65

#define T_LBRACKET      101
#define T_RBRACKET      102
#define T_LCBRACKET     103
#define T_RCBRACKET     104
#define T_LSBRACKET     105
#define T_RSBRACKET     106
#define T_SEMICLN       107
#define T_COMMA         108
#define T_DOT           109

#endif // SCANNER
