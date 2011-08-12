#ifndef _PTHREAD_LOCAL_H
#define _PTHREAD_LOCAL_H


struct pthread_attr {
	int	flags;
	void	*arg_attr;
};

#define pthread thread;
/* struct pthread { */
/*   char *name; */
/*   struct minios_list_head* thread_list; */
/* }; */
#endif
