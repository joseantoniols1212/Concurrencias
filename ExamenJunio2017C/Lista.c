#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>

void crearLista(TLista *lista){
  *lista = NULL;
}

// Devuelve 1 si esta en la lista y 0 si no
int estaPunto(TLista lista, struct Punto punto){
  int esta = 0;
  while(lista != NULL && !esta){
    if(lista->punto.x == punto.x) esta = 1;
  }
  return esta;
}

void insertarPunto(TLista *lista, struct Punto punto, int * ok){
  TLista nuevo;

  if((nuevo = malloc(sizeof(struct Nodo))) == NULL) {
    perror("No se ha podido pedir memoria.");
  } else {
    nuevo->punto.x = punto.x;
    nuevo->punto.y = punto.y;

    *ok = 0;

    if(*lista == NULL) { // Si la lista esta vacia metemos el primer elemento

      *lista = nuevo;
      *ok = 1;

    } else { // En caso de que no este vacia
      
      if ((*lista)->punto.x > punto.x ) {  // Comprobamos si debe ser el primer elemento a ser insertado

        nuevo->sig = *lista;
        *lista = nuevo;
        *ok = 1;

      } else if((*lista)->punto.x == punto.x) { // Si el primer elemento es igual devolvermos ok = 0

        *ok = 0;

      }{ // En caso de que no sea el primer elemento de la lista
        
        TLista iter;
        int parar = 0;
        iter = (*lista);
        while(iter->sig != NULL && !parar) {
          if(iter->sig->punto.x == punto.x) {
            parar = 1;
          } else if (iter->sig->punto.x < punto.x){
            *ok = 1;
            parar = 1;
            nuevo->sig = iter->sig;
            iter->sig = nuevo;
          }
          iter = iter->sig;
        }
      }
    }
  }
}


void eliminarPunto(TLista *lista,float x,int* ok) {
  if(*lista == NULL) { // Si la lista esta vacia devolvemos 0 

    *ok = 0;

  } else if ((*lista)->punto.x == x) { // En caso de que el primer elemento sea el que hay que eliminar
    
    TLista aux = (*lista)->sig;
    free(*lista);
    *lista = aux;

  } else {

    *ok = 0;
    TLista iter, aux;
    iter = (*lista);

    while(iter->sig != NULL && iter->sig->punto.x <= x) {

      if(iter->sig->punto.x == x) {
        aux = iter->sig;
        iter->sig = aux->sig;
        free(aux);
        *ok = 1;
      } 
       
      iter = iter->sig;
    }
  }
}

void mostrarLista(TLista lista){
  while(lista != NULL){
    printf("x: %f   y: %f", lista->punto.x, lista->punto.y);
    lista = lista->sig;
  }
}

void destruir(TLista *lista){
  if(*lista != NULL){
    destruir(&(*lista)->sig);
    free(*lista);
  }
}


void leePuntos(TLista *lista,char * nFichero){
  FILE * f;

  f = fopen(nFichero, "rb");

  float x,y;
  while(fread(&x, sizeof(float), 1, f) && fread(&y, sizeof(float), 1, f)){
    struct Punto punto = {x, y};
    int ok = 0;
    insertarPunto(lista,punto, &ok);
  }

  fclose(f);
}
