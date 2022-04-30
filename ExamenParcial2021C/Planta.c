/*
 * Planta.c
 *
 *  Created on: 9 abr. 2021
 *      Author: RZP
 */


#include "Planta.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * crea una lista de habitaciones vacia
 */
void crear(ListaHab *lh) {
	*lh = NULL;
}

/**
 * En esta función se añade a la lista, la habitación con número nh,
 * cliente "nombre" y fecha de salida "fs".
 * Si ya existe una habitación numerada con nh en la lista se actualizan sus campos
 * con los nuevos valores ("nombre" y "fs").
 * Si no existe ninguna habitación con ese número, se inserta un nuevo nodo de manera que
 * la lista siempre esté ordenada con respecto a los números de las habitaciones (de
 * menor a mayor)
 */
void nuevoCliente(ListaHab *lh,unsigned nh,char *nombre,unsigned fs) {
	ListaHab nuevo;
	if(((nuevo = malloc(sizeof(struct Nodo)))==NULL)){
		perror("No se pudo pedir memoria para nuevo cliente.");
	} else {
		strcpy(nuevo->nombre, nombre);
		nuevo->fechaSalida = fs;
		nuevo->numHab = nh;
		if(*lh == NULL){

			*lh = nuevo;
			nuevo->sig = NULL;

		} else if((*lh)->numHab == nh) {

			nuevo->sig = (*lh)->sig;
			free(*lh);
			*lh = nuevo;

		} else {

			ListaHab anterior = *lh;
			ListaHab iter = anterior->sig;

			while(iter != NULL && iter->numHab < nh){
				iter = iter->sig;
				anterior = iter;
			}

			anterior->sig = nuevo;
			if(iter == NULL){
				nuevo->sig = NULL;
			} else if(iter->numHab == nh) {
				nuevo->sig = iter->sig;
				free(iter);
			} else { // iter->numHab > nh
				nuevo->sig = iter;
			}
		}
	}
}

/**
 * Escribe por la pantalla la información de cada una de las habitaciones
 * almacenadas en la lista.
 * El formato de salida debe ser:
 * \t habitacion "nh" ocupada por "nombre" con fecha de salida "fs"
 */
void imprimir(ListaHab lh) {
	while(lh != NULL){
		printf("\t Habitacion %u ocupada por %s con fecha de salida %u \n", lh->numHab, lh->nombre, lh->fechaSalida);
		lh = lh->sig;
	}
}

/**
 * Borra todos los nodos de la lista y la deja vacía
 */
void borrar(ListaHab *lh) {
	if(*lh != NULL){
		borrar(&(*lh)->sig);
		free(*lh);
	}
}

/**
 * Borra todos las habitaciones cuya fecha de salida es fs.
 */

void borrarFechaSalida(ListaHab *lh,unsigned fs) {
	ListaHab iter = *lh;
	ListaHab anterior = NULL;
	while(iter != NULL){
		if(iter->fechaSalida == fs){
			if(anterior == NULL){
				*lh = (*lh)->sig;
			} else {
				anterior->sig = iter->sig;
			}
			free(iter);
		}
		anterior = iter;
		iter = iter->sig;
	}

}

