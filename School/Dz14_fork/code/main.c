#include "./main.h"

int main(void)
{
/*
  pid_t pid;
  int rv;
  pid=fork();
  if(pid==-1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if(pid == 0)
  {
    printf("CHILD: CHILD\n");
    printf("CHILD: My PID -- %d\n", getpid());
    printf("CHILD: Parent PID -- %d\n", getppid());
    printf("CHILD: EXIT\n");
    exit(rv);
  }
  else
  {
    printf("PARENT: PARENT\n");
    printf("PARENT: My PID -- %d\n", getpid());
    printf("PARENT: Child PID -- %d\n", pid);
    printf("Wait CHILD");
    wait(&rv);
    printf("PARENT: CHILD exit --%d\n", WEXITSTATUS(rv));
    printf("PARENT: END\n");
  }
*/


  pid_t pid1;
  int rv[6];
  pid1 = fork();
  if(pid1==-1)
  {
    perror("first fork");
    exit(EXIT_FAILURE);
  }
  else if(pid1==0)
  {
    pid_t pid4=fork();
    if(pid4==0)
    {
      printf("CHAILD4: My PID--%d\n", getpid());
      printf("CHAILD4: My parent PID--%d\n", getppid());
      exit(rv[3]);
    }
    else
    {
      pid_t pid5=fork();
      if(pid5==0)
      {
        printf("CHAILD5: My PID--%d\n", getpid());
        printf("CHAILD5: My parent PID--%d\n", getppid());
        exit(rv[5]);
      }
      else
      {
        printf("CHAILD1: My PID--%d\n", getpid());
        printf("CHAILD1: My parent PID--%d\n", getppid());
        wait(&rv[4]);
        wait(&rv[3]);
        printf("CHAILD1: CHAILD4 return:%d\n", WEXITSTATUS(rv[4]));
        printf("CHAILD3: CHALID3 return:%d\n", WEXITSTATUS(rv[3]));
        exit(rv[1]);
       }
     }
  }
  else
  {
    pid_t pid2=fork();
    if(pid2==0)
    {
      pid_t pid3=fork();
      if(pid3==0)
      {
        printf("CHAILD3: My PID--%d\n", getpid());
        printf("CHAILD3: My parent PID--%d\n", getppid());
        exit(rv[3]);
      }
      else
      {
        printf("CHAILD2: My PID--%d\n", getpid());
        printf("CHAILD2: My parent PID--%d\n", getppid());
        wait(&rv[3]);
        printf("CHAILD2: CHAILD3 return: %d\n", WEXITSTATUS(rv[3]));
        exit(rv[2]);
      }
    }
    else
    {
      printf("PARENT: My PID--%d\n", getpid());
      printf("PARENT: My parent PID--%d\n", getppid());
      wait(&rv[2]);
      wait(&rv[1]);
    }
    
  }



  return 0;
}


