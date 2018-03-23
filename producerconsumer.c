#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

pthread_mutex_t mutex;
pthread_t t_prod[10],t_cons[10];
sem_t s_full,s_empty;

int count=0;
int list[5];

void *producer(void *x ){
  printf("\nEnter the number to be produced : ");
  int ins;
  scanf("%d",&ins);
  sem_wait(&s_empty);
  pthread_mutex_lock(&mutex);
  printf("\nItem produced is %d\n",ins );
  list[count++]=ins;
  pthread_mutex_unlock(&mutex);
  sem_post(&s_full);
}

void *consumer(void *x)
{
  int del;
  sem_wait(&s_full);
  pthread_mutex_lock(&mutex);
  del=list[--count];
  printf("Item consumed is %d\n",del);
  pthread_mutex_unlock(&mutex);
  sem_post(&s_empty);
}

void main (){
  sem_init(&s_full,0,0);
  sem_init(&s_empty,0,5);
  int i,j;
  printf("\nHow many items would you like to produce :  ");
  scanf("%d",&i);
  printf("\nHow many items woudld you like to consume :  ");
  scanf("%d",&j);
  for(int x=0;x<i;x++)
  {
  pthread_create(&t_prod[x],NULL,producer,NULL);
  }
  for(int x=0;x<i;x++)
  {
  pthread_join(t_prod[x],NULL);
  }
  for(int x=0;x<j;x++)
  {  
  pthread_create(&t_cons[x],NULL,consumer,NULL);
  }
  for(int x=0;x<j;x++)
  {
  pthread_join(t_cons[x],NULL);
  }
}
