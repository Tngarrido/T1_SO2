#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "../file_manager/manager.h"


  //COMIENZA CON COLOR VERDE
  int color = 0; //0: verde, 1: rojo
  int parent_id;
  int pid_fabrica;

void handle_semaforo(int sig){
  /*
  este proceso deberia ir cambiando su status cada cierto tiempo
  con el fin de representar el cambio de color de un semaforó
  */
  printf("CAMBIANDO DE COLORL\n");
  if (color==0)
  {
      //cambiando a rojo
      color = 1;
      //enviamos señal al proceso principal
      printf("ENVIANDO SEÑALLL A %d  color: %d\n", pid_fabrica, color);
      send_signal_with_int(pid_fabrica, color);
      printf("YA SE ENVIO\n");
  }
  else
  {
    //cambiando a verde
    color = 0;
    printf("ENVIANDO SEÑAL\n");
   send_signal_with_int(pid_fabrica, color);
    exit(0);
  }
}




int main(int argc, char* argv[])
{

  /*
  RECOGEMOS LOS ARGUMENTOS ENTREGADOS
  argv[0]: id
  argv[1]: delay
  argv[2]: parent
  */
  //TRANSFORMAMOS BUFFER A INT NUEVAMENTE
  int id = atoi(argv[0]);
  int delay = atoi(argv[1]);
  parent_id = atoi(argv[2]);
  pid_fabrica = atoi(argv[3]);
  printf("HIJO S: PID FABRICA ES: %d\n", pid_fabrica);
  //CONECTACMOS UNA SIGALRM CON HANDLE
  printf("HIJO S: CONECTAMOS SIGALRM CON HANLDE SEMAFORO-EVIAMOS DE UNA\n");
  printf("ENVIANDO SEÑALLL A %d  color: %d\n", pid_fabrica, color);
  //send_signal_with_int(pid_fabrica, color);
  printf("YA SE ENVIO TRUCO\n");
  exit(0);
  //signal(SIGALRM, handle_semaforo);
  //sleep(2 - 1);
  //pasaron 2 segundos y se envia la señal
  //kill(getpid(), SIGALRM);

/*
  while (true)
  {
    //DUERME MANTENIENDOSE EN EL COLOR QUE TOCA
    sleep(delay - 1);
    //ENVIA SEÑAL QUE CAMBIO DE COLOR
    alarm(1);
  }
  */
  
  
  
}
