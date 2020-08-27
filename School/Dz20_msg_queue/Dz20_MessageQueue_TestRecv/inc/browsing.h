#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <ncurses.h>
#include <panel.h>

#include <sys/wait.h>
#include "../inc/filework.h"
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include "../inc/getstring.h"

void show_dir(unsigned char* _absPath, WINDOW* win, uint8_t* ddY);
void new_dir(unsigned char* oldPath, unsigned char* move, uint8_t ddY);
void run_prog(WINDOW* win, unsigned char* Path, uint8_t ddY);
void COPYfile(unsigned char* Path1, unsigned char* Path2, WINDOW* Win, unsigned int Line, unsigned int Col, uint8_t ddY);
void NewMassage(WINDOW* win);
