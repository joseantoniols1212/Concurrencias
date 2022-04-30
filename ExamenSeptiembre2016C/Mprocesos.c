#include "Mprocesos.h"
#include <stdio.h>
#include <stdlib.h>

void Crear(LProc *lista){
    *lista = NULL;
}

void AnadirProceso(LProc *lista, int idproc){
    LProc nuevo = malloc(sizeof(LProc));
    if(nuevo == NULL) {
        perror("No se pudo pedir memoria al anyadir proceso");
    } else {
        nuevo->id = idproc;
        if(*lista == NULL){
            *lista = nuevo;
            nuevo->sig = nuevo;
        } else {
            nuevo->sig = (*lista)->sig;
            (*lista)->sig = nuevo;
        }
    }
}

void EjecutarProcesos(LProc lroundrobin){
    if(lroundrobin != NULL){
        LProc iter = lroundrobin->sig;
        while(iter != lroundrobin){
            printf("Proceso %i ejecutado \n", iter->id);
            iter = iter->sig;
        }
    }
}

void EliminarProceso(int id, LProc *lista) {
    if(*lista != NULL){
        LProc iter = (*lista)->sig;
        LProc anterior = *lista;
        while(iter != (*lista)){
            if(iter->id == id){
                anterior->sig = iter->sig;
                free(iter);
                iter = anterior->sig;
            } else {
                iter = iter->sig;
            }
        }
        if(iter->id == id){
            anterior->sig = iter->sig;
            free(iter);
            *lista = anterior;
        }
    }
}

void EscribirFichero (char * nomf, LProc *lista) {
    FILE * f;

    if((f = fopen(nomf, "wb"))==NULL){
        perror("No se pudo abrir el archivo");
    } else {

        LProc iter = (*lista)->sig;
        while(iter != *lista){
            fwrite(&(iter->id), sizeof(int), 1, f);
            iter = iter->sig;
        }
        fwrite(&((*lista)->id), sizeof(int), 1, f);

        fclose(f);
    }
}
