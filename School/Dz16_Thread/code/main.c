#include "./main.h"

long A=0;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

void* func(void* param)
{
  
  unsigned long tmp=0;
  //unsigned i=0;
  for(unsigned long i=0; i<1000000; i++)
  {
    pthread_mutex_lock(&mut);
    tmp=A;
    tmp++;
    A=tmp;
    pthread_mutex_unlock(&mut);
  }
  
 //pthread_exit(0);
}

int main(void)
{
  pthread_t tid[1000];
  //Инициализация mutex
  //pthread_mutex_init(&mut, NULL);

  for(unsigned k=0; k<1000; k++)
    pthread_create(&tid[k], NULL, (void*)func, NULL);

  for(unsigned i=0; i<1000; i++)
    pthread_join(tid[i], NULL);    
  
  printf("%d\n", A);

  return 0;
}


