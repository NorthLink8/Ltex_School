#include "main.h"

int show_dir(unsigned char* path)
{
  u16 count=0;
  DIR* d=opendir(path);
  if(d==NULL)
  {
    perror("open dir of plugins");
    return -1;
  }
  struct dirent* dir;

  while((dir=readdir(d))!=NULL)
  {
    if(strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      printf("%d  %s\n", count, dir->d_name);
    }
  }
  //count=0;
  unsigned char name[PATH_MAX];
  if(getcwd(name, sizeof(name))!=NULL)
    printf("%s\n", name);

  return (int)count;
}

int SetPlugs(unsigned char* path)
{
  u16 count=0;
  DIR* d=opendir(path);
  if(d==NULL)
  {
    perror("open dir of plugins");
    return -1;
  }
  struct dirent* dir;

  while((dir=readdir(d))!=NULL)
  {
    if(strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      unsigned char FullPathName[PATH_MAX];
      sprintf(FullPathName,  "%s/%s", path, dir->d_name);
      
      void* plugsErr=dlopen(FullPathName, RTLD_LAZY|RTLD_GLOBAL);
      if(!plugsErr)
      {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        continue;
      }
      printf("DlOpen: %s\n", FullPathName);
      unsigned char* funcName = dlsym(plugsErr, "FUNC_NAME"); 
      printf("%s\n", funcName);
    }
    
  }
  return (int)count;
}


int main(void)
{
  int numofplugs=0;
  show_dir("./plugins/inc");
  printf("\n");
  //printf("\nNum of plugins = %d\n", numofplugs);
  
  
  printf("Num of plugins = %d\n", numofplugs);
  SetPlugs("./plugins/inc");


  /*
  while(1)
  {
  }
  */
  return 0;
}
