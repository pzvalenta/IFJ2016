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

 // typy instrukci
 #define I_STOP     0     //stop
 #define I_ADD      //1     //+
 #define I_SUB      //2     //-
 #define I_MUL      //3     //*
 #define I_DIV      //4     //div
 #define I_FIND     //5     //find
 #define I_INC      6     //inkrementace
 #define I_DEC      //7     //dekrementace
 #define I_NOT      //8     //not
 #define I_IFGOTO   9     //podmineny skok
 #define I_GOTO     10    //skok
 #define I_EQUAL    //11    //rovna se
 #define I_NEQUAL   //12    //nerovna se
 #define I_LABEL      13    //navesti


typedef struct{
  int Inst_type;     //typ instrukce
  void *addr1;
  void *addr2;
  void *addr3;
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
void list_insert_last (tInstrList *L, tInstr I);
void list_first (tInstrList *L);
void list_next (tInstrList *L);
void list_goto (tInstrList *L, void *goto_instr);
void *GetLastPointer (tInstrList *L);
tInstr *GetData (tList_item *L);
