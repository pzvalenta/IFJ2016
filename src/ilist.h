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
 #define I_STOP         0     //stop
 #define I_ADD_INT      1     //int + int
 #define I_ADD_DOUBLE   2     //double + double
 #define I_SUB_INT      3     //int - int
 #define I_SUB_DOUBLE   4     //double - double
 #define I_MUL_INT      5     //int * int
 #define I_MUL_DOUBLE   6     //double * double
 #define I_DIV_INT      7     //dividing integers
 #define I_DIV_DOUBLE   8     //dividing doubles
 #define I_FIND         9     //find
 #define I_INC          10    //inkrementace
 #define I_DEC          11    //dekrementace
 #define I_NOT          12    //not
 #define I_IFGOTO       13    //podmineny skok
 #define I_GOTO         14    //skok
 #define I_EQUAL        15    //rovna se
 #define I_NEQUAL       16    //nerovna se
 #define I_LABEL        17    //navesti


typedef struct{
  int Inst_type;     //typ instrukce
  void *addr1;       //zdroj 1
  void *addr2;       //zdroj 2
  void *addr3;       //cil
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
