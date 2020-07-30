#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>


#define   uchar   unsigned char
#define   u8      uint8_t
#define   u16     uint16_t
#define   u32     uint32_t

uchar* getstring(u16* len);
