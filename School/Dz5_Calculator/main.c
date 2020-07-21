#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define uchar unsigned char

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

void Math(uchar* operation)
{
 	int32_t	Num1=0, Num2=0, Result;
	
	printf("Enter num1: ");
	scanf("%d", &Num1);
	printf("Enter num2: ");
	scanf("%d", &Num2);

	if(operation[0]=='+')
		Result=Num1+Num2;
	else if(operation[0]=='-')
		Result=Num1-Num2;
	else if(operation[0]=='*')
		Result=Num1*Num2;
	else if(operation[0]=='/')
		Result=Num1/Num2;

	printf("%d%c%d=%d\n", Num1, operation[0], Num2, Result);
}

void StringProcessing()
{
	uint16_t length=50;
	uchar* _string="work";
	while(strcmp(_string, "exit")!=0)
	{
		printf("Enter the action: ");
		_string=get_string(&length);
		if(strcmp(_string, "math")==0)
		{
			printf("Enter math operation: ");
			uchar* _operation=get_string(&length);
			Math(_operation);
			free(_operation);
		}
	}
	//free(_string);
}

int main(void)
{
	StringProcessing();
	return 0;
}

