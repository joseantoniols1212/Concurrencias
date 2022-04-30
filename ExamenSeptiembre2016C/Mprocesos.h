/*
 * Mprocesos.h
 *
 *  Created on: 01/09/2016
 *      Author: luisll
 */

#ifndef MPROCESOS_H_
#define MPROCESOS_H_
#include <stdlib.h>

/* Defincion de tipos*/

typedef struct Nodo * LProc;
struct Nodo {
    int id;
    LProc sig;
};

void Crear(LProc *lista);

void AnadirProceso(LProc *lista, int idproc);

void EjecutarProcesos(LProc lroundrobin);


void EliminarProceso(int id, LProc *lista);

void EscribirFichero (char * nomf, LProc *lista);


#endif /* MPROCESOS_H_ */
