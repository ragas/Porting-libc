#include <pthread.h>
#include <pthread_local.h>
#include <mini-os/os.h>
#include <mini-os/xmalloc.h>
#include <unistd.h>
extern pthread_t background_thread;

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
  

  local_irq_restore(flags);
  *thread = newthread; 

  
  return 0;
}




static int waiting_for_thread = 0;

void *f_sched(void *p){
  
  printk("Scheduling Thread");

  if (waiting_for_thread)
  while (1){
    schedule();
  }
    return NULL;
}


int scan_threads(pthread_t thread){

  
  struct thread *checkthread;
  struct minios_list_head *iterator, *next_iterator;


  minios_list_for_each_safe(iterator, next_iterator, &idle_thread->thread_list)
    
    {
      checkthread = minios_list_entry(iterator, struct thread, thread_list);
      if (checkthread == thread){
	schedule();
	return -1;
      }
    }
  return 0;
}

int pthread_join(pthread_t thread, void **valptr)
{
  
  while ( scan_threads(thread) != 0)
    schedule();
 
    /* printk("END JOIN\n"); */
  return 0;
}

