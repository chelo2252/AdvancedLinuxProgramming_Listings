#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void* thread_function (void* thread_arg)
{
  //imprimimos un texto de ejemplo
  printf("%s\n", "Im a thread and my job is done");
  return NULL;
}

int main ()
{
  //Crea el objeto de atributos
  pthread_attr_t attr;
  pthread_t thread;

  //Inicializa el objeto de atributos con los valores por defecto
  pthread_attr_init (&attr);
  //Setea el modo detach
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  //Crea un thread con los atributos especificados
  pthread_create (&thread, &attr, &thread_function, NULL);
  //Libera el objeto de atributos
  pthread_attr_destroy (&attr);

  //Le hacemos dormir un ratito para que se vea el output del thread creado
  sleep(2);

  // No hace falta hacer el join porque el thread es detached  

  return 0;
}
