/*
	DESCRIPTION         
	===========
	The sigaction() system call is used to change the action taken by a
	process on receipt of a specific signal.

	signum specifies the signal and can be any valid signal except
	SIGKILL and SIGSTOP.

	If act is non-NULL, the new action for signal signum is installed
	from act.  If oldact is non-NULL, the previous action is saved in
	oldact.

	The sigaction structure is defined as something like:

           struct sigaction {
           	   //puntero a la funcion que accionara en respuesta a la senhal o SIG_DFL o SIG_IGN	
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
*/

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

sig_atomic_t sigusr1_count = 0;

//Como respuesta al recibimiento de la senhal aumenta el contador
void handler (int signal_number)
{
  ++sigusr1_count;
}

int main ()
{

  //Crea el struct sa
  struct sigaction sa;
  memset (&sa, 0, sizeof (sa));

  //Establece el metodo handler en el struct sa para accionar a una senhal
  sa.sa_handler = &handler;

  // Se establece a la senhal SIGUSR1 la accion indicada en el struct sa,
  // sin guardar la vieja accion tomada.
  sigaction (SIGUSR1, &sa, NULL);

  //A modo de prueba nos enviamos nosotros mismos la senhal SIGUSR1 10 veces 
  for (int i = 0; i < 10; ++i)
  {
  	kill(getpid(), SIGUSR1);
  }

  //imprime el numero de veces que fue recibida la senhal SIGUSR1
  printf ("SIGUSR1 was raised %d times\n", sigusr1_count);
  return 0;
}
