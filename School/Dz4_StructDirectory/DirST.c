#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char
uint8_t BookSize=0;

typedef struct
{
	char* FirstName;
	char* LastName;
	char* PhoneNumber;
} User;

uchar* get_string(uint16_t *len)
{
	*len=0;
	uint16_t capacity=1;
	uchar* s=(uchar*)malloc(10*sizeof(uchar));
	uchar c=getchar();

	while(c!='\n')
	{
		s[(*len)++]=c;
		if(*len>=10)
		{
			capacity*=2;
			s=(uchar*)realloc(s, capacity*sizeof(uchar));
		}
		c=getchar();
	}
	s[*len]='\0';
	return s;
}

void Act(User** _structure, uchar* string)
{
	if(!strcmp(string, "book"))
	{
		for(uint8_t t=0; t<BookSize+1; t++)
		{
			printf("%d: \n", t+1);
			printf("	%d \n", sizeof(User));
			printf("	%s \n", _structure[t]->FirstName);
			printf("	%s \n", _structure[t]->LastName);
			printf("	%s \n", _structure[t]->PhoneNumber);
		}
	}
	else if(!strcmp(string, "new"))
	{
		BookSize++;
		*_structure=(User*)realloc(*_structure, (sizeof(User)*(BookSize+1)));
		printf("%d\n%d\n", BookSize+1,sizeof(User));		
		uint16_t length=50;
		printf("Enter new user first name: ");
		
		uchar *string=get_string(&length);
		_structure[BookSize]->FirstName=(uchar*)malloc(strlen(string) * sizeof(uchar));
		strcpy(_structure[BookSize]->FirstName, string);
		free(string);

		printf("Enter new user last name: ");
		string=get_string(&length);
		_structure[BookSize]->LastName=(uchar*)malloc(strlen(string) * sizeof(uchar));
		strcpy(_structure[BookSize]->LastName, string);
		free(string);
	
		printf("Enter new user phone: ");
		string=get_string(&length);
		_structure[BookSize]->PhoneNumber=(uchar*)malloc(strlen(string) * sizeof(uchar));
		strcpy(_structure[BookSize]->PhoneNumber, string);
		free(string);
	}
}

uchar *action="work";



int main (void)
{
	
	User* _user;
	_user=(User*)malloc(1*sizeof(User));

	_user[0].FirstName=(uchar*)malloc(strlen("Alexandr")*sizeof(uchar));
	strcpy(_user[0].FirstName, "Alexandr\0");

	_user[0].LastName=(uchar*)malloc(strlen("Kartonozhkin")*sizeof(uchar));
	strcpy(_user[0].LastName, "Kartonozhkin\0");
	
	_user[0].PhoneNumber=(uchar*)malloc(strlen("+79137697818")*sizeof(uchar));
	strcpy(_user[0].PhoneNumber, "+79137697818\0");

	printf("%d \n", sizeof(*_user));

	printf("%s \n", _user[0].FirstName);
	printf("%s \n", _user[0].LastName);
	printf("%s \n", _user[0].PhoneNumber);
	
	while(strcmp(action,"exit")!=0)
	{
		printf("Enter the action:");
		uint16_t len=50;
		action=get_string(&len);

		Act(&_user, action);

	}


	return 0;
}
