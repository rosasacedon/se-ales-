#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "leer_estudiantes.h"

#define MKDIR "mkdir"

int main(int argc, char* argv[]){

	Alumno lista[num_alumnos];

	printf("[PA] Comenzando lectura\n");

	leerArchivo(lista);

	printf("[PA] Fichero leído\n");

	printf("[PA] Creando directorios\n");

	char *dir;
	dir = malloc(sizeof(HOME) + sizeof(char[9]));
	int i;
	for(i = 0; i < num_alumnos; i++){
		sprintf(dir, "%s%s", HOME, lista[i].dni);
		mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	printf("[PA] Directorios creados\n");

	printf("[PA] Finalizado\n");

	return EXIT_SUCCESS;

}
