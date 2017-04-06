#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;

  /* Crea un proceso hijo.  */
  child_pid = fork ();
  if (child_pid > 0) {
    /* si esta aca, es el padre. Esperar 15 segundos.  */
    sleep (15);
  }
  else {
    /* Si es el hijo, salir directamente.  */
    exit (0);
  }
  return 0;
}
