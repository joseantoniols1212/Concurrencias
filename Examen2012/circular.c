#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "circular.h"

void Crear(LProc *lista){
    *lista = NULL;
}

void AnyadirProceso(LProc *lista, int idproc){
    if(*lista != NULL){
        LProc iter = *lista;
        while(iter->sig != *lista){
            iter = iter->sig;
        }
        LProc nuevo = malloc(sizeof(struct circular));
        nuevo->pid = idproc;
        nuevo->sig = *lista;
        iter->sig = nuevo;
    } else {
        (*lista) = malloc(sizeof(struct circular));
        (*lista)->pid = idproc;
        (*lista)->sig = *lista;
    }
}

void MostrarLista(LProc lista){
    if(lista == NULL){
        printf("Lista vacia \n");
    } else {
        LProc iter = lista;
        do {
            printf("pid: %i \n", iter->pid);
            iter=iter->sig;
        } while (iter != lista);
        printf("Final de la lista \n");
    }
}

void EjecutarProceso(LProc *lista){
    if (*lista != NULL){
        if((*lista)->sig != (*lista)){
            LProc aux = *lista;
            LProc iter = *lista;
            while (iter->sig != (*lista)){
                iter = iter->sig;
            }
            iter->sig = aux->sig;
            *lista = aux->sig;
            free(aux);
        } else {
            free(*lista);
            *lista = NULL;
        }
    }
}
