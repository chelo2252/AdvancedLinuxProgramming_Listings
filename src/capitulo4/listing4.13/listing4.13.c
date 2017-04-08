#include <unistd.h>
#include <pthread.h>
#include <stdio.h>


void do_work () {
  printf("%s\n", "working...");
}

int counter = 0;
int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag ()
{
  pthread_mutex_init (&thread_flag_mutex, NULL);
  thread_flag = 1;
}

/* Sets the value of the thread flag to FLAG_VALUE.  */

void set_thread_flag (int flag_value)
{
  /* Protect the flag with a mutex lock.  */
  pthread_mutex_lock (&thread_flag_mutex);
  thread_flag = flag_value;
  pthread_mutex_unlock (&thread_flag_mutex);
}

/* Calls do_work repeatedly while the thread flag is set; otherwise
   spins.  */

void* thread_function (void* thread_arg)
{
  while (1) {
    int flag_is_set;

    /* Protect the flag with a mutex lock.  */
    pthread_mutex_lock (&thread_flag_mutex);
    flag_is_set = thread_flag;
    pthread_mutex_unlock (&thread_flag_mutex);

    if (flag_is_set && counter < 10) {
      do_work ();
      counter++;
    } else {
        set_thread_flag (0);
    }
  }
  return NULL;
}



int main() 
{
  pthread_t thread_id;

  initialize_flag();

  pthread_create (&thread_id, NULL, &thread_function, NULL);
    
  /* Make sure the thread has finished.  */
  pthread_join (thread_id, NULL);
  
  return 0;
}