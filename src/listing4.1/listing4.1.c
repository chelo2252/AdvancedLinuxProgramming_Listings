#include <pthread.h>
#include <stdio.h>

//Cambiamos los while(1) por for para que el programa termine, ya que de igual manera 
//se logra el objetivo de ver como dos threads se ejecutan de manera concurrente.


void* print_xs (void* unused)
{
  //Desde el thread creado vamos a imprimir x
  for (int i = 0; i < 5; ++i)
   {
     fputc ('x', stderr);
   }  
  
  return NULL;
}

/* The main program.  */

int main ()
{
  pthread_t thread_id;
  
  /* Create a new thread.  The new thread will run the print_xs
     function.  */
  pthread_create (&thread_id, NULL, &print_xs, NULL);
  
  //Desde el thread creador vamos a imprimir o's
  for (int i = 0; i < 5; ++i)
   {
     fputc ('o', stderr);
   }  

   return 0;
}
