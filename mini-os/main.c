
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void my_main(void);

void *my_thread(void *p);
void *_background_thread(void *x);

void *_background_thread(void *x){
  printf("INSIDE SECOND THREAD\n");
  
   
  return NULL;
}

void *f2(void *x){

  sleep(5);
  printf("\n\n\n\n\n\n\n\n\n\n\n");
  pthread_t background_thread,some_thread;
  printf("\n&&&&&&&\nInside FIRST Thread\n&&&&&&&\n");

  pthread_create(&background_thread,NULL,_background_thread,NULL);
  pthread_join(background_thread,NULL) ;

  pthread_create(&some_thread,NULL,my_thread,NULL);
  pthread_join(some_thread,NULL) ;

  pthread_create(&background_thread,NULL,_background_thread,NULL);
  pthread_join(background_thread,NULL) ;

  return NULL;
}


void *my_thread(void *p){
  int d;
  printf("In thread my_thread \n Enter a Number, Press Enter: ");
  scanf("%d",&d);
  printf(" %d\n",d);
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

