#include "./main.h"
pthread_t tid[4];
pthread_mutex_t mut[5];
unsigned int magazine[5];
unsigned int customer[3];
unsigned int count[3];
//pthread_cond_t cnd[5];
//rand()%100+550;


void customers(int num)
{
  //unsigned int count=0;
  while(customer[num]<3000)
  {
    for(unsigned j=0; j<5; j++)
    {
      if(customer[num]<3000)\
      {
        pthread_mutex_lock(&mut[j]);
        if(magazine[j]!=0)
        {
          customer[num]+=magazine[j];
          //magazine[j]=0;
          count[num]++;
          printf("cutomer[%d] bougth: %d; NUM OF BUY=%d\n", num, magazine[j], count[num]);
          magazine[j]=0;
        }
        pthread_mutex_unlock(&mut[j]);
        sleep(1);
      }
    }
  }
  //printf("customer[%d]=%d, count[%d]=%d\n", num, customer[num], num, count);
  pthread_exit(&tid[num]);
}

void loader(/*void* params*/)
{
  //while(customer[0]<3000 && customer[1]<3000 && customer[2]<3000)
  while(customer[0]<3000 || customer[1]<3000 || customer[2]<3000)
  {
    for(unsigned i=0; i<5; i++)
    {
      if(magazine[i]==0)
      {
        pthread_mutex_lock(&mut[i]);
        magazine[i]=rand() % 100+450;
        //printf("%d\n", magazine[i]);
        pthread_mutex_unlock(&mut[i]);
        sleep(1);
      }
    }
  }
  pthread_exit(&tid[3]);
  /*
  for(unsigned i=0; i<5; i++)
  {
    pthread_mutex_lock(&mut[i]);

    pthread_mutex_unlock(&mut[i]);
  }
  */
  
}

int main(void)
{
  //pthread_t tid[4];
  for(unsigned i=0; i<5; i++)
    pthread_mutex_init(&mut[i], NULL);
  
  count[0]=0;
  count[1]=0;
  count[2]=0;
  pthread_create(&tid[3], NULL, (void*)loader, NULL);
  pthread_create(&tid[0], NULL, (void*)customers, (int*)0);
  pthread_create(&tid[1], NULL, (void*)customers, (int*)1);
  pthread_create(&tid[2], NULL, (void*)customers, (int*)2);
  

  pthread_join(tid[3], NULL);
  printf("END: customer[%d]=%d\n", 0, customer[0]);
  printf("END: customer[%d]=%d\n", 1, customer[1]);
  printf("END: customer[%d]=%d\n", 2, customer[2]);

  //printf("Hello!\n");
  return 0;
}


