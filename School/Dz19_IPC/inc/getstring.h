#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>


#define uchar unsigned char

typedef struct
{
	unsigned char* FirstName;
	unsigned char* LastName;
	unsigned char* PhoneNumber;
} User;


extern unsigned char* get_string(unsigned int *len);
