
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mini-os/xmalloc.h>
#include <mini-os/sched.h>



void *f1(void *x){
  printf("f1");
  pthread_exit(0);
}

/* void *f2(int *x){ */
/*   int i; */
/*   i = *x; */
/*   /\* sleep(1); *\/ */
/*   printf("f2: %d",i); */
/*   pthread_exit(0);  */
/* } */
  


void my_main(void){

  printf("\n Test Print\n");

  pthread_t f1_thread;


  /* void *f1(); */
  int i1,i2;
  i1 = 1;
  i2 = 2;
  pthread_create(&f1_thread,NULL,f1,&i1);
  /* pthread_create(&f2_thread,NULL,f2,&i2); */
}


void my_thread(void *p){
  char d;
  printf("Enter a char, Press Enter: ");
  scanf("%c",&d);
  printf("\nscanned value: %c\n",d);
}

