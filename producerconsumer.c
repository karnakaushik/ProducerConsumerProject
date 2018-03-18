#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

pthread_mutex_t mutex;
pthread_t t_prod,t_cons;
sem_t s_full,s_empty;
int size=5;

int count=0;
int list[5];

void *producer(void *x ){
  int ins=5;
  sem_wait(&s_empty);
  pthread_mutex_lock(&mutex);
  printf("Item produced is %d\n",ins );
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
  pthread_create(&t_prod,NULL,producer,NULL);
  pthread_join(t_prod,NULL);
  pthread_create(&t_cons,NULL,producer,NULL);
  pthread_join(t_cons,NULL);
}
