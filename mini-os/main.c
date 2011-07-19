
#include <stdio.h>
#include <stdlib.h>
#include <mini-os/xmalloc.h>
#include <mini-os/sched.h>
void my_main(void){

   printf("\n Test Print\n");
  
}

void my_thread(void *p){
  char d;
  printf("Enter a char, Press Enter: ");
  scanf("%c",&d);
  printf("\nscanned value: %c\n",d);
}

