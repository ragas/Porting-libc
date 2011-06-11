#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stdarg.h>
#include <stddef.h>
#include <xen/xen.h>
#include <xen/event_channel.h>
#include "gntmap.h"

#include <stdio.h>
#include <string.h>

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


