CC = gcc
DEF_CFLAGS += -fno-builtin -Wall -Werror -Wredundant-decls -Wno-format -Wno-redundant-decls
DEF_CFLAGS += $(call cc-option,$(CC),-fno-stack-protector,)
DEF_CFLAGS += $(call cc-option,$(CC),-fgnu89-inline)
DEF_CFLAGS += -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Winline
DEF_CFLAGS += -nostdinc -nostdlib
DEF_CFLAGS += -I ../../libc/include -I../include -I../../libc/arch/amd64 -I../../libc/include/sys  -I../uthread/ -I../arch/amd64/ 
DEF_CFLAGS += -D_THREAD_SAFE -D_ANSI_LIBRARY

OBJS := uthread_create.c \
	uthread_join.c	\
	uthread_fd.c \
 uthread_exit.c \
 uthread_kern.c \
 uthread_stack.c \
 uthread_gc.c \
 uthread_priority_queue.c \
 uthread_fcntl.c \
uthread_init.c \
uthread_mutex.c \
uthread_clean.c \
uthread_fork.c \
sched_prio.c \
uthread_accept.c \
uthread_atfork.c \
uthread_attr_destroy.c \
uthread_attr_getdetachstate.c \
uthread_attr_getguardsize.c \
uthread_attr_getinheritsched.c \
uthread_attr_getschedparam.c \
uthread_attr_getschedpolicy.c \
uthread_attr_getscope.c \
uthread_attr_getstackaddr.c \
uthread_attr_getstack.c \
uthread_attr_getstacksize.c \
uthread_attr_init.c \
uthread_attr_setcreatesuspend_np.c \
uthread_attr_setdetachstate.c \
uthread_attr_setguardsize.c \
uthread_attr_setinheritsched.c \
uthread_attr_setprio.c \
uthread_attr_setschedparam.c \
uthread_attr_setschedpolicy.c \
uthread_attr_setscope.c \
uthread_attr_setstackaddr.c \
uthread_attr_setstack.c \
uthread_attr_setstacksize.c \
uthread_autoinit.c \
uthread_bind.c \
uthread_cancel.c \
uthread_closefrom.c \
uthread_close.c \
uthread_concurrency.c \
uthread_condattr_destroy.c \
uthread_condattr_init.c \
uthread_cond.c \
uthread_detach.c \
uthread_dup2.c \
uthread_dup.c \
uthread_equal.c \
uthread_execve.c \
uthread_fchflags.c \
uthread_fchmod.c \
uthread_fchown.c \
uthread_file.c \
uthread_find_thread.c \
uthread_flock.c \
uthread_fpathconf.c \
uthread_fstatfs.c \
uthread_fstat.c \
uthread_fsync.c \
uthread_getdirentries.c \
uthread_getpeername.c \
uthread_getprio.c \
uthread_getschedparam.c \
uthread_getsockname.c \
uthread_getsockopt.c \
uthread_info_openbsd.c \
uthread_ioctl.c \
uthread_kill.c \
uthread_listen.c \
uthread_lseek.c \
uthread_main_np.c \
uthread_mattr_init.c \
uthread_mattr_kind_np.c \
uthread_msync.c \
uthread_multi_np.c \
uthread_mutexattr_destroy.c \
uthread_mutex_prioceiling.c \
uthread_mutex_protocol.c \
uthread_nanosleep.c \
uthread_once.c \
uthread_open.c \
uthread_pipe.c \
uthread_poll.c \
uthread_read.c \
uthread_readv.c \
uthread_recvfrom.c \
uthread_recvmsg.c \
uthread_resume_np.c \
uthread_rwlockattr.c \
uthread_rwlock.c \
uthread_select.c \
uthread_self.c \
uthread_sem.c \
uthread_sendmsg.c \
uthread_sendto.c \
uthread_seterrno.c \
uthread_setprio.c \
uthread_setschedparam.c \
uthread_setsockopt.c \
uthread_shutdown.c \
uthread_sigaction.c \
uthread_sigblock.c \
uthread_sigmask.c \
uthread_signal.c \
uthread_sig.c \
uthread_sigpending.c \
uthread_sigprocmask.c \
uthread_sigsetmask.c \
uthread_sigsuspend.c \
uthread_sigwait.c \
uthread_single_np.c \
uthread_spec.c \
uthread_spinlock.c \
uthread_stackseg_np.c \
uthread_suspend_np.c \
uthread_switch_np.c \
uthread_vfork.c \
uthread_wait4.c \
uthread_write.c \
uthread_writev.c \
uthread_yield.c \
uthread_connect.c \
uthread_socket.c \
uthread_socketpair.c 


default: .
	rm -f *.o
	$(CC) $(DEF_CFLAGS) -c $(OBJS)
	ar r ../libpthread.a *.o
