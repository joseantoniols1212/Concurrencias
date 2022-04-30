/*
 ============================================================================
 Name        : Practica2B.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "arbolbb.h"

/**
 * Recibe un número "tam" del usuario, y
 * crea un fichero binario para escritura con el nombre "nfichero"
 * en que escribe "tam" numeros (unsigned int) aleatorios
 * Se utiliza srand(time(NULL)) para establecer la semilla (de la libreria time.h)
 * y rand()%100 para crear un n�mero aleatorio entre 0 y 99.
 */
void creafichero_tam_random(char* nfichero, unsigned tam)
{
	FILE * pfile = fopen(nfichero,"wb");
	if(pfile == NULL){
		perror("No se ha podido abrir el fichero\n");
	} else {
		srand(time(NULL));
		unsigned int array_rand[tam];
		for(int i = 0; i < tam; i++){
			unsigned int num = rand()%tam;
			array_rand[i] = num;
		}
		fwrite(array_rand, sizeof(unsigned), tam, pfile);
		fclose(pfile);
	}
}
/**
 * Muestra por pantalla la lista de números (unsigned int) almacenada
 * en el fichero binarhoio "nfichero"
 */
void muestrafichero(char* nfichero) // TODO
{
	FILE * pfile = fopen(nfichero, "rb");
	if(pfile == NULL){
		perror("No se ha podido abrir el fichero\n");
	} else {
		unsigned int basura;
		while(fread(&basura, sizeof(unsigned), 1, pfile) != 0) printf("%u \n", basura);
		fclose(pfile);
	}
}

/**
 * Guarda en el arbol "*miarbol" los números almacenados en el fichero binario "nfichero"
 */

void cargaFichero(char* nfichero, T_Arbol* miarbol)
{
	FILE * pfile = fopen(nfichero, "rb");
	if(pfile == NULL){
		perror("No se ha podido abrir el fichero\n");
	} else {
		unsigned int basura;
		while(fread(&basura, sizeof(unsigned), 1, pfile) != 0) Insertar(miarbol, basura);
		fclose(pfile);
	}
}

int main(void) {
	char nfichero[50];
	unsigned num_random;

	printf ("Introduce el nombre del fichero binario:\n");
	scanf ("%s",nfichero);

	printf ("Introduce el número de elementos a crear:\n");
	scanf ("%i",&num_random);

	creafichero_tam_random(nfichero, num_random);

	printf("\nAhora lo leemos y mostramos\n");
	muestrafichero(nfichero);

	printf ("\nAhora lo cargamos en el arbol\n");
	T_Arbol miarbol;
	Crear (&miarbol);
	cargaFichero(nfichero,&miarbol);

	printf ("\nY lo mostramos ordenado\n");
	Mostrar(miarbol);
	

	printf("\nAhora lo guardamos ordenado\n");
	FILE * fich;
	fich = fopen (nfichero, "wb"); //al abrir con w se borra el contenido
	if(fich != NULL){
		Salvar (miarbol, fich);
		fclose (fich);
	}
	printf("\nY lo mostramos ordenado\n");
	muestrafichero(nfichero);
	Destruir (&miarbol);

	return EXIT_SUCCESS;
}
