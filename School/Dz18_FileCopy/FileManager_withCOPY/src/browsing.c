#include "../inc/browsing.h"

void show_dir(unsigned char* _absPath, WINDOW* win, uint8_t* ddY)
{

  uint16_t count=0;
  DIR* d=opendir(_absPath);
  if(d==NULL)
    return; 

  struct dirent* dir;

  while((dir=readdir(d))!=NULL)
  {
    if(dir->d_type==DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      mvwprintw(win, count, 3, "./%s", dir->d_name);
    }
    if(dir->d_type==DT_REG && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      mvwprintw(win, count, 3, "%s", dir->d_name);
    }
  }
  /*
  unsigned char name[PATH_MAX];
  if(getcwd(name, sizeof(name))!=NULL)
    mvwprintw(win, count+2,1,"%s",name);
  */
  
  //

  if(*ddY>count)
    *ddY=count;
  else if(*ddY<=1)
    *ddY=1;

  for(uint16_t i=0; i<count; i++)
    mvwprintw(win, i,1, "%c", ' ');
  mvwprintw(win, *ddY, 1, "%c", '>');
  mvwprintw(win, count+3,1,"%d", *ddY);
  mvwprintw(win, count+4, 1, "%s", _absPath);
  count=0;
  closedir(d);
}

void new_dir(unsigned char* oldPath, unsigned char* move, uint8_t ddY)
{
  uint16_t count=0;
  DIR* d=opendir(oldPath);
  if(d==NULL)
    return;
  struct dirent* dir;
  
  if(strcmp(move, ".")==0)
  {
    while((dir=readdir(d))!=NULL)
    {
      if(dir->d_type==DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        count++;
        if(count==ddY)
        {
          sprintf(oldPath, "%s/%s", oldPath, dir->d_name);
          count=0;
          break;
        }
      }
      if(dir->d_type==DT_REG && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        count++;
      }
    }
  }
  else
  {
    unsigned char newPath[PATH_MAX];
    strcpy(newPath, oldPath);
    for(uint16_t t=strlen(newPath); t>1; t--)
    {
      if(newPath[t]!='/')
        newPath[t]=0;
      else
      {
        newPath[t]=0;
        newPath[t+1]=0;
        break;
      }
    }
    strcpy(oldPath, newPath);
  }
  closedir(d);
}

void run_prog(WINDOW* win, unsigned char* Path, uint8_t ddY)
{
  uint16_t count=0;
  unsigned char PathToProg[PATH_MAX];
  DIR* d=opendir(Path);
  if(d==NULL)
  {
    //exit(EXIT_FAILURE);
    return;
  }
  struct dirent* dir;

  while((dir=readdir(d))!=NULL)
  {
    if(dir->d_type==DT_REG && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      if(count==ddY)
      {
        sprintf(PathToProg,"%s/%s", Path, dir->d_name);
        //mvwprintw(win, 10, 1, "%s", PathToProg);
        count=0;
        break;
      }
    }
    else if(dir->d_type==DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
    }
  }
  endwin();
  closedir(d);
  
  pid_t pid=0;
  int rv;
  pid=fork();
  if(pid<0)
  {
    perror("fork");
    //exit(EXIT_FAILURE);
    return;
  }
  else if(pid==0)
  {
    execv(PathToProg, NULL);
    exit(rv);
  }
  else
  {
    wait(&rv);
  }
  
}


//Тут просто надо получить им файла, который собираюсь копировать
void COPYfile(unsigned char* Path1, unsigned char* Path2, WINDOW* Win, unsigned int Line, unsigned int Col, uint8_t ddY)
{
  uint16_t count=0;
  unsigned char PathToFile[2][PATH_MAX];
  DIR* d=opendir(Path1);
  if(d==NULL)
  {
    //exit(EXIT_FAILURE);
    return;
  }
  struct dirent* dir;

  //mvwprintw(Win, Line, Col, "%s", Path1);
  //mvwprintw(Win, Line+1, Col, "%s", Path2);
  while((dir=readdir(d))!=NULL)
  {
    if(dir->d_type==DT_REG && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      if(count==ddY)
      {
        sprintf(PathToFile[0],"%s/%s", Path1, dir->d_name);
        sprintf(PathToFile[1],"%s/%s", Path2, dir->d_name);
        //mvwprintw(Win, Line, Col, "%s", PathToFile[0]);
        //mvwprintw(Win, Line+1, Col, "%s", PathToFile[1]);
        count=0;
        break;
      }
    }
    else if(dir->d_type==DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
    }
  }
  //ПОЛУЧИЛИ ИМЯ ФАЙЛА, КОТОРЫЙ НУЖНО СКОПИРОВАТЬ
  _filecopy(PathToFile[0], PathToFile[1], Win, Line, Col);
  
}



