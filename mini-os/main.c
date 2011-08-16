
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void my_main(void);
void *f2(void *x);
/* void *thread_1(void *p); */
/* void *thread_2(void *x); */

/* pthread_mutex_t my_mutex  = PTHREAD_MUTEX_INITIALIZER; */

/* void *mutex_tester_one(void *notused){ */
/*   int d=1; */

/*   printf("mutex_one_start %x\n",&my_mutex); */
/*   pthread_mutex_lock(&my_mutex); */
/*   printf("LOCKED By 1\n"); */

/*   scanf("%d",&d); */
  
/*   pthread_mutex_unlock(&my_mutex); */
/*     printf("mutex_1_unlocked\n"); */
/*   return NULL; */
/* } */

/* void *mutex_tester_two(void *notused){ */
/*   int d=1; */

/*   printf("mutex_2_start\n"); */
/*   pthread_mutex_lock(&my_mutex); */
/*   printf("LOCKED BY 2\n"); */

/*   scanf("%d",&d); */
/*   pthread_mutex_unlock(&my_mutex); */
/*   printf("mutex_2_unlock\n"); */
/*   return NULL; */
/* } */


/* void *thread_2(void *x){ */
/*   printf("INSIDE SECOND THREAD\n"); */
  
   
/*   return NULL; */
/* } */


/* void *thread_1(void *p){ */
/*   int d; */
/*   printf("In thread my_thread \n Enter a Number, Press Enter: "); */
/*   scanf("%d",&d); */
/*   printf(" %d\n",d); */
/*   return NULL; */
/* } */


/* void *f2(void *x){ */


/*   printf("\n\n\n\n\n\n\n\n\n\n\nSleeping for 5 sec\n"); */
/*   /\* sleep(5); *\/ */
/*   pthread_t p_thread_1,p_thread_2; */
/*   printf("\n&&&&&&&\nInside FIRST Thread\n&&&&&&&\n"); */

/*   pthread_create(&p_thread_1,NULL,thread_1,NULL); */
/*   pthread_join(p_thread_1,NULL) ; */

/*   pthread_create(&p_thread_2,NULL,thread_2,NULL); */
/*   pthread_join(p_thread_2,NULL) ; */


/*   pthread_create(&p_thread_1,NULL,mutex_tester_one,NULL); */


/*   pthread_create(&p_thread_2,NULL,mutex_tester_two,NULL); */

/*   return NULL; */
/* } */


void  my_main(){

   /* printf("\n Test Print\n"); */
   pthread_t f2_thread;//,f1_thread;


   pthread_create(&f2_thread,NULL,f2,NULL);

   /* pthread_join(f2_thread,NULL); */

   /* printf("##########\n"); */
   /* pthread_create(&f1_thread,NULL,my_thread,NULL); */

   /* pthread_join(f1_thread,NULL); */
  
   /* pthread_create(&f2_thread,NULL,f2,NULL); */

   

   /* pthread_join(f2_thread,NULL); */
}

/* #include <sys/time.h> */
/* #include <stdio.h> */
/* #include <pthread.h>  */
/* #include <errno.h> */


void *producer(void*);
void *consumer(void*);
int get_buffer(void);

pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;
int b;  /* buffer size = 1; */

void add_buffer(int i){
  b = i;
}

int get_buffer(){
  return b ;
}

void *producer(void *unused)
{
  int i = 0;
  printf("I'm a producer\n");
  while (1) {

    pthread_mutex_lock(&region_mutex);
    add_buffer(i);
    pthread_mutex_unlock(&region_mutex);
    i = i + 1;
  }
  pthread_exit(NULL);
}

 
void *f2(void *unused)  
{
  pthread_t producer_thread; 
  pthread_t consumer_thread; 
  sleep(2);
    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_join(consumer_thread,NULL);
    return NULL;
}
 
void *consumer( void *unused)
{
  int i,v;
  printf("I'm a consumer\n");
  for (i=0;i<100;i++) {

    pthread_mutex_lock(&region_mutex);
    v = get_buffer();
    pthread_mutex_unlock(&region_mutex);
    printf("got %d  ",v);
  }
  pthread_exit(NULL);
}
