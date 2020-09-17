#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <sys/wait.h>
#include <dirent.h>
#include <pthread.h>

#include <ncurses.h>
#include <panel.h>

#define BUFSIZE (10)

//void _file_copy(char buf[2][PATH_MAX]);
//void _copy_status(int** status[2]);
//extern void* _filecopy(unsigned char* path1, unsigned char* path2);
extern void* _filecopy(unsigned char* _path1, unsigned char* _path2, WINDOW* window, unsigned int _line, unsigned int _col);
