
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

extern void print_runqueue(void);
void my_main(void);

void *thread_1(void *p);
void *thread_2(void *x);

pthread_mutex_t my_mutex  = PTHREAD_MUTEX_INITIALIZER;

void *mutex_tester_one(void *notused){
  int d=1;

  printf("mutex_one_start %x\n",&my_mutex);
  pthread_mutex_lock(&my_mutex);
  printf("LOCKED By 1\n");

  scanf("%d",&d);
  
  pthread_mutex_unlock(&my_mutex);
    printf("mutex_1_unlocked\n");
  return NULL;
}

void *mutex_tester_two(void *notused){
  int d=1;

  printf("mutex_2_start\n");
  pthread_mutex_lock(&my_mutex);
  printf("LOCKED BY 2\n");

  scanf("%d",&d);
  pthread_mutex_unlock(&my_mutex);
  printf("mutex_2_unlock\n");
  return NULL;
}


void *thread_2(void *x){
  printf("INSIDE SECOND THREAD\n");
  
   
  return NULL;
}


void *thread_1(void *p){
  int d;
  printf("In thread my_thread \n Enter a Number, Press Enter: ");
  scanf("%d",&d);
  printf(" %d\n",d);
  return NULL;
}


void *f2(void *x){


  printf("\n\n\n\n\n\n\n\n\n\n\nSleeping for 5 sec\n");
  /* sleep(5); */
  pthread_t p_thread_1,p_thread_2;
  printf("\n&&&&&&&\nInside FIRST Thread\n&&&&&&&\n");

  pthread_create(&p_thread_1,NULL,thread_1,NULL);
  pthread_join(p_thread_1,NULL) ;

  pthread_create(&p_thread_2,NULL,thread_2,NULL);
  pthread_join(p_thread_2,NULL) ;


  pthread_create(&p_thread_1,NULL,mutex_tester_one,NULL);


  pthread_create(&p_thread_2,NULL,mutex_tester_two,NULL);

  return NULL;
}


void  my_main(){

   printf("\n Test Print\n");
   pthread_t f2_thread;//,f1_thread;


   pthread_create(&f2_thread,NULL,f2,NULL);

   /* pthread_join(f2_thread,NULL); */

   /* printf("##########\n"); */
   /* pthread_create(&f1_thread,NULL,my_thread,NULL); */

   /* pthread_join(f1_thread,NULL); */
  
   /* pthread_create(&f2_thread,NULL,f2,NULL); */

   

   /* pthread_join(f2_thread,NULL); */
}

