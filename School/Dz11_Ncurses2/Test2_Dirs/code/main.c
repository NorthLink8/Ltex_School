#include "main.h"


void show_dir(unsigned char* path)
{
  DIR* d = opendir(path);
  if(d==NULL)
    return;
  struct dirent* dir;
  while((dir=readdir(d))!=NULL)
  {
    if(dir->d_type != DT_DIR)
      printf("%s%s\n", "\x1B[32m" /*It's GREEN*/, dir->d_name);
    else
    {
      if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        printf("%s%s\n", "\x1B[34m"/*It's BLUE*/, dir->d_name);
        unsigned char d_path[255];
        sprintf(d_path, "%s%s", path, dir->d_name);
        show_dir(d_path);
      }
      else
        printf("%s%s\n", "\x1B[0m"/*NORMAL*/, dir->d_name);
        
    }
  }
  closedir(d);
}


int main(void)
{
  /*
  DIR* d;
  struct dirent* dir;
  d = opendir(".");
  if(d)
  {
    while((dir=readdir(d))!=NULL)
      printf("%s\n", dir->d_name);
    closedir(d);
  }
  */
  show_dir(".");
  /*
  while(1)
  {
  }
  */
  return 0;
}
