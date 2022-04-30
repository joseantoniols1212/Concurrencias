/*
 * arbolbb.c
 *
 *  Created on: 15 mar. 2021
 *      Author: Laura
 */
#include <stdio.h>
#include <stdlib.h>
#include "arbolbb.h"


// Inicializa la estructura a NULL.
void Crear(T_Arbol* arbol_ptr){
    *arbol_ptr = NULL;
}

// Destruye la estructura utilizada.
void Destruir(T_Arbol *arbol_ptr){
    if(*arbol_ptr != NULL){
        Destruir(&(*arbol_ptr)->izq);
        Destruir(&(*arbol_ptr)->der);
        free(*arbol_ptr);
    }
}

// Inserta num en el arbol
void Insertar(T_Arbol *arbol_ptr,unsigned num)
{
    if(*arbol_ptr == NULL){
        *arbol_ptr = malloc(sizeof(struct T_Nodo));
        (*arbol_ptr)->dato = num;
        (*arbol_ptr)->izq = NULL;
        (*arbol_ptr)->der = NULL;

    } else {
        if((*arbol_ptr)->dato != num){
            if((*arbol_ptr)->dato > num){
                Insertar(&((*arbol_ptr)->izq), num);
            } else {
                Insertar(&((*arbol_ptr)->der), num);
            }
        }
    }
}

// Muestra el contenido del árbol en InOrden
void Mostrar(T_Arbol arbol){
    if(arbol!=NULL){
        Mostrar(arbol->izq);
        printf("  %u  ",arbol->dato);
        Mostrar(arbol->der);
    }
}


// Guarda en disco el contenido del arbol - recorrido InOrden
void Salvar(T_Arbol arbol, FILE *fichero){
	if(arbol != NULL){
        Salvar(arbol->izq, fichero);
		fwrite(&(arbol->dato), sizeof(unsigned), 1, fichero);
        Salvar(arbol->der, fichero);
	}
}
