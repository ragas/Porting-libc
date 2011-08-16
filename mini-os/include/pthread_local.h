#ifndef _PTHREAD_LOCAL_H
#define _PTHREAD_LOCAL_H

#include <pthread.h>
#include <list.h>
struct pthread_attr {
	int	flags;
	void	*arg_attr;
};

#define pthread thread;


struct pthread_mutex {
  struct thread*  m_owner;
  struct thread* m_blocked;
  /* struct minios_list_head m_blocked; //threads blocked because of mutex  */
};


#endif
