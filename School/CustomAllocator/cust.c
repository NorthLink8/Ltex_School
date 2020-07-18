#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define uchar unsigned char
#define u8 uint8_t
#define u16 uint16_t
#define STACK_SIZE 32
#define HEAP_SIZE STACK_SIZE * 4
#define HEADER 4

static u16 IN_USE=0;

typedef struct
{
  u8 stack[STACK_SIZE];
  uchar** unmapped;
  u8 heap[HEAP_SIZE];

  struct
  {
    uchar** data;
    uchar** bss;
    uchar* text;
  } data_t;
} virtual_mem;

typedef struct
{
  u8* ptr;
  u16 size;
} entity;
entity LIST[40];

void LOG()
{
  printf("OUR LIST\n");
  for(unsigned i=0; i<IN_USE; i++)
  {
    printf("Data + HEADER.[%p]. Memory of heap free:[%d]\n", LIST[i].ptr, LIST[i].size);
  }
  printf("Entitis in use:[%d]\n", ((sizeof(LIST)/sizeof(LIST[0])-IN_USE)));
}

//size_t кроссплатформенный размер данных, который может хранить самые большой размер массива
entity* new_entity(size_t size)
{
  if(LIST[0].ptr == NULL && LIST[0].size==0)
  {
    static virtual_mem vm;//Глобализируем статичную перменную Сохраняем ее state
    LIST[0].ptr=vm.heap;
    LIST[0].size=HEAP_SIZE;
    IN_USE++;
    LOG();
  }
  entity* best = LIST;

  for(unsigned i=0; i<IN_USE; i++)
  {
    if(LIST[i].size >= size && LIST[i].size<best->size)
    {
      best=&LIST[i];
    }
  }
  return best;//Возвращаем лучшую область памяти
}

//heap coalizing
void* w_malloc(size_t size)
{
  //Heap пока что не растет. Это плохо, но это можно будет исправить
  assert(size <= HEAP_SIZE);//Места больше нет
  size +=HEADER;
  
  entity* e=new_entity(size);
  
  u8* start = e->ptr;//Старт нашего Heap
  u8* user_ptr = start+HEADER;
  
  *start = size;

  e->ptr+=size;
  e->size-=size;
  
  
  //****************//
  assert(e->size >= 0);
  //***************//
  
  LOG();
  return user_ptr;
}

void w_free(void* ptr)
{
   u8* start = (u8*)ptr - HEADER;

   LIST[IN_USE].ptr=start;//&(*stzrt)
   LIST[IN_USE].size=*start;//(u8)*((u8*)ptr-HEADER)
   IN_USE++;
   LOG();
}


void test()
{
  /*
  int* a = w_malloc(sizeof(int));
  int* b = w_malloc(sizeof(long));

  w_free(a);
  */
  typedef struct
  {
    int a;
    int b;
  } foo;

  foo* _foo;
  char* bar;
  int* bazz;

  _foo = w_malloc(sizeof(_foo));
  bar = w_malloc(5);
  bazz = w_malloc(sizeof(int));

  _foo->a=5;
  _foo->b=10;

  strcpy(bar, "bar\0");
  memcpy(bazz, &_foo->a, sizeof(int));
  
  printf("//*******************************//\n");
  printf("Address: [%p], data: [%d] [%d]\n", _foo, _foo->a, _foo->b);
  printf("Address: [%p], data: [%c]\n", bar, *bar);
  printf("Address: [%p], data: [%d]\n", bazz, *bazz);
  printf("Дикая фрагментация! Отвечаю...");

  w_free(_foo);
  w_free(bar);


  char* other = w_malloc(4);
  //Этой строчкой мы забъем всю память в heap и полностью его зафрагментируем. Останется 0
  //Если в malloc подставить вообще 96 то, сработает assert!
  //char* other = w_malloc(95);
  strcpy(other, "other");
  printf("Addres: [%p], data: [%s] \n", other, other);
}


int main(void)
{
  test();
  return 0;
}
