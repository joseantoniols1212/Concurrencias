#include <stdlib.h>
#include <stdio.h>
#include "gestion_memoria.h"

int MAX  = 1000;

/*
Función privada recomendada:
Recibe una lista y compacta elementos que son consecutivos, devolviendo la lista compactada.
*/
void compactar(T_Manejador *manejador_ptr){
    T_Manejador ant = *manejador_ptr;
    T_Manejador ptr = *manejador_ptr;
    while(ptr!=NULL && ptr->sig != NULL){
        ant = ptr;
        ptr = ptr->sig;
        if(ant->fin == ptr->inicio){
            ant->sig = ptr->sig;
            ant->fin = ptr->fin;
        }
    }
}

/* Crea la estructura utilizada para gestionar la memoria disponible. Inicialmente, s�lo un nodo desde 0 a MAX 
Por recordar:
typedef struct T_Nodo* T_Manejador;

struct T_Nodo {
	unsigned inicio;
	unsigned fin;
	T_Manejador sig;
};

En el main se define la lista como T_Manejador manej; (un puntero a una structura T_Nodo).
¿Porqué se pasa un puntero a T_Manejador? ¿Que pasa si pasamos T_Manejador y no un puntero a T_Manejador y cambiamos su valor (su valor es una zona de memporia)?
*/
void crear(T_Manejador* manejador){
    (*manejador) = malloc(sizeof(struct T_Nodo));
    (*manejador)->inicio=0;
    (*manejador)->fin=MAX-1;
    (*manejador)->sig=NULL;
}

/* Destruye la estructura utilizada (libera todos los nodos de la lista. El par�metro manejador debe terminar apuntando a NULL 

Consejo: Para saber si te estas dejando memoria por ahí, en el main crea un bucle infinito que crea y destruye, si la memoria no se mantiene constante, está mal.

*/
void destruir(T_Manejador* manejador){
    T_Manejador aux = (*manejador);
    while((*manejador)!=NULL){
        (*manejador)=(*manejador)->sig;
        free(aux);
        aux = (*manejador);
    }
}

/* Devuelve en �dir� la dirección de memoria �simulada� (unsigned) donde comienza el trozo de memoria continua de tamaño �tam� solicitada.
Si la operación se pudo llevar a cabo, es decir, existe un trozo con capacidad suficiente, devolvera TRUE (1) en �ok�; FALSE (0) en otro caso.
 */
void obtener(T_Manejador *manejador, unsigned tam, unsigned* dir, unsigned* ok){
    *ok=0;
    T_Manejador anterior = *manejador;
    T_Manejador iter = *manejador;
    unsigned tam_nodo;
    while(iter!=NULL && !(*ok)){ // Recorremos la lista enlazada
        tam_nodo = iter->fin - iter->inicio + 1;
        if(tam_nodo < tam){ // Comprobamos si el nodo es menor que tam

            anterior = iter; //Guardamos el nodo antes de avanzar por si necesitamos eliminar un nodo
            iter = iter->sig; // Pasamos al siguiente nodo

        } else if (tam_nodo > tam){ // Si el nodo es mayor que tam, tomamos la memoria de aqui

            *dir=iter->inicio;
            iter->inicio = iter->inicio + tam;
            *ok=1;

        } else { // Si el nodo es del tamanyo que se pide, se elimina el nodo

            if(iter == *manejador){
                *dir=iter->inicio;
                *manejador = NULL;
            }
            *dir=iter->inicio;
            anterior->sig = iter->sig;
            free(iter);
            *ok=1;

        }
    }
}

/* Muestra el estado actual de la memoria, bloques de memoria libre */
void mostrar (T_Manejador manejador){
    // if(manejador==NULL){
    //     printf("AAAA \n");
    // }
    while(manejador!=NULL){
      printf("Inicio: %u, Fin: %u, \n", manejador->inicio, manejador->fin);
      manejador=manejador->sig;
  }
}

/* Devuelve el trozo de memoria continua de tamaño �tam� y que
 * comienza en �dir�.
 * Se puede suponer que se trata de un trozo obtenido previamente.
 */
void devolver(T_Manejador *manejador,unsigned tam,unsigned dir){
    T_Manejador nuevo = malloc(sizeof(struct T_Nodo));
    T_Manejador ant, iter;
    if( *manejador == NULL ){ //Si la memoria esta totalmente llena
        (*manejador)->sig = nuevo;
        nuevo->inicio = dir;
        nuevo->fin = dir + tam - 1;
        nuevo->sig = NULL;
        *manejador = nuevo;
    } else if ( (*manejador)->inicio > dir + tam -1 ){ // Si tiene que insertar el nodo el primero
        nuevo->sig = (*manejador);
        (*manejador) = nuevo;
        nuevo->inicio = dir;
        nuevo->fin = dir + tam - 1;
    } else {
        ant = *manejador;
        iter = (*manejador)->sig;
        while(iter != NULL && iter->inicio < dir + tam - 1 ){
            ant = iter;
            iter = iter->sig;
        }
        ant->sig = nuevo;
        nuevo->sig = iter;
        nuevo->inicio = dir;
        nuevo->fin = dir + tam -1;
    }
    compactar(manejador);
}
