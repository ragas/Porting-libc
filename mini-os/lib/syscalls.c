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
#include <signal.h>
#include <poll.h>
#include <sys/socket.h>

#include <sys/resource.h>

#include <sys/param.h>
#include <sys/mount.h>
#include<sys/stat.h> /* for fstat etc functions*/

void printk(const char *fmt, ...);

/* void _exit(int status) */
/* { */
/*   /\* How should this work? *\/ */
/*   do_exit(); */
/*   stop_kernel(); */
/* } */

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
  printk("UNIMP_function_malloc\n"); 
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

/* #define NOFILE 32 */
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
  printk("syscall_*mmap");
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

pid_t getpid(void)
{
    printk("GETPID\n");
    return 1;
}

pid_t getppid(void)
{

    return 1;
}

pid_t setsid(void)
{
  printk("SETSID\n");
    return 0;
}


/***********
for threading
***********/

int     _thread_sys_close(int t){
  return 0;
}

int _thread_sys_fcntl(int fd, int cmd, ...){
  return 0;

}


void	_thread_sys__exit(int t) {
}

pid_t	_thread_sys_getpid(void) {
  return 1;
}

int     _thread_sys_dup2(int oldfd, int newfd) {
  return 0;
}

int     _thread_sys_ioctl(int d, unsigned long request, ...){

  return 0;
}

int     _thread_sys_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact){
  return 0;
}

int     _thread_sys_sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
  return 0;
}

ssize_t _thread_sys_read(int fd , void *buf, size_t count){
  return 0;
}
ssize_t _thread_sys_write(int fd, const void *buf, size_t count){
  return 0;
}

int     _thread_sys_open(const char *pathname, int flags, ...){
  printk("_SYS_OPEN\n");
  int fd ;
  fd = alloc_fd(FTYPE_CONSOLE);
  return fd;
}

int     _thread_sys_pipe(int *pipefd){
  return 0;
}

int 	_thread_sys_poll(struct pollfd *fds, unsigned nfds, int timeout){
  return 0;

}

pid_t   _thread_sys_fork(void){
  return 0;
}

pid_t   _thread_sys_vfork(void){
  return 0;
}

int     _thread_sys_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){

  return 0;
}

int     _thread_sys_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  return 0;
}


int     _thread_sys_dup(int oldfd){
  return 0;
}

int     _thread_sys_closefrom(int x){
  return 0;
}

int     _thread_sys_execve(const char *filename, char * const *argv, char * const *envp){
  return 0;
}

int     _thread_sys_fchflags(int x, unsigned int y){
  return 0;

}

int     _thread_sys_fchmod(int fd, mode_t mode){
  return 0;
}

int     _thread_sys_fchown(int fd, uid_t owner, gid_t group){
  return 0;
}

int     _thread_sys_flock(int fd, int operation){
  return 0;
}

long	_thread_sys_fpathconf(int fd, int name){
  return 0;
}

int     _thread_sys_fsync(int fd){
  return 0;
}

int     _thread_sys_fstatfs(int fd, struct statfs *buf){
  return 0;
}

int     _thread_sys_getdirentries(int fd, char *buf, int nbytes, off_t *basep){
  return 0;
}

int     _thread_sys_getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
  return 0;
}

int     _thread_sys_getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
  return 0;
}

int     _thread_sys_getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen){
  return 0;
}

int     _thread_sys_listen(int sockfd, int backlog){
  return 0;
}


ssize_t _thread_sys_readv(int fd, const struct iovec *iov, int iovcnt){
  return 0;
}


ssize_t _thread_sys_writev(int fd, const struct iovec *iov, int iovcnt){
  return 0;
}

int setitimer(int which, const struct itimerval *new_value,
	      struct itimerval *old_value){

  return 0;
}

int sigismember(const sigset_t *set, int signum){
  return 0;
}

void *calloc(size_t nmemb, size_t size){

  return NULL;
}

char *getenv(const char *name){
  return NULL;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp){

  return 0;

}

int revoke(const char *path){

  return 0;
}

int  setlogin(const char *name){
  printk("SETLOGIN");
  return 0;
}

int sigaddset(sigset_t *set, int signum){

  return 0;
}

int getrlimit(int resource, struct rlimit *rlim){

  return 0;
}

int sigdelset(sigset_t *set, int signum){
  return 0;
}

int msync(void *addr, size_t length, int flags){
  return 0;

}

unsigned int sleep(unsigned int seconds){
  return 0;
}


int _thread_sys_fstat(int fd, struct stat *buf){

  return 0;
}
