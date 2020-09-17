#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <ncurses.h>
#include <panel.h>


#define uchar unsigned char

typedef struct
{
	char* FirstName;
	char* LastName;
	char* PhoneNumber;
} User;

extern unsigned char* get_string(unsigned int *len, WINDOW* win);

extern unsigned char* get_simString(unsigned int* len);
