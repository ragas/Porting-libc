
#include <stdio.h>
#include <stdlib.h>
#include <mini-os/xmalloc.h>

int my_main(void){

  int d;
  int *c;
  c = (int*)malloc(sizeof(int));
  *c = 1;
  printf("\n %x:%d;; Successfully printed using BSD LIBC\n",c,*c);
  scanf ("%d",&d);
  printf("\nscanned value: %d");
  return 0;
}
