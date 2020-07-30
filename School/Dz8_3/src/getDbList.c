#include "../inc/getDbList.h"

//

//Создаем экземпляр структуры DbLinkedList(Двусвязного списка)
DbLinkedList* createDbLinkedList()
{
  DbLinkedList *tmp = (DbLinkedList*)malloc((int)sizeof(DbLinkedList));
  tmp->size=0;
  tmp->head = tmp->tail=NULL;

  return tmp;
}

//Удаление двусвязного списка
void deleteDbLinkedList(DbLinkedList** list)
{
  Node* tmp = (*list)->head;
  Node* next = NULL;
  while(tmp)
  {
    next=tmp->next;
    free(tmp);
    tmp=next;
  }
  free(*list);
  (*list)=NULL;
}

//Вставка элемента спереди
void pushFront(DbLinkedList* list, void* data)
{
  Node* tmp = (Node*)malloc((int)sizeof(Node));

  if(tmp == NULL)
    exit(1);

  tmp->value=data;
  tmp->next = list->head;
  tmp->prev = NULL;
  if(list->head)
    list->head->prev = tmp;
  
  list->head = tmp;
  
  if(list->tail==NULL)
    list->tail = tmp;

  list->size++;
}

//Удаление элемента спереди
void* popFront(DbLinkedList* list)
{
  Node* prev;
  Node* tmp;

  if(list->head == NULL)
    exit(2);

  prev = list->head;
  list->head = list->head->next;

  if(list->head)
    list->head->prev = NULL;

  if(prev == list->tail)
    list->tail=NULL;

  tmp=prev->value;
  free(prev);
  list->size--;
  return tmp;
}

//Вставка элемента с конца
void pushBack(DbLinkedList* list, void* value)
{
  Node* tmp = (Node*)malloc(sizeof(Node));
  if(tmp == NULL)
    exit(3);

  tmp->value=value;
  tmp->next=NULL;
  tmp->prev=list->tail;

  if(list->tail)
    list->tail->next=tmp;

  list->tail=tmp;

  if(list->head == NULL)
    list->head = tmp;

  list->size++;
}

//Удаление элемента с конца
void* popBack(DbLinkedList* list)
{
  Node* next;
  void* tmp;
  
  if(list->tail == NULL)
    exit(4);

  next = list->tail;
  list->tail = list->tail->prev;
  
  if(list->tail)
    list->tail->next = NULL;

  if(next == list->head)
    list->head = NULL;

  tmp = next->value;
  free(next);
  
  list->size--;
  return tmp;
}

//получение N-го элемента
Node* getNth(DbLinkedList* list, size_t index)
{
  Node* tmp=list->head;
  size_t i = 0;
  
  if(index < list->size/2)
  {
    i=0;
    tmp = list->head;
    while(tmp && i<index)
    {
      tmp = tmp->next;
      i++;
    }
  }
  else
  {
    i = list->size - 1;
    tmp = list->tail;
    while(tmp && i>index)
    {
      tmp = tmp->prev;
      i--;
    }
  }
  /*
  while(tmp && i<index)
  {
    tmp = tmp->next;
    i++;
  }
  */
  return tmp;
}

//Вставка узла
void insert(DbLinkedList* list, size_t index, void* value)
{
  Node* elm = NULL;
  Node* ins = NULL;
  elm = getNth(list, index);

  if(elm == NULL)
    exit(5);

  ins = (Node*)malloc(sizeof(Node));
  ins->value = value;
  ins->prev = elm;
  ins->next = elm->next;
  
  if(elm->next)
    elm->next->prev = ins;
  
  elm->next=ins;

  if(!elm->prev)
    list->head = elm;
  if(!elm->next)
    list->tail = elm;

  list->size++;
}

//Удаление узла
void* deleteNth(DbLinkedList* list, size_t index)
{
  Node* elm = NULL;
  void* tmp = NULL;
  elm = getNth(list, index);
  
  if(elm == NULL)
    exit(5);
  if(elm->prev)
    elm->prev->next = elm->next;
  if(elm->next)
    elm->next->prev = elm->prev;

  tmp = elm->value;

  if(!elm->prev)
    list->head = elm->next;
  if(!elm->next)
    list->tail = elm->prev;
  
  free(elm);
  list->size--;
  return tmp;
}

//Функия печати одного элемента
void printDbLinkedList(DbLinkedList* list, void (*fun)(void*))
{
  Node* tmp = list->head;
  while(tmp)
  {
    fun(tmp->value);
    tmp = tmp->next;
  }
  printf("\n");
}


void printInt(void* value)
{
  printf("%d", *((int*)value));
}



//Создание списка из массива
DbLinkedList* fromArray(void* arr, size_t n, size_t size)
{
  DbLinkedList* tmp = NULL;
  size_t i = 0;
  
  if(arr == NULL)
    exit(7);

  tmp = createDbLinkedList();
  while(i<n)
  {
    pushBack(tmp, ((uchar*)arr + i*size));
    i++;
  }
  return tmp;
}
