CC = gcc
CFLAGS = -fno-builtin -Wall -Werror -Wredundant-decls -Wno-format -Wno-redundant-decls   -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Winline -nostdinc -nostdlib -I../include -I../arch/amd64 -I../include/sys -c

default: libc mini-os
	cd libc;make
	cd mini-os;make bsdlibc=y