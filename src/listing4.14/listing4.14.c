#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

extern void do_work ();

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void initialize_flag ()
{
  /* Initialize the mutex and condition variable.  */
  pthread_mutex_init (&thread_flag_mutex, NULL);
  pthread_cond_init (&thread_flag_cv, NULL);
  /* Initialize the flag value.  */
  thread_flag = 0;
}

/* Calls do_work repeatedly while the thread flag is set; blocks if
   the flag is clear.  */

void* thread_function (void* thread_arg)
{
  /* Loop infinitely.  */
  while (1) {
    /* Lock the mutex before accessing the flag value.  */
    pthread_mutex_lock (&thread_flag_mutex);
    while (!thread_flag) 
      /* The flag is clear.  Wait for a signal on the condition
	 variable, indicating the flag value has changed.  When the
	 signal arrives and this thread unblocks, loop and check the
	 flag again.  */
      pthread_cond_wait (&thread_flag_cv, &thread_flag_mutex);
    /* When we've gotten here, we know the flag must be set.  Unlock
       the mutex.  */
    pthread_mutex_unlock (&thread_flag_mutex);
    /* Do some work.  */
    do_work ();
  }
  return NULL;
}

/* Sets the value of the thread flag to FLAG_VALUE.  */

void set_thread_flag (int flag_value)
{
  /* Lock the mutex before accessing the flag value.  */
  pthread_mutex_lock (&thread_flag_mutex);
  /* Set the flag value, and then signal in case thread_function is
     blocked, waiting for the flag to become set.  However,
     thread_function can't actually check the flag until the mutex is
     unlocked.  */
  thread_flag = flag_value;
  pthread_cond_signal (&thread_flag_cv);
  /* Unlock the mutex.  */
  pthread_mutex_unlock (&thread_flag_mutex);
}

/*funcion del thread que maneja cuando setear la bandera
  a modo de prueba, se duerme el thread durante cada seteo
  para poder ver la funcionalidad de la variable de condition*/
void* flag_manager(void* arg){
  while(1){
    set_thread_flag(1);
    sleep(2);    
    set_thread_flag(0);
    sleep(5);
  }
}

void do_work(){
  printf("%s\n", "Haciendo algo");
}

int main(){
  initialize_flag();

  pthread_t thread_fm;
  pthread_create(&thread_fm,NULL,&flag_manager,NULL);

  int tamanho = 5;
  pthread_t threads[tamanho];

  for(int i = 0 ; i < tamanho ; i++)
    pthread_create(&(threads[i]),NULL,&thread_function,NULL);
  
  pthread_join(thread_fm,NULL);

  for(int i = 0 ; i < tamanho ; i++)
    pthread_join(threads[i],NULL);

  return 0;
}
