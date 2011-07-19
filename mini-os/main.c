
#include <stdio.h>
#include <stdlib.h>
#include <mini-os/xmalloc.h>
#include <mini-os/sched.h>
void my_main(void){

   printf("\n Test Print\n");
  
}

void my_thread(void *p){
  int d;
  printf("Enter a number, Press Enter: ");
  scanf("%d",&d);
  printf("\nscanned value: %d\n",d);
}

