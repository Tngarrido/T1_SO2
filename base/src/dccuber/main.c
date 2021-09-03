#include <stdio.h>
#include <unistd.h>
#include "../file_manager/manager.h"
#include <sys/wait.h>
#include <stdbool.h>


pid_t semaforo1_pid;
int child_fabrica;


void handle_Semaforo(int sig, siginfo_t *siginfo, void *context)
{
    //Luego hay que ver como indentificar al semaforo
    printf("LLEGO SEÑAL DEL SEMAFORO\n");
    int color_semaforo = siginfo->si_value.sival_int;
    printf("PADRE: SEMAFORO CAMBIO DE COLOR %d\n", color_semaforo);
}

void handle_sigalrm(int sig)
{
   printf("PRINCIPAL: enviando la fucking señal a \n");
   send_signal_with_int(child_fabrica, 2);
   printf("ya se envio la señal\n");
}



int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);
  //data_in: arreglo de arreglos que contienen char (otro arreglo)
  /*
  primera linea: data_in->lines[0]
  primera palabra: data_in->lines[0][0]
  1era letra de la 1era palabra: data_in->lines[0][0][0]
  cantidad total de lineas: data_in->len
  */
  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  //DISTANCIA DE SEMAFOROS
  unsigned int dist_semaforo1 = data_in->lines[0][0];
  int dist_semaforo2 = atoi(data_in->lines[0][1]);
  int dist_semaforo3 = atoi(data_in->lines[0][2]);
  int dist_bodega = atoi(data_in->lines[0][3]);
  //CADA time_c SEGUNDOS SE DEBE CREAR UN PROCESO REPARTIDOR -> ALARM(time_c)
  int time_c = atoi(data_in->lines[1][0]);
  int cantidad_repartidores = atoi(data_in->lines[1][1]);
  int time_1 = atoi(data_in->lines[1][2]); //alarm(time_i)
  int time_2 = atoi(data_in->lines[1][3]);
  int time_3 = atoi(data_in->lines[1][4]);
  printf("CREAMOS UN PROCESO HIJO SEMÁFORO\n");
  int status_semaforo1;
  //realizamos el proceso de un nuevo ejecutable
  
  int pid_parent = getpid();
  child_fabrica = fork();
  printf("FABRICA  PID: %d\n", child_fabrica);
  if (!child_fabrica)
  {
      //PROCESO FABRICA
      //CONECTAMOS PARA QUE RECIBA SEÑAL
      printf("HIJO F: CONECTAMOS LA SEÑAL\n");
      connect_sigaction(SIGUSR1, handle_Semaforo);
      printf("HIJO: F: Esperamos la señal \n");
      while(true);
  }
  /*
  else
  {
    SEMAFORO ------------------------------------------------------------------------
    pid_t child_semaforo = fork();
    if (!child_semaforo)
    {
      //PROCESO SEMAFORO
      char id_str[4];
      char delay[20];
      char parent_id_str[20];
      char fabrica_id_str[20];
      int id = 1;
      sprintf(id_str, "%d", id);
      sprintf(delay, "%d", time_1);
      sprintf(parent_id_str, "%d", pid_parent);
      sprintf(fabrica_id_str, "%d", child_fabrica);
      char *args[5] ={id_str, delay, parent_id_str, fabrica_id_str, NULL};
      printf("CHILD: EJECUTANDO ARCHIVO EJECUTABLE SEMAFORO\n");
      execvp("./semaforo", args);
    }
    else
    {
      printf("SEMAFORO  PID: %d\n", child_semaforo);
      //PROCESO PRINCIPAL
      printf("PADRE: ESPERA LA SEÑAL DEL HIJO\n");
  
      pid_t child_exit = wait(NULL);     
      printf("PADRE: CHILD FINALIZO %d\n", child_exit);
      pid_t child_exit2 = wait(NULL);
      
      printf("PADRE: CHILD FINALIZO %d\n", child_exit2); 
    }
  }
  */
 // Esperamos al único hijo
  signal(SIGALRM, handle_sigalrm);
  // Puedes intentar de cambiar la siguiente linea por alarm(1);
  kill(getpid(), SIGALRM);
  wait(NULL);
  printf("Padre ha terminado.\n");
  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
  
}
