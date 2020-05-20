#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	printf("[PD] Borrando archivos\n");

	system("rm -r p1home/");	

	printf("[PD] Archivos borrados.Finalizando\n");

	return EXIT_SUCCESS;
}
