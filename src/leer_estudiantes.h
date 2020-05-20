#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NALUS 15
#define FILENAME "./estudiantes_p1.text"
#define HOME "p1home/"

typedef struct{
	char dni[9];
	char modex;
	int nota;
} Alumno;

int leerArchivo(Alumno list[num_alumnos]);

int leerArchivo(Alumno list[num_alumnos]){

	FILE *fp;
	Alumno a;
	char *token;

	printf("[LECTURA] Abriendo archivo\n");

	if((fp = fopen(FILENAME, "r")) == NULL){
		fprintf(stderr, "[LECTURA] ERROR. EL fichero no existe.\n");
		return EXIT_FAILURE;
	}

	printf("[LECTURA] Archivo abierto correctamente.\n");

	printf("[LECTURA] Leyendo archivo\n");

	char cad[16];
	int cont = 0, alu = 0;
	fgets(cad, 16, fp);

	while(!feof(fp)){
		token = strtok(cad, " ");
		while(token != NULL){
			switch(cont){
				case 0:
					strcpy(a.dni, token);
					break;
				case 1:
					a.modex = token[0];
					break;
				case 2:
					a.nota = atoi(token);
					break;
			}
			cont++;
			token = strtok(NULL, " ");
		}
		list[alu] = a;
		cont = 0;
		alu++;
		fgets(cad, 16, fp);
	}

	fclose(fp);

	printf("[LECTURA] Lectura completa.\n");

	return EXIT_SUCCESS;

}
