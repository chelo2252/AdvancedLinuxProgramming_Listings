#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

struct job {
  /* Link field for linked list.  */
  struct job* next; 
  /* Other fields describing work to be done... */
  int id;
};

/* A linked list of pending jobs.  */
struct job* job_queue = NULL;

extern void process_job (struct job*,int*);

/* Process queued jobs until the queue is empty.  */

void* thread_function (void* arg)
{
  while (job_queue != NULL) {
    /* Get the next available job.  */
    struct job* next_job = job_queue;
    /* Remove this job from the list.  */
    job_queue = job_queue->next;
    /* Carry out the work.  */
    process_job (next_job,arg);
    /* Clean up.  */
    free (next_job);
  }
  return NULL;
}

void process_job(struct job* job, int* threadPos){
  printf("Procesando job: %d  Por thread: %d\n",job->id, *threadPos);
}

int main(){
  /*se crea la lista y luego se comienzan los threads,
    con su pos para poder identificarlos*/
  for(int i = 0; i < 10 ; i++){
    struct job* nuevoJob = malloc(sizeof(struct job));
    
    nuevoJob->next = job_queue;
    nuevoJob->id = i;
    job_queue = nuevoJob;
  }

  int tamanho = 5;
  pthread_t threads[tamanho];

  for(int i = 0 ; i < tamanho ; i++){
    int* threadPos = malloc(sizeof(int));
    *threadPos = i; 
    pthread_create(&(threads[i]),NULL,&thread_function,threadPos);
  }
  
  for(int i = 0 ; i < tamanho ; i++)
    pthread_join(threads[i],NULL);

  return 0;
}