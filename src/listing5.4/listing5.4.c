#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};

/* Wait on a binary semaphore.  Block until the semaphore value is
   positive, then decrement it by one.  */

int binary_semaphore_wait (int semid)
{
  struct sembuf operations[1];
  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;
  /* Decrement by 1.  */
  operations[0].sem_op = -1;
  /* Permit undo'ing.  */
  operations[0].sem_flg = SEM_UNDO;
  
  return semop (semid, operations, 1);
}

/* Post to a binary semaphore: increment its value by one.  This
   returns immediately.  */

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;
  /* Increment by 1.  */
  operations[0].sem_op = 1;
  /* Permit undo'ing.  */
  operations[0].sem_flg = SEM_UNDO;
  
  return semop (semid, operations, 1);
}

int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}

int binary_semaphore_allocation (key_t key, int sem_flags)
{
  return semget (key, 1, sem_flags);
}

/* Deallocate a binary semaphore.  All users must have finished their
   use.  Returns -1 on failure.  */

int binary_semaphore_deallocate (int semid)
{
  union semun ignored_argument;
  return semctl (semid, 1, IPC_RMID, ignored_argument);
}


int main()
{
  int semaphore_set_id;
  int retrn;


  semaphore_set_id = binary_semaphore_allocation(1234,IPC_CREAT|0666);
  printf("Id del semaforo: %d\n", semaphore_set_id);
  
  binary_semaphore_initialize(semaphore_set_id);
  
  retrn = semctl(semaphore_set_id,0,GETVAL,NULL);
  printf("Valor del semaforo inicializado: %d\n",retrn);
  
  binary_semaphore_wait(semaphore_set_id);

  retrn = semctl(semaphore_set_id,0,GETVAL,NULL);
  printf("Valor del semaforo luego del wait: %d\n",retrn);

  binary_semaphore_post(semaphore_set_id);
  retrn = semctl(semaphore_set_id,0,GETVAL,NULL);
  printf("Valor del semaforo luego del post: %d\n",retrn);

  retrn = binary_semaphore_deallocate(semaphore_set_id);
  printf("Valor de retorno del desasignado: %d\n", retrn);
  
  return 0;
}