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

#define START       		255 // pocatecni nastaveni tokenu (id)

#define T_IDENT         011
#define T_KEY           020

#define T_NUMBER_I      041
#define T_NUMBER_D      042
#define T_STRING        043


#define T_END           001

#define T_ADD           051
#define T_EQUAL         052
#define T_PLUS          053
#define T_GREAT         055
#define T_GEQUAL        056
#define T_MINUS         057
#define T_LESS          059
#define T_LEQUAL        060
#define T_MUL           061
#define T_EXCLAIM       064
#define T_SLASH         065

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
