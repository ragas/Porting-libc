CC := gcc
CFLAGS := -fno-builtin -Wall -Werror -Wredundant-decls -Wno-format -Wno-redundant-decls   -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Winline -nostdinc -nostdlib -I.. -c

OBJS := memset.o memcpy.o memchr.o memmove.o strlen.o 

default: .
	$(CC) $(CFLAGS) memset.S memcpy.S memchr.S memmove.S strlen.S 
