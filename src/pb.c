#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include "leer_estudiantes.h"

#define MODEX "./MODELOSEXAMEN/"
#define MOD "MODELO"
#define SUFF ".pdf"
#define PERM 0644
#define BUFFSIZE 255

int copiarFichero(Alumno a);

int main(int argc, char* argv[]){

	Alumno lista[num_alumnos];

	printf("[PB] Leyendo\n");

	leerArchivo(lista);

	printf("[PB] Fichero leído\n");

	printf("[PB] Copiando archivos\n");
	int i;
	for(i = 0; i < num_alumnos; i++){
		copiarFichero(lista[i]);
	}

	printf("[PB] Copia finalizada\n");

	printf("[PB] Finalizado\n");

	return EXIT_SUCCESS;
}

int copiarFichero(Alumno a){

	int in_fd, out_fd, n_chars;
	char buf[BUFFSIZE];
	char *src;
	char *dst;

	src = malloc(sizeof(MODEX) + sizeof(MOD) + sizeof(char) + sizeof(SUFF));
	dst = malloc(sizeof(HOME) + sizeof(char[9]) + sizeof(MOD) + sizeof(char) + sizeof(SUFF));

	sprintf(src, "%s%s%c%s", MODEX, MOD, a.modex, SUFF);
	sprintf(dst, "%s%s/%s%c%s", HOME, a.dni, MOD, a.modex, SUFF);

	if((in_fd = open(src, O_RDONLY)) == -1){
		fprintf(stderr, "[PB] ERROR. Source file opening failed\n");
		return EXIT_FAILURE;
	}

	if((out_fd = creat(dst, PERM)) == -1){
		fprintf(stderr, "[PB] ERROR. Destination file creating failed\n");
		return EXIT_FAILURE;
	}

	while((n_chars = read(in_fd, buf, BUFFSIZE)) > 0){
		if(write(out_fd, buf, n_chars) != n_chars){
			fprintf(stderr, "[PB] ERROR. Destination file writing failed\n");
			return EXIT_FAILURE;
		}

		if(n_chars == -1){
			fprintf(stderr, "[PB] ERROR. Destination file writing failed\n\n");
			return EXIT_FAILURE;
		}
	}

	if(close(in_fd) == -1 || close(out_fd) == -1){
		fprintf(stderr, "[PB] ERROR. Files closeing failed\n\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
