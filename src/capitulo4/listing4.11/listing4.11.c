#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

struct job {
  /* Link field for linked list.  */
  struct job* next; 

  int job_number;
};

/* A linked list of pending jobs.  */
struct job* job_queue;

pthread_t thread1_id;
pthread_t thread2_id;

void process_job (struct job* job) 
{
  printf("%s %d\n", "Processing job number", job->job_number);
}

/* A mutex protecting job_queue.  */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Process queued jobs until the queue is empty.  */

void* thread_function (void* arg)
{
  while (1) {
    struct job* next_job;

    /* Lock the mutex on the job queue.  */
    pthread_mutex_lock (&job_queue_mutex);
    
    /* Now it's safe to check if the queue is empty.  */
    if (job_queue == NULL)
      next_job = NULL;
    else {
      /* Get the next available job.  */
      next_job = job_queue;
      /* Remove this job from the list.  */
      job_queue = job_queue->next;
    }
    
    /* Unlock the mutex on the job queue, since we're done with the
       queue for now.  */
    pthread_mutex_unlock (&job_queue_mutex);

    /* Was the queue empty?  If so, end the thread.  */
    if (next_job == NULL)
      break;

    /* Carry out the work.  */
    process_job (next_job);
    /* Clean up.  */
    //free (next_job);
  }
  return NULL;
}

//Creamos una mini cola de jobs, a ser procesada por dos threads
//pero protegida con un mutex
int main() 
{
  struct job sj1;
  struct job sj2;

  memset (&sj1, 0, sizeof (sj1));
  memset (&sj2, 0, sizeof (sj2));

  sj1.next = &sj2;
  sj1.job_number = 1;
  sj2.next = NULL;
  sj2.job_number = 2;

  job_queue = &sj1;

  pthread_create (&thread1_id, NULL, &thread_function, NULL);
  pthread_create (&thread2_id, NULL, &thread_function, NULL);

  /* Make sure the first thread has finished.  */
  pthread_join (thread1_id, NULL);
  /* Make sure the second thread has finished.  */
  pthread_join (thread2_id, NULL);


  return 0;
}
