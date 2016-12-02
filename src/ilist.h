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
 #include "main.h"

 // typy instrukci
 #define I_STOP         0     //stop

 #define I_ADD          1     //scitani
/* list_insert_last(*List instrukci, I_ADD, scitanec, scitanec, vysledek)*/
 #define I_SUB          2     //odcitani
/* list_insert_last(*List instrukci, I_SUB, mensenec, mensitel, vysledek)*/
 #define I_MUL          3     //nasobeni
/* list_insert_last(*List instrukci, I_MUL, cinitel, cinitel, vysledek)*/
 #define I_DIV          4     //deleni
/* list_insert_last(*List instrukci, I_DIV, delenec, delitel, vysledek)*/

 #define I_GREAT        5     //vetsi nez >
 /* list_insert_last(*List instrukci, I_GREAT, 1. porovnavany, 2. porovnavany, vysledek)*/
 #define I_LESS         6     //mensi nez <
 /* list_insert_last(*List instrukci, I_LESS, 1. porovnavany, 2. porovnavany, vysledek)*/
 #define I_GREQ         7     //vetsirovno >=
 /* list_insert_last(*List instrukci, I_GREQ, 1. porovnavany, 2. porovnavany, vysledek)*/
 #define I_LESEQ        8     //mensirovno <=
 /* list_insert_last(*List instrukci, I_LESEQ, 1. porovnavany, 2. porovnavany, vysledek)*/
 #define I_EQUAL        9     //rovna se ==
 /* list_insert_last(*List instrukci, I_EQUAL, 1. porovnavany, 2. porovnavany, vysledek)*/
 #define I_NEQUAL       10    //nerovna se !=
/* list_insert_last(*List instrukci, I_NEQUAL, 1. porovnavany, 2. porovnavany, vysledek)*/

 #define I_GOTO         11    //skok
 /* list_insert_last(*List instrukci, I_GOTO,??,adresa kam skocit, )*/
 #define I_IFGOTO       12    //podmineny skok
 /* list_insert_last(*List instrukci, I_IFGOTO, 1/0 = skok/neskok, adresa kam skocit, )*/
 #define I_PUSH         13    //push
/* list_insert_last(*List instrukci, I_PUSH, co se pushuje, , )*/
 #define I_POP          14    //pop
/* list_insert_last(*List instrukci, I_POP, co se popuje, , )*/
 #define I_CMP_STR      15    //porovnavani sringu
/* list_insert_last(*List instrukci, I_CMP_STR, prvni string, druhy string, vysledek)*/
 #define I_MOV          16    //presouvani z adresy 1 - source do adresy 3 - dest
/* list_insert_last(*List instrukci, I_MOV, source, , destination)*/




 // #define I_FIND         9     //find
 // #define I_INC          10    //inkrementace
 // #define I_DEC          11    //dekrementace
 // #define I_NOT          12    //not
 // #define I_IFGOTO       13    //podmineny skok !

 // input
 // read (3 ruzne) (zatim vynechat)
 // print

 #define I_LABEL        17    //navesti



typedef struct{
  int Inst_type;     //typ instrukce
  void *addr1;       //operator 1
  void *addr2;       //operator 2
  void *addr3;       //vysledek
} tInstr;

typedef struct list_item{
  tInstr instruct;
  struct list_item *next_item;
} tList_item;


typedef struct {
  struct list_item *first;  // prvni prvek
  struct list_item *last;   // posledni prvek
  struct list_item *act;    // aktivni prvek
} tInstrList;



void list_init (tInstrList *L);
void list_free (tInstrList *L);
int list_insert_last (tInstrList *L, tInstr I);
void list_first (tInstrList *L);
void list_next (tInstrList *L);
void list_goto (tInstrList *L, void *goto_instr);
void *GetLastPointer (tInstrList *L);
tInstr *GetData (tList_item *L);
