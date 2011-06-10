#include<unistd.h>

#include<sys/stat.h> /* for fstat etc functions*/

void _exit(int status)
{
  /* How should this work? */
  for(;;);

}

ssize_t	 read(int fd , void *buf, size_t count)
{
  return -1;
}

ssize_t	 write(int fd, const void *buf, size_t count)
{
  return -1;
}

off_t	 lseek(int fd, off_t offset, int whence)
{
  return -1;
}

int	 close(int fd)
{
  return -1;
}

int malloc(int size)
{
  return -1;
}

/* void *	mmap(void *, size_t, int, int, int, off_t) */
/* { */

/* } */


int	mprotect(void *addr, size_t len, int port)
{
  return -1;
}

int	munmap(void *addr, size_t len)
{

  return -1;
}

int	 isatty(int fd)
{
  return -1;
}

int fstat(int fd, struct stat *buf)
{
  return -1;
}

int	 getpagesize(void)
{
  return -1;
}

void abort(void)
{

}

