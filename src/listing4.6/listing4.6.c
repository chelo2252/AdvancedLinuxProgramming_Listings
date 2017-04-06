#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*estructura utilizada para la transaccion debido a que a un thread,
  solo se le puede pasar un puntero como parametro*/
struct Transfer{
  int from_acct;
  int to_acct;
  float dollars;
};
/* An array of balances in accounts, indexed by account number.  */

float* account_balances;

/* Transfer DOLLARS from account FROM_ACCT to account TO_ACCT.  Return
   0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
   too small.  */

int process_transaction (int from_acct, int to_acct, float dollars)
{
  int old_cancel_state;
  /* Check the balance in FROM_ACCT.  */
  if (account_balances[from_acct] < dollars)
    return (void*) 1;
  /* Begin critical section.  */
  pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &old_cancel_state);
  /* Move the money.  */
  account_balances[from_acct] -= dollars;
  /*si no se hubiera evitado el cancelar el thread y descomentado la linea
    siguiente, no se podria haber completado la operacion(aumentar la cuenta destino)*/
  //sleep(5);
  account_balances[to_acct] += dollars;
  /* End critical section.  */
  pthread_setcancelstate (old_cancel_state, NULL);

  return (void*) 0;
}

/*proceso que "castea" los datos de la transaccion a la funcion del listing*/
void* process(void* args){
  struct Transfer transfer = *((struct Transfer*) args);
  return process_transaction(transfer.from_acct, transfer.to_acct, transfer.dollars);
}


int main(){
  //se crea el vector de balances
  account_balances = malloc(sizeof(float)*4);
  *account_balances = 7.0;
  *(account_balances+1) = 3.0;
  *(account_balances+2) = 2.0;
  *(account_balances+3) = 4.0;
  
  printf("%s\n", "Original");
  printf("%.2f de la Cuenta %d\n", account_balances[0],0);
  printf("%.2f de la Cuenta %d\n", account_balances[3],3);
  

  struct Transfer transfer;
  transfer.from_acct = 0;
  transfer.to_acct = 3;
  transfer.dollars = 5.0;

  pthread_t thread;
  //creo proceso, luego se obtiene el resultado del thread
  pthread_create(&thread,NULL,&process,&transfer);

  int result = 5;
  //no se podra cancelar
  //pthread_cancel(thread);
  pthread_join(thread, (void*) &result);

  if(result == 0){
    printf("Operacion exitosa\n");
  }else if(result == 1){
    printf("Error en la operacion\n");
  }else{
    printf("Error inesperado\n");
  }
  printf("%.2f de la Cuenta %d\n", account_balances[0],0);
  printf("%.2f de la Cuenta %d\n", account_balances[3],3);
  
  return 0;
}