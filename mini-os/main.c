
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <xmalloc.h>



void my_main(void);
void *f2(void *x);

void  my_main(){

  
   pthread_t f2_thread;//,f1_thread;


   pthread_create(&f2_thread,NULL,f2,NULL);
}



void *producer(void*);
void *consumer(void*);
int get_buffer(void);

pthread_mutex_t produce_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t consume_mutex = PTHREAD_MUTEX_INITIALIZER;


int b,turn=0;  /* buffer size = 1; */

void add_buffer(int i){
  b = i;
}

int get_buffer(){
  return b ;
}

void *producer(void *unused)
{
  int i = 0,v=0;
printf("I'm a producer\n");
while (v < 20) {
  pthread_mutex_lock(&produce_mutex);

  /* printf("Added %d\n",i); */
  add_buffer(i);
  pthread_mutex_unlock(&consume_mutex);
  /* printf("Unlock consumer mutex\n"); */
  v++;
  i += 1;
}
 return NULL;
/* pthread_exit(NULL); */
}
 
void *f2(void *unused)  
{


  pthread_t producer_thread; 
  pthread_t consumer_thread; 
  sleep(2);
  printf("\n\n\n\n\n\n\n\n");
  printf("********\n");
  printf("Running Example pthread program \n");
  printf("********\n");
  pthread_mutex_lock(&consume_mutex);
    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_join(consumer_thread,NULL);
    return NULL;
}
 
void *consumer( void *unused)
{
int i,v;
printf("I'm a consumer\n");
for (i=0;i<10;i++) {
   pthread_mutex_lock(&consume_mutex);
   v = get_buffer();
   pthread_mutex_unlock(&produce_mutex);
   printf("got %d\n",v);
}

 return NULL;
/* pthread_exit(NULL); */
}
