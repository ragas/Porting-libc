CC = gcc
DEF_CFLAGS += -fno-builtin -Wall -Werror -Wredundant-decls -Wno-format -Wno-redundant-decls
DEF_CFLAGS += $(call cc-option,$(CC),-fno-stack-protector,)
DEF_CFLAGS += $(call cc-option,$(CC),-fgnu89-inline)
DEF_CFLAGS += -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Winline
DEF_CFLAGS += -nostdinc -nostdlib
DEF_CFLAGS += -I../include -I../arch/amd64 -I../include/sys


default: stdio gen locale libstubs arch string stdlib thread
	cd stdio; make
	cd gen; make
	cd locale;make
	cd libstubs;make
	cd arch/amd64/string;make
	cd string;make
	cd stdlib;make
	cd thread;make
	ar r libc.a stdio/*.o
	ar r libc.a gen/*.o
	ar r libc.a locale/*.o
	ar r libc.a libstubs/*.o
	ar r libc.a arch/amd64/string/*.o
	ar r libc.a string/*.o
	ar r libc.a stdlib/*.o
	ar r libc.a thread/*.o