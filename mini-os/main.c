
#include <stdio.h>
#include <stdlib.h>
#include <mini-os/xmalloc.h>
#include <mini-os/sched.h>
void my_main(void){

  int d=1;
  int *c;
  c = (int*)malloc(sizeof(int));
  *c = 1;
  printf("\n %x:%d;; Successfully printed using BSD LIBC\n",c,*c);
  /* scanf ("%d",&d); */
  printf("\nscanned value: %d",d);

}

void my_thread(void *p){
  int d;
  scanf("%d",&d);
  printf("\nscanned value: %d\n",d);
}

