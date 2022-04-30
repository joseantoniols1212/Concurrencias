#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdlib.h>
struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

enum Meses { ENE, FEB, MAR, ABR, MAY, JUN, JUL, AGO, SEP, OCT, NOV, DIC };

struct str_Revisa_Mensual
{
    char titulo[200];
    enum Meses mes;
    float precio;
};

union u_Item{
    struct str_Libro libro;
    struct str_Revisa_Mensual revista;
};

typedef struct str_union_item * ptr_str_union_item;

struct str_union_item{
    union u_Item item;
    char tipo;
    ptr_str_union_item siguiente;  
};

/*
1.- Ahora vamos a leer el fichero que hemos creado antes haciendo uso de fscanf. Ojo que esta función no admite precisión como el printf, así que cosas como %2.2f o %0.5f serán simplemente %f. Mira la parte de Negated scanset que la vamos a usar para leer todo lo que está antes de una coma.

https://www.cplusplus.com/reference/cstdio/fscanf/
*/

void destruir(ptr_str_union_item * listt){
    ptr_str_union_item aux;
    while(*listt!=NULL){
        aux = *listt;
        *listt = (*listt)->siguiente;
        free(aux);
    }
    *listt == NULL;
}

int main(int argc, char const *argv[])
{

    if (argc!=2){
        printf("Se esperaban el nombre de fichero como parámetro de entrada");
        exit(-1);
    }

    ptr_str_union_item lista = NULL;



    FILE * ptr_file;
    if ((ptr_file = fopen(argv[1],"r"))==NULL){
        perror("Error al abrir el fichero");
        exit(-1);
    }
    
    char tipo;
    char titulo[200];
    float precio;
    //"tipo %c, Titulo %s, precio %.2f\n"

    //Usa:
    //    char que_tengo_delante = fgetc(ptr_file);
    //    int leidos = fscanf(ptr_file,"",&tipo,titulo,&precio);
    // Para debugear que estamos haciendo mal! 
    // Nunca sale a la primera :)

    // int leidos = fscanf(ptr_file, "tipo %c, Titulo %[^], precio %f \n", &tipo, titulo, &precio);
    // char que_tengo_delante = fgetc(ptr_file);
    
    ptr_str_union_item nuevo;
    while(fscanf(ptr_file,"tipo %c, Titulo %[^], precio %f \n",&tipo,titulo,&precio)==3){
        if((nuevo = malloc(sizeof(struct str_union_item)))==NULL) break;

        nuevo->siguiente = lista->siguiente;  
        lista = nuevo;

        nuevo->tipo = tipo;
        if(tipo == "l"){
            strcpy(nuevo->item.libro.titulo, titulo);
            nuevo->item.libro.precio = precio;
        } else if (tipo == "r"){
            strcpy(nuevo->item.revista.titulo, titulo);
            nuevo->item.revista.precio = precio;
        }
    }

    destruir(&lista);
    fclose(ptr_file);
    return 0;
}