#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>


#define uchar unsigned char

typedef struct
{
	char* FirstName;
	char* LastName;
	char* PhoneNumber;
} User;


extern uchar* get_string(uint16_t *len);
