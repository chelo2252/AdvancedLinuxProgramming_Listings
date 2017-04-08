#include <malloc.h>
#include <pthread.h>
#include <stdio.h>



/* Allocate a temporary buffer.  */

void* allocate_buffer (size_t size)
{
  return malloc (size);
}

/* Deallocate a temporary buffer.  */

void deallocate_buffer (void* buffer)
{
  /*comprobamos que se ejecuta el cleanup handlear de todas maneras*/
  printf("Liberando memoria de thread %d\n", *((int*)pthread_self()));
  free (buffer);
}

void do_some_work ()
{
  /* Allocate a temporary buffer.  */
  void* temp_buffer = allocate_buffer (1024);
  /* Register a cleanup handler for this buffer, to deallocate it in
     case the thread exits or is cancelled.  */
  pthread_cleanup_push (deallocate_buffer, temp_buffer);

  /* Do some work here that might call pthread_exit or might be
     cancelled...  */

  int id = *((int*)pthread_self());
  printf("%d\n", id);
  /*si el thread id es par, salimos del thread*/
  if(id%2 == 0){
    printf("%s %d\n", "saliendo de thread",id);
    pthread_exit(NULL);
  }

  printf("%s\n", "sigo en el thread");

  /* Unregister the cleanup handler.  Since we pass a non-zero value,
     this actually performs the cleanup by calling
     deallocate_buffer.  */
  pthread_cleanup_pop (1);
}

void* thread_work(void* args){  
  do_some_work();
}

int main()
{

  pthread_t thread;

  pthread_create(&thread,NULL,&thread_work,NULL);
  

  pthread_join(thread,NULL);

  return 0;
}
