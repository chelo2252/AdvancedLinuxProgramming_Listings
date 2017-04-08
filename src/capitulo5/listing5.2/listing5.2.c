#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>


/* We must define union semun ourselves.  */

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};

/* Obtain a binary semaphore's ID, allocating if necessary.  */

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
  
	semaphore_set_id = binary_semaphore_allocation(1234,IPC_CREAT|0666);
	/*o haciendo ipcs -s*/
	printf("Id del semaforo: %d\n", semaphore_set_id);
	
	int rtrn = binary_semaphore_deallocate(semaphore_set_id);
  printf("Valor de retorno del desasignado: %d\n", rtrn);
  return 0;
}
