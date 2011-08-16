#include <os.h>
#include <syscalls.h>
#include <wait.h>

#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
/* #include <net/if.h> */
#include <time.h>
#include <errno.h>
#include <fcntl.h>
/* #include <pthread.h> */
#include <assert.h>
#include <dirent.h>
#include <stdlib.h>
#include <math.h>




#include<sys/stat.h> /* for fstat etc functions*/

void printk(const char *fmt, ...);

void _exit(int status)
{
  /* How should this work? */
  do_exit();
  stop_kernel();
}

ssize_t	 read(int fd , void *buf, size_t count)
{
  /* printk("syscall_read\n"); */
    switch (files[fd].type) {

	case FTYPE_CONSOLE: {

	    int ret;
            DEFINE_WAIT(w);

            while(1) {

                add_waiter(w, console_queue);  

                ret = xencons_ring_recv(files[fd].cons.dev, buf, count);

                if (ret){
		  /* printk("\nRET:%x,%x",ret,&buf);		   */
		  break;}


                schedule();

            }
	    remove_waiter(w); 
            return ret;
        }
        /* case FTYPE_KBD: { */
        /*     int ret, n; */
        /*     n = count / sizeof(union xenkbd_in_event); */
        /*     ret = kbdfront_receive(files[fd].kbd.dev, buf, n); */
	/*     if (ret <= 0) { */
	/* 	/\* errno = EAGAIN; *\/ */
	/* 	return -1; */
	/*     } */
	/*     return ret * sizeof(union xenkbd_in_event); */
        /* } */
	default:
	    break;
    }
    printk("read(%d): Bad descriptor\n", fd);


  return -1;
}

ssize_t	 write(int fd, const void *buf, size_t count)
{
  /* printk("syscall_write"); */

    switch (files[fd].type) {
	case FTYPE_CONSOLE:
	    console_print(files[fd].cons.dev, (char *)buf, count);
	    return count;
	default:
	    break;
    }
    printk("write(%d): Bad descriptor\n", fd);
    /* errno = EBADF; */
    return -1;



}

off_t	 lseek(int fd, off_t offset, int whence)
{
  printk("lseek");
  return -1;
}

int	 close(int fd)
{
  printk("close");
  return -1;
}

void *malloc(size_t size)
{
  /* printk("UNIMP_function_malloc\n"); */
  return NULL;
}

int mprotect(void *addr, size_t len, int port)
{
  /* printk("syscall_mprotect"); */
  return 0; //Always success
}



int munmap(void *addr, size_t len)
{
  printk("munmap");
  return -1;
}

int isatty(int fd)
{
  printk("isatty");
  return -1;
}


static void init_stat(struct stat *buf)
{
    memset(buf, 0, sizeof(*buf));
    buf->st_dev = 0;
    buf->st_ino = 0;
    buf->st_nlink = 1;
    buf->st_rdev = 0;
    buf->st_blksize = 4096;
    buf->st_blocks = 0;
}


int fstat(int fd, struct stat *buf)
{
  /* printk("syscall_fstat"); */
    init_stat(buf);
    switch (files[fd].type) {

	case FTYPE_CONSOLE:
	  {
            if (files[fd].type == FTYPE_CONSOLE)
                buf->st_mode = S_IFCHR|S_IRUSR|S_IWUSR;
            buf->st_uid = 0;
	    buf->st_gid = 0;
	    buf->st_size = 0;
	    buf->st_atime = 
	    buf->st_mtime = 
	      buf->st_ctime = 0;/* time(NULL); */
	    return 0;
	}
	default:
	    break;
    }

    printk("statf(%d): Bad descriptor\n", fd);
    /* errxono = EBADF; */
    return -1;
}


int getpagesize(void)
{
  /* printk("syscall_getpagesize"); */
  return PAGE_SIZE;
}

void abort(void)
{
  printk("abort");
  for(;;);
}

#define NOFILE 32
struct file files[NOFILE] = {
    { .type = FTYPE_CONSOLE }, /* stdin */
    { .type = FTYPE_CONSOLE }, /* stdout */
    { .type = FTYPE_CONSOLE }, /* stderr */
};

int alloc_fd(enum fd_type type)
{
    int i;
    /* pthread_mutex_lock(&fd_lock); */
    for (i=0; i<NOFILE; i++) {
	if (files[i].type == FTYPE_NONE) {
	    files[i].type = type;
	    /* pthread_mutex_unlock(&fd_lock); */
	    return i;
	}
    }
    /* pthread_mutex_unlock(&fd_lock); */
    printk("Too many opened files\n");
    do_exit();
}


void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
{
  /* printk("syscall_*mmap"); */
  unsigned long n = (length + PAGE_SIZE - 1) / PAGE_SIZE;
  
  ASSERT(!start);
  ASSERT(prot == (PROT_READ|PROT_WRITE));
  ASSERT((fd == -1 && (flags == (MAP_SHARED|MAP_ANON) || flags == (MAP_PRIVATE|MAP_ANON)))
	 || (fd != -1 && flags == MAP_SHARED));
  
  if (fd == -1)
    return map_zero(n, 1);
  else if (files[fd].type == FTYPE_XC) {
    unsigned long	zero	  = 0;
    return map_frames_ex(&zero, n, 0, 0, 1, DOMID_SELF, NULL, 0);
  } else if (files[fd].type == FTYPE_MEM) {
    unsigned long	first_mfn = offset >> PAGE_SHIFT;
    return map_frames_ex(&first_mfn, n, 0, 1, 1, DOMID_IO, NULL, _PAGE_PRESENT|_PAGE_RW);
  } else		ASSERT(0);
}

long sysconf(int name)
{
    printk("sysconf");
  return -1;
}

void *realloc(void *ptr, size_t size)
{
  printk("*realloc");
  return NULL;
}

void free(void *ptr)
{
  printk("free");
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    s_time_t start = NOW();
    s_time_t stop = start + SECONDS(req->tv_sec) + req->tv_nsec;
    s_time_t stopped;
    struct thread *thread = get_current();

    thread->wakeup_time = stop;
    clear_runnable(thread);
    schedule();
    stopped = NOW();

    if (rem)
    {
	s_time_t remaining = stop - stopped;
	if (remaining > 0)
	{
	    rem->tv_nsec = remaining % 1000000000ULL;
	    rem->tv_sec  = remaining / 1000000000ULL;
	} else memset(rem, 0, sizeof(*rem));
    }

    return 0;
}

unsigned int sleep(unsigned int seconds)
{
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    if (nanosleep(&req, &rem))
	return -1;

    if (rem.tv_nsec > 0)
	rem.tv_sec++;

    return rem.tv_sec;
}
