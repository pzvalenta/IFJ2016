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
 #define I_SUB          2     //odcitani
 #define I_MUL          3     //nasobeni
 #define I_DIV          4     //deleni

 #define I_GREAT        5     //vetsi nez >
 #define I_LESS         6     //mensi nez <
 #define I_GREQ         7     //vetsirovno >=
 #define I_LESEQ        8     //mensirovno <=
 #define I_EQUAL        9     //rovna se ==
 #define I_NEQUAL       10    //nerovna se !=

 // #define I_FIND         9     //find
 // #define I_INC          10    //inkrementace
 // #define I_DEC          11    //dekrementace
 // #define I_NOT          12    //not
 // #define I_IFGOTO       13    //podmineny skok
 // #define I_GOTO         14    //skok

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
