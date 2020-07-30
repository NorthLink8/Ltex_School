#include "../inc/getstring.h"

//Структура-узел
typedef struct _Node
{
  void* value;
  struct _Node* next;
  struct _Node* prev;
} Node;


//Структура-Двусвязный список
typedef struct _DbLinkedList
{
  size_t size;
  Node* head;
  Node* tail;
} DbLinkedList;

DbLinkedList* createDbLinkedList();
void deleteDbLinkedList(DbLinkedList** list);
void pushFront(DbLinkedList* list, void* data);
void* popFront(DbLinkedList* list);
void pushBack(DbLinkedList* list, void* value);
void* popBack(DbLinkedList* list);
Node* getNth(DbLinkedList* list, size_t index);
void insert(DbLinkedList* list, size_t index, void* value);
void* deleteNth(DbLinkedList* list, size_t index);
void printDbLinkedList(DbLinkedList* list, void (*fun)(void*));
void printInt(void* value);
void printString(void* _string);

DbLinkedList* fromArray(void* arr, size_t n, size_t size);
