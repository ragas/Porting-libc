#include <pthread.h>
#include <pthread_local.h>
#include <mini-os/os.h>
#include <mini-os/xmalloc.h>
#include <unistd.h>

#include <list.h>
extern struct minios_list_head exited_threads;
static int __pthread_start;

extern void print_runqueue(void);
int pthread_init(void);

int pthread_init(){
  struct thread *thread;
  int count = 0;
    struct minios_list_head *it;
    struct thread *th;
    minios_list_for_each(it, &idle_thread->thread_list)
    {
        th = minios_list_entry(it, struct thread, thread_list);
	if (is_runnable(th)) count++;
        printk("   Thread \"%s\", runnable=%d\n", th->name, is_runnable(th));
    }

    struct minios_list_head *iterator;//, *next_iterator;
    minios_list_for_each(iterator, &exited_threads)
      
      {
	thread = minios_list_entry(iterator, struct thread, thread_list);
	printk("EXITED: %s\n",thread->name);
      }
    

    printk("Count:%d\n",count);
    if (count > 2)
      return 1;
    else{
      __pthread_start = 1;
      return 0;
    }
}


int pthread_attr_init(pthread_attr_t *attr)
{

	/* attr->pta_magic = PT_ATTR_MAGIC; */
  (*attr)->flags = 0;


  return 0;
}


int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*startfunc)(void *), void *arg)
{

  pthread_t newthread;
  pthread_attr_t newattr;
  unsigned long flags;

  if(attr == NULL){
    newattr = malloc(sizeof(pthread_attr_t));
    pthread_attr_init(&newattr);
  }
  else
    newattr = *attr;

  
  newthread = arch_create_thread("pthread", (void *)startfunc, arg);

  /* pthread_init(); */


  /*  newthread->thread_list = &thread->thread_list;  */
  /* _thread = &newthread; */
  /* printk("----->%x,%x,%x\n",&thread->thread_list,(*_thread)->thread_list,newthread->thread_list); */
  /* printk("%s\n",(*_thread)->name); */
  newthread->flags = 0;
  newthread->wakeup_time = 0LL;
  
  set_runnable(newthread);

  local_irq_save(flags);
 
  minios_list_add_tail(&newthread->thread_list, &idle_thread->thread_list); 
  
  newthread->join_list = NULL;
  local_irq_restore(flags);
  *thread = newthread; 

  
  return 0;
}

/* static int waiting_for_thread = 0; */

/* void *f_sched(void *p){ */
  
/*   printk("Scheduling Thread"); */

/*   if (waiting_for_thread) */
/*   while (1){ */
/*     schedule(); */
/*   } */
/*     return NULL; */
/* } */


/* int scan_threads(pthread_t thread){ */

  
/*   struct thread *checkthread; */
/*   struct minios_list_head *iterator, *next_iterator; */


/*   minios_list_for_each_safe(iterator, next_iterator, &idle_thread->thread_list) */
    
/*     { */
/*       checkthread = minios_list_entry(iterator, struct thread, thread_list); */
/*       if (checkthread == thread){ */
/* 	schedule(); */
/* 	return -1; */
/*       } */
/*     } */
/*   return 0; */
/* } */

int pthread_join(pthread_t thread, void **valptr)
{
  
  pthread_t cur_thread;
  cur_thread = current;

  if( thread->join_list == NULL){
    thread->join_list = malloc(sizeof(struct thread));

    thread->join_list->flags = 0;
    thread->join_list->thread_list.prev = &thread->join_list->thread_list;
    thread->join_list->thread_list.next = &thread->join_list->thread_list;

  }

  /* block the calling thread, add it to waiting threads join_list */
  unsigned long flags;
  local_irq_save(flags);
   
  minios_list_del(&cur_thread->thread_list);
  clear_runnable(cur_thread);

  minios_list_add(&cur_thread->thread_list, &thread->join_list->thread_list);
  local_irq_restore(flags);
  schedule();
  return 0;
}



int pthread_mutex_lock(pthread_mutex_t *mutex){
 
 pthread_t thread;

 thread = current;
   
 if(*mutex == NULL){
   /* printk("LOCK Mutex %x, thread: thread %x\n",*mutex,thread);   */
   *mutex = (struct pthread_mutex*)malloc(sizeof(struct pthread_mutex)); 


   (*mutex)->m_owner = current;
   (*mutex)->m_blocked = malloc (sizeof (struct thread));
   (*mutex)->m_blocked->flags = 0;
   (*mutex)->m_blocked->thread_list.next = &(*mutex)->m_blocked->thread_list;
   (*mutex)->m_blocked->thread_list.prev = &(*mutex)->m_blocked->thread_list;

   /* printk("LOCK Mutex %x, thread: thread %x\n",*mutex,thread);   */
  }

 else {
   /* printk("LOCK Mutex %x, Called by: %x Already Acq by %x \n",*mutex, thread,(*mutex)->m_owner);    */
   if (thread != (*mutex)->m_owner){
     unsigned long flags;
     local_irq_save(flags);
   
     minios_list_del(&thread->thread_list);
     clear_runnable(thread);
   
     minios_list_add(&thread->thread_list, &(*mutex)->m_blocked->thread_list); 
     local_irq_restore(flags);

     /* printk("lock %x\n",thread); */


   }
   schedule(); 
   
 }

 return 0;

}

int pthread_mutex_unlock(pthread_mutex_t *mutex){

  /* struct minios_list_head *it; */
  pthread_t thread,th;
  struct minios_list_head *it,*it_2;
  thread = current;
  

  /* printk("UNLOCK Mutex %x, Called by: %x \n",*mutex,thread); */
  if(*mutex == NULL) return 1;

  /* printk("UNLOCK Mutex %x, Called by: %x Already Acq by %x \n",*mutex,thread,(*mutex)->m_owner);     */


  unsigned long flags;
  local_irq_save(flags);


  minios_list_for_each_safe(it,it_2, &(*mutex)->m_blocked->thread_list)
    {
        th = minios_list_entry(it, struct thread, thread_list);

	minios_list_del(&th->thread_list);
	minios_list_add(&th->thread_list, &idle_thread->thread_list);
	set_runnable(th);

    }
   
  local_irq_restore(flags);
  free(*mutex); 
  *mutex = NULL; 
  
  schedule();  

  /*  pthread_t thread,wake_up; */
  /* thread = current; */
  /* struct minios_list_head *it, *n; */

  /* printk("Mutex UnLock: thread %x\n",thread); */
 
  /* minios_list_for_each_safe(it,n, &(*mutex)->m_blocked->thread_list) */
  /*   { */
  /*     printk("blocked on : %x\n",it); */
  /*     wake_up = minios_list_entry(it,struct thread, thread_list); */
  /*     wake(wake_up); */
     
  /*   } */
 
  /* free(*mutex);  */

  return 0;
}

void	pthread_exit(void *unused){
  exit_thread();
}
