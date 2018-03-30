#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
# define size 5

pthread_mutex_t mutex;
pthread_t t_prod[10],t_cons[10],t_test;
sem_t s_full,s_empty;

int count=0;
int list[size];

void *producer(void *x ){
  printf("\nEnter the number to be produced : ");
  int ins;
  scanf("%d",&ins);
  /* For test case if want to check that we can run more producer
  pthread_create(&t_test,NULL,producer,NULL);
  pthread_join(t_test,NULL);   */
  sem_wait(&s_empty);
  pthread_mutex_lock(&mutex);
  printf("\nItem produced is %d\n",ins );
  list[count++]=ins;
  pthread_mutex_unlock(&mutex);
  sem_post(&s_full);
  pthread_exit(NULL);
}

void *consumer(void *x)
{
  int del;
  sem_wait(&s_full);
  pthread_mutex_lock(&mutex);
  del=list[--count];
  // pthread_create(&t_test,NULL,producer,NULL);
  // pthread_join(t_test,NULL);
  printf("Item consumed is %d\n",del);
  pthread_mutex_unlock(&mutex);
  sem_post(&s_empty);
  pthread_exit(NULL);
}

void main (){
  sem_init(&s_full,0,0);
  sem_init(&s_empty,0,5);
  int i,j;
  printf("\nHow many items would you like to produce :  ");
  scanf("%d",&i);
  for(int x=0;x<i;x++)
  {
  pthread_create(&t_prod[x],NULL,producer,NULL);
  sleep(3);
  }
  for(int x=0;x<i;x++)
  {
  pthread_join(t_prod[x],NULL);
  }
  printf("\nHow many items woudld you like to consume :  ");
  scanf("%d",&j);
  
  for(int x=0;x<j;x++)
  {  
  if(x>i){
  printf("\nCannot Consume Items more than Produced So exiting Now...\n");
  break;
  }
  pthread_create(&t_cons[x],NULL,consumer,NULL);
  sleep(1);
  }
  for(int x=0;x<j;x++)
  {
  pthread_join(t_cons[x],NULL);
  }
}
