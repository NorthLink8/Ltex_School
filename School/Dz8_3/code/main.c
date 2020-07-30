#include "main.h"

uchar* action="work";
//DbLinkedList* list = createDbLinkedList();
DbLinkedList* list;


typedef struct _FirstUser
{
  char* FirstName;
  char* LastName;
  char* PhoneNumber;
} FirstUser;


void printStr(uchar* _str)
{
  for(uint8_t i=0; i<strlen(_str); i++)
    printf("%c", _str[i]);
  printf("\n");
}


void printDbLinkedStructs(DbLinkedList* list)
{
  u8 num=0;
  FirstUser* _struct;
  Node* tmp = list->head;
  while(tmp)
  {
    num++;
    _struct = tmp->value;
    printf("%d\n", num); 
    /*
    printf("%s\n", _struct->FirstName);
    printf("%s\n", _struct->LastName);
    printf("%s\n", _struct->PhoneNumber);
    */
    printStr(_struct->FirstName);
    printStr(_struct->LastName);
    printStr(_struct->PhoneNumber);
    tmp = tmp->next;
  }
  printf("\n");
}

void AddNew()
{
  FirstUser nuser;
  u16 length1=50;
  printf("Enter first name of new user: ");
  uchar* _string1=getstring(&length1);
  nuser.FirstName = (uchar*)malloc(strlen(_string1)*(int)sizeof(uchar));
  strcpy(nuser.FirstName, _string1);
  //free(length);
  u16 length2=50;
  printf("Enter last name of new user: ");
  uchar* _string2=getstring(&length2);
  nuser.LastName = (uchar*)malloc(strlen(_string2)*(int)sizeof(uchar));
  strcpy(nuser.LastName, _string2);  
  //free(length);
  u16 length3=50;
  printf("Enter phone number of new user: ");
  uchar* _string3=getstring(&length3);
  nuser.PhoneNumber = (uchar*)malloc(strlen(_string3)*(int)sizeof(uchar));
  strcpy(nuser.PhoneNumber, _string3);
  //free(length);
  /*
  printf("%s\n", NewUser.FirstName);
  printf("%s\n", NewUser.LastName);
  printf("%s\n", NewUser.PhoneNumber);
  */
  pushBack(list, &nuser); 
}



int main(void)
{
  /*
  printf("Enter your string: ");
  u16 length=50;
  uchar* _string=getstring(&length);
  printf("%s\n", _string);
  free(_string);
  */
  printf("PHONE LIST\n");
  list = createDbLinkedList();
  
  FirstUser fuser;
  //fuser=(FirstUser*)malloc(1*sizeof(FirstUser));
	fuser.FirstName=(uchar*)malloc(strlen("Alexandr")*sizeof(uchar));
	strcpy(fuser.FirstName, "Alexandr\0");
	fuser.LastName=(uchar*)malloc(strlen("Kartonozhkin")*sizeof(uchar));
	strcpy(fuser.LastName, "Kartonozhkin\0");
	fuser.PhoneNumber=(uchar*)malloc(strlen("+79137697818")*sizeof(uchar));
	strcpy(fuser.PhoneNumber, "+79137697818\0");
  pushBack(list, &fuser);


  //printDbLinkedStructs(list);
  
  //printDbLinkedList(list, printString);
  /*int a=10,b=20,c=30,d=40,e=50,f=60,g=70,h=80;
  
  pushBack(list, &a);
  pushBack(list, &b);
  pushBack(list, &c);
  pushBack(list, &d);
  pushBack(list, &e);
  pushBack(list, &f);
  pushBack(list, &g);
  pushBack(list, &h);
  printDbLinkedList(list, printInt);

  printf("length %d\n", list->size);
  printf("nth 2 %d\n", *((int*)getNth(list, 2)->value));*/
  
  while(1)
  {
    printf("Enter your action:");
    u16 _length=50;
    action=getstring(&_length);
    if(!strcmp(action, "exit"))
    {
      printf("End of program.\n");
      break;
    }
    else if(!strcmp(action, "add"))
    {
      AddNew();
    }
    else if(!strcmp(action, "list"))
    {
      printDbLinkedStructs(list);
    }
  }
  return 0;
}
