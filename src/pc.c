#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "leer_estudiantes.h"

#define NOTAFILE "NotaEsperada.txt"
#define MSG "La nota que debes obtener en este nuevo examen para superar la prueba es"

int calcularNota(int ini);

int main(int argc, char *argv[]){

	Alumno lista[NALUS];

	printf("[PC] Comenzando lectura\n");

	leerArchivo(lista);

	printf("[PC] Fichero leído\n");

	printf("[PC] Calculando notas\n");

	int nota;
	float suma;
	char media[32];

	FILE *fp;

	char *dir;

	dir = malloc(sizeof(HOME) + sizeof(char[9]) + sizeof(NOTAFILE));

	char *cad;

	cad = malloc(sizeof(MSG) + sizeof(int) + sizeof(char)*3);
	int i;
	for(i = 0; i < NALUS; i++){

		nota = calcularNota(lista[i].nota);

		sprintf(dir, "%s%s/%s", HOME, lista[i].dni, NOTAFILE);

		if((fp = fopen(dir, "w")) == NULL){
			fprintf(stderr, "[PC] ERROR. No se pudo abrir el fichero para escritura\n");
			return EXIT_FAILURE;
		}

		sprintf(cad, "%s %d.\n", MSG, nota);

		if(fputs(cad, fp) == EOF){
			fprintf(stderr, "[PC] ERROR. Falló la escritura del archivo\n");
			return EXIT_FAILURE;			
		}

		fclose(fp);

		suma = suma + lista[i].nota;

	}

	printf("[PC] Calculando media\n");

	sprintf(media, "%f", (suma / NALUS));

	if(write(atoi(argv[1]), media, sizeof(media)) != sizeof(media)){
		fprintf(stderr, "[PC] ERROR. Fallo la escritura en la tubería\n");
		return EXIT_FAILURE;
	}

	printf("[PC] Media calculada y escrita en tubería\n");

	printf("[PC] Finalizado\n");
	
	return EXIT_SUCCESS;
}

int calcularNota(int ini){
	return 10 - ini;
}
