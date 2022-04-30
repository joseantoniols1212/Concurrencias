#include <stdio.h>
#include <stdlib.h>
#include "Componentes.h"
#include <string.h>

/*
La rutina Lista_Vacia devuelve 1 si la lista que se le pasa
como parametro esta vacia y 0 si no lo esta.
*/
int Lista_Vacia(Lista lista){
  return lista == NULL;
}

/*Num_Elementos es una funcion a la que se le pasa un puntero a una lista 
y devuelve el numero de elementos de dicha lista.
*/
int Num_Elementos(Lista  lista){
  int cont = 0;
  while(lista != NULL){
    lista = lista->sig;
    cont++;
  }
  return cont;
}

/*
La rutina Adquirir_Componente se encarga de recibir los datos de un nuevo 
componente (codigo y texto) que se le introducen por teclado y devolverlos 
por los parametros pasados por referencia "codigo" y "texto".
*/
void Adquirir_Componente(long *codigo,char *texto){
  scanf("%lo %s", codigo, texto);
  fflush(stdout);
}

/*
La funcion Lista_Imprimir se encarga de imprimir por pantalla la lista 
enlazada completa que se le pasa como parametro.
*/
void Lista_Imprimir( Lista lista){
  while(lista != NULL) {
    printf("Codigo: %lo  Descripcion: %s \n",lista->codigoComponente, lista->textoFabricante);
    lista = lista->sig;
  }
}

/*
La funcion Lista_Salvar se encarga de guardar en el fichero binario 
"examen.dat" la lista enlazada completa que se le pasa como parametro. 
Para cada nodo de la lista, debe almacenarse en el fichero
el código y el texto de la componente correspondiente.
*/
void Lista_Salvar( Lista  lista) {
  FILE *f;

  if(!(f = fopen("examen.dat", "wb"))){
    perror("Error al abrir el fichero");
  }

  while(lista != NULL) {
    unsigned longitudCadena = strlen(lista->textoFabricante);
    fwrite(&(lista->codigoComponente), sizeof(long), 1, f);
    fwrite(&(lista->textoFabricante), sizeof(char), longitudCadena, f);
    fwrite(&longitudCadena, sizeof(unsigned), 1, f);
    lista = lista->sig;
  }

  fclose(f);
}

/*
La funcion Lista_Crear crea una lista enlazada vacia
de nodos de tipo Componente.
*/
Lista Lista_Crear() {
  return NULL;
}

/*
La funcion Lista_Agregar toma como parametro un puntero a una lista,
el código y el texto de un componente y  anyade un nodo al final de 
la lista con estos datos.
*/
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante) {
  Lista nuevo = malloc(sizeof(struct elemLista));
  strcpy(nuevo->textoFabricante ,textoFabricante);
  nuevo->codigoComponente = codigo;
  nuevo->sig = NULL;
  if(*lista == NULL){
    *lista = nuevo; 
  } else {
    Lista iter = *lista;
    while(iter->sig != NULL) {
      iter = iter->sig;
    }
    iter->sig = nuevo;
  }
}

/*
Lista_Extraer toma como parametro un puntero a una Lista y elimina el
Componente que se encuentra en su ultima posicion.
*/
void Lista_Extraer(Lista *lista) {
  if(*lista != NULL){
    if((*lista)->sig == NULL){
      free(*lista);
      *lista = NULL;
    } else {
      Lista iter = *lista;
      while(iter->sig->sig != NULL) {
        iter = iter->sig;
      }
      free(iter->sig);
      iter->sig = NULL;
    }
  }
}

/*
Lista_Vaciar es una funcion que toma como parametro un puntero a una Lista
y elimina todos sus Componentes.
*/
void Lista_Vaciar(Lista *lista){
  if(*lista != NULL){
    Lista_Vaciar(&(*lista)->sig);
    free(*lista);
    *lista = NULL;
  }
}

