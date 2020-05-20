#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

#include "leer_estudiantes.h"

#define PA "exec/pa"
#define PB "exec/pb"
#define PC "exec/pc"
#define PD "exec/pd"
#define NPS 2
#define LOG "log.txt"
#define WR 1
#define RD 0

pid_t pids[3];

FILE *mylog;

void handler(int signum);

int main(int argc, char* argv[]){

	int status_a;

	mylog = fopen(LOG, "w");

	fprintf(mylog, "Log del sistema *\n");

	printf("[MANAGER] Iniciando programa\n");

	signal(SIGINT, handler);

	mkdir(HOME, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	printf("[MANAGER] Creando proceso PA\n");

	switch(pids[0] = fork()){
		case -1:
			fprintf(stderr, "[MANAGER] ERROR. No ha podido crearse el proceso hijo.");
			return EXIT_FAILURE;
		case 0:
		    execl(PA, PA, NULL);
		    fprintf(stderr, "[PA] ERROR. Ejecucuión fallida\n");
		    return EXIT_FAILURE;
		default:
			break;
	}

	printf("[MANAGER] Esperando PA\n");

	waitpid(pids[0], &status_a, 0);

	fprintf(mylog, "Creación de directorios finalizada\n");

	printf("[MANAGER] Proceso PA (%d) finalizado (Causa: %d).\n", pids[0], WEXITSTATUS(status_a));

	printf("[MANAGER] Creando procesos PB y PC\n");

	int status_b, status_c;

	int tub[2];
	char desc[4];
	char buf[32];
	int i;
	pipe(tub);
	sprintf(desc, "%d", tub[WR]);

	for(i = 0; i < NPS; i++){
		switch(pids[i+1] = fork()){
			case -1:
				fprintf(stderr, "[MANAGER] ERROR. No ha podido crearse el proceso hijo.");
				return EXIT_FAILURE;
			case 0:
				if(i == 0){
					execl(PB, PB, NULL);
		    		fprintf(stderr, "[PB] ERROR. Ejecucuión fallida\n");
		    		return EXIT_FAILURE;
				}else{
					execl(PC, PC, desc, NULL);
		    		fprintf(stderr, "[PC] ERROR. Ejecucuión fallida\n");
		    		return EXIT_FAILURE;
				}
			default:
				break;
		}
	}

	printf("[MANAGER] Esperando proceso PB\n");

	waitpid(pids[1], &status_b, 0);

	fprintf(mylog, "Copia de modelos de examen finalizada\n");

	printf("[MANAGER] Proceso PB (%d) finalizado (Causa: %d).\n", pids[1], WEXITSTATUS(status_b));

	printf("[MANAGER] Esperando proceso PC\n");

	waitpid(pids[2], &status_c, 0);

	fprintf(mylog, "Creación de archivos con nota necesaria para alcanzar la nota de corte finalizada\n");
	
	printf("[MANAGER] Proceso PC (%d) finalizado (Causa: %d).\n", pids[2], WEXITSTATUS(status_c));

	printf("[MANAGER] Leyendo nota media desde tubería\n");

	if(read(tub[RD], buf, sizeof(buf)) < 0){
		fprintf(stderr, "[MANAGER] ERROR. Falló la lectura de la tubería\n");
		return EXIT_FAILURE;
	}

	fprintf(mylog, "La nota media de la clase es %s\n", buf);

	printf("[MANAGER] Nota media leída correctamente\n");

	fprintf(mylog, "FIN DEL PROGRAMA\n");

	fclose(mylog);

	printf("[MANAGER] Finalizado\n");

	return EXIT_SUCCESS;

}

void handler(int signum){

	printf("[MANAGER] Señal de interrupción recibida\n");

	printf("[MANAGER] Interrumpiendo procesos\n");

	kill(pids[0], SIGINT);
	kill(pids[1], SIGINT);
	kill(pids[2], SIGINT);

	printf("[MANAGER] Procesos hijos finalizados\n");

	printf("[MANAGER] Ejecutando PD\n");

	pid_t d_pid;

	int status_d;

	switch(d_pid= fork()){
		case -1:
			fprintf(stderr, "[MANAGER] ERROR. No pudo crearse el proceso hijo.");
		    exit(EXIT_FAILURE);
		case 0:
		    execl(PD, PD, NULL);
		    fprintf(stderr, "[PD] ERROR. Ejecucuión fallida\n");
		    exit(EXIT_FAILURE);
		default:
			break;
	}

	waitpid(d_pid, &status_d, 0);

	fprintf(mylog, "EJECUCIÓN INTERRUMPIDA POR EL USUARIO (Ctrl + C)\n");

	printf("[MANAGER] Proceso PD (%d) finalizado (Causa: %d).\n", d_pid, WEXITSTATUS(status_d));

	printf("[MANAGER] Finalizado.\n");

	fclose(mylog);

	exit(EXIT_FAILURE);

}
