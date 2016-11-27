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
 #define BASE_STACK_SIZE 20

//hlavicka pro interpret
 int interpret(tInstrList *instrList);
typedef struct{
  int type;
  void *val;
}*St_data;

// zasobnik
 typedef struct Stack{
   St_data data;  //ulozena data
   int size;
   struct Stack *next;   //odkaz na dalsi prvek zasobniku
   int topof; //top of the stack
 }Stack;


 //hlavicky funkci pro zasobnik:
 Stack Init_stack();

 void Push_stack(Stack stack, void *value, int type);

 void Pop_stack(Stack stack, void ** value, int type);

 void Free_stack(Stack *stack);

 void ResizeStack(Stack *stack);
