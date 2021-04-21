#include <stdio.h>
#include <stdlib.h>

typedef void (*fnptr_t)(void);

typedef struct struct_A{
  fnptr_t *vptr;
  int value;

}struct_A;

typedef struct struct_B{
  fnptr_t *vptr;
  int value;
  int extra;
}struct_B;

void do_something(struct_A* ptr){
  ptr->vptr[0]();
}

void showA(){
  printf("%s","show structA\n");
}

void showB(){
  printf("%s", "show structB\n");
}

fnptr_t vTable_A[1] = {showA};
fnptr_t vTable_B[1] = {showB};

struct_A* initA(int v){
  struct_A *ret = malloc(sizeof(*ret));
  ret->value=v;
  ret->vptr = vTable_A;
  return ret;
  
struct_B* initB(int v, int e){
  struct_B* ret = malloc(sizeof(*ret));
  ret->value=v;
  ret->extra=e;
  ret->vptr = vTable_B;
  return ret;
}

void deleteA(struct_A* ptr){
  free(ptr);
}

void deleteB(struct_B* ptr){
  free(ptr);
}
int main(){
  struct_A* a = initA(1);
  struct_B* b= initB(3,4);
  do_something(a);
  do_something((struct_A*)b);
  return 0;
}

