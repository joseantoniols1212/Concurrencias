#include <stdlib.h>
#include <stdio.h>
#include "gestion_lista.h"

//crea una lista vacía
void crearLista(Lista *l){
    *l = malloc(sizeof(struct NodoLista));
} 
 //escribe en la pantalla los elementos de la lista
void recorrerLista(Lista l){
    while(l != NULL){
        printf("Elemento: %i", l->elem);
        l = l->sig;
    }
} 

//devuelve 0 sii la lista está vacía
int listaVacia(Lista l){
    int llena;

    if(l==NULL){
        llena = 0;
    } else {
        llena = 1;
    }
 return llena;
}  

// inserta el elemento elem en la lista l de forma que quede ordenada de forma creciente
void insertarLista(Lista *l,int elem){
    Lista nuevo = malloc(sizeof(struct NodoLista));
    nuevo->elem = elem;

    if(*l == NULL){ // Si no tiene elementos
        nuevo->sig = NULL;
        *l = nuevo;
    } else if( (*l)->elem > elem ) { // Si tiene un elemento
        nuevo->sig = *l;
        *l = nuevo;
    } else {
        Lista iter = *l;
        while(iter->sig != NULL && iter->sig->elem < elem){
            iter = iter->sig;
        }
        nuevo->sig = iter->sig;
        iter->sig = nuevo;
    }
}   

// elimina de la lista el elemento elem. Devuelve 1 si se ha podido eliminar y 0, si elem no estaba en la lista.
int extraerLista(Lista *l,int elem){
    Lista aux, iter;
    iter = *l;
    while(iter != NULL && iter->elem < elem){
        
    }
}   

 //elimina todos los nodos de la lista y la deja vacía
void borrarLista(Lista *l){
    Lista aux;
    while(*l != NULL){
        aux = *l;
        (*l) = (*l)->sig;
        free(aux);
    }
}  