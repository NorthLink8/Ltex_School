#include "main.h"


uint8_t BookSize=1;
uchar *action="work";


void StringCPY(uchar* string1, uchar* string2)
{
  for(uint8_t i=0; i<strlen(string2); i++)
    string1[i]=string2[i];
}

void Act(User** _structure, uchar* string)
{
	if(!strcmp(string, "book"))
	{
    //printf("%d\n",sizeof(User));
		for(uint8_t t=0; t<BookSize; t++)
		{
			printf("%d: \n", t+1);
			//printf("  sizeof(_structure)=%d \n", sizeof(_structure));
			printf("	%s \n", _structure[t]->FirstName);
			printf("	%s \n", _structure[t]->LastName);
			printf("	%s \n", _structure[t]->PhoneNumber);
		}
	}
	else if(!strcmp(string, "new"))
	{
		BookSize++;
		*_structure=(User*)realloc(*_structure, ((sizeof(User))*(BookSize)));
				
		uint16_t length=50;
    printf("Enter new user first name: ");
		uchar *string=get_string(&length);
		

    _structure[BookSize-1]->FirstName=(uchar*)malloc(strlen(string) * sizeof(uchar));
    StringCPY(_structure[BookSize-1]->FirstName, string);
		//strcpy(_structure[BookSize-1]->FirstName, string);
		free(string);

		printf("Enter new user last name: ");
		string=get_string(&length);
    _structure[BookSize-1]->LastName=(uchar*)malloc(strlen(string) * sizeof(uchar));
		StringCPY(_structure[BookSize-1]->LastName, string);
    //strncpy(_structure[BookSize-1]->LastName, string,strlen(_structure[BookSize-1]->LastName));
    //strcpy(_structure[BookSize-1]->LastName, string);
		free(string);
	
		printf("Enter new user phone: ");
		string=get_string(&length);
		_structure[BookSize-1]->PhoneNumber=(uchar*)malloc(strlen(string) * sizeof(uchar));
    StringCPY(_structure[BookSize-1]->PhoneNumber, string);
    //strncpy(_structure[BookSize-1]->PhoneNumber, string,strlen(_structure[BookSize-1]->PhoneNumber));
		//strcpy(_structure[BookSize-1]->PhoneNumber, string);
		free(string);
    
    printf("BookSize=%d\nsizeof(User)=%d\n", BookSize, (int)sizeof(User));
	}
}


int main(void)
{
  printf("Hello user :)\n");

  User* _user;
	_user=(User*)malloc(1*sizeof(User));
  printf("Start sizeof(Structure)=%d\n\n", (int)sizeof(User));

	_user[0].FirstName=(uchar*)malloc(strlen("Alexandr")*sizeof(uchar));
	strcpy(_user[0].FirstName, "Alexandr\0");

	_user[0].LastName=(uchar*)malloc(strlen("Kartonozhkin")*sizeof(uchar));
	strcpy(_user[0].LastName, "Kartonozhkin\0");
	
	_user[0].PhoneNumber=(uchar*)malloc(strlen("+79137697818")*sizeof(uchar));
	strcpy(_user[0].PhoneNumber, "+79137697818\0");

  printf("BookSize=%d\nsizeof(Structure)=%d\n", BookSize+1,(int)sizeof(User));
  

	/*
  printf("%d \n", sizeof(*_user));

	printf("%s \n", _user[0].FirstName);
	printf("%s \n", _user[0].LastName);
	printf("%s \n", _user[0].PhoneNumber);
	*/

	while(strcmp(action,"exit")!=0)
	{
		printf("Enter the action:");
		uint16_t len=50;
		action=get_string(&len);

		Act(&_user, action);
	}

  return 0;
}
