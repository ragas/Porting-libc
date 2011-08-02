CC = gcc
DEF_CFLAGS += -fno-builtin -Wall -Werror -Wredundant-decls -Wno-format -Wno-redundant-decls
DEF_CFLAGS += $(call cc-option,$(CC),-fno-stack-protector,)
DEF_CFLAGS += $(call cc-option,$(CC),-fgnu89-inline)
DEF_CFLAGS += -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Winline
DEF_CFLAGS += -nostdinc -nostdlib
DEF_CFLAGS += -I../include -I../arch/amd64 -I../include/sys

OBJS := unithread_malloc_lock.c  unithread_tag.c

default: .
	$(CC) $(DEF_CFLAGS) -c $(OBJS)