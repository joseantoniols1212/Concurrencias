#include <stdlib.h>
#include <stdio.h>
#include "gestion_tremor.h"

/* Muestra los episodios de tremor que ha tenido el usuario por orden cronológico, primero los más nuevos, se le pasa la cabeza de la lista  */
	void mostrar_nuevos2antiguos (T_Lista lista){
        if (lista!=NULL){
            mostrar_nuevos2antiguos(lista->sig);
            printf("Evento en %s con duracion %i\n",ctime(&(lista->fecha)),lista->duracion);
        }
    }



/* 
Registra un episodio de tremor, con su fecha y duración, OK es igual a 1 si se puede, 0 si no es posible pedir memoria
 */
	void registrar(T_Lista * ptr_lista_head, const time_t * fecha, unsigned duracion,unsigned* ok){
        T_Lista nuevo = (T_Lista) malloc(sizeof(struct T_Nodo));

        if(nuevo == NULL){
            *ok = 0;
        } else {
            *ok = 1;
        }

        nuevo->duracion = duracion;
        nuevo->fecha = *fecha;
        nuevo->sig = NULL;

        if(*ptr_lista_head == NULL){
            *ptr_lista_head = nuevo;
        } else {
            T_Lista aux = *ptr_lista_head;
            while(aux->sig != NULL) aux = aux->sig;
            aux->sig = nuevo;
        }
    }

/* 
Libera todos los episodios que son anteriores a la fecha dada. Devuelve el número que se ha eliminado.
 */
	int liberar(T_Lista * ptr_lista_head, const time_t *  fecha){
        int borrados = 0;

        T_Lista aux;
        while((*ptr_lista_head) != NULL && (*ptr_lista_head)->fecha < *fecha){
            aux = (*ptr_lista_head);
            (*ptr_lista_head) = (*ptr_lista_head)->sig;
            free(aux);
            borrados++;
        }
        return borrados;
    }

/* Destruye la estructura utilizada (libera todos los nodos de la lista. El parámetro manejador debe terminar apuntando a NULL */

	void destruir(T_Lista* ptr_lista_head){
        T_Lista aux;
        while(*ptr_lista_head != NULL){
            aux = *ptr_lista_head;
            *ptr_lista_head = (*ptr_lista_head)->sig;
            free(aux);
        }
    }