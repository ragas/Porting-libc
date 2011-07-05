#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stdarg.h>
#include <stddef.h>
#include <xen/xen.h>
#include <xen/event_channel.h>
#include "gntmap.h"
#include <mini-os/console.h>
#include <mini-os/xenbus.h>

#include <stdio.h>
#include <string.h>

#define RAND_MIX 2654435769U
int rand(void);

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define ASSERT(x)                                              \
do {                                                           \
	if (!(x)) {                                                \
		printk("ASSERTION FAILED: %s at %s:%d.\n",             \
			   # x ,                                           \
			   __FILE__,                                       \
			   __LINE__);                                      \
        BUG();                                                 \
	}                                                          \
} while(0)

#define BUG_ON(x) ASSERT(!(x))


enum fd_type {
    FTYPE_NONE = 0,
    FTYPE_CONSOLE,
    FTYPE_FILE,
    FTYPE_XENBUS,
    FTYPE_XC,
    FTYPE_EVTCHN,
    FTYPE_GNTMAP,
    FTYPE_MEM
};

extern struct file {
  enum fd_type type;
  union {
    struct gntmap gntmap;
    struct {
      struct consfront_dev *dev;
    } cons;
    struct {
      /* To each xenbus FD is associated a queue of watch events for this
       * FD.  */
      xenbus_event_queue events;
    } xenbus;
  };
  int read;	/* maybe available for read */
} files[];

int alloc_fd(enum fd_type type);
#endif


