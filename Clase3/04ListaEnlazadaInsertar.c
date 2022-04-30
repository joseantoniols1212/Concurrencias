#include <stdio.h>
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
1- Se proporciona el código para rellenar tres item de esa lista enlazada. ¿Cómo se puede insertar un nuevo elemento al principio de la lista? 

2.-Comenta el código anterior y prueba ahora, a insertarlo al final.

3. Ahora queremos mantener todos los libros al principio y las revistas al final de la lista. Prueba a generar dos punteros para recorrer la lista e insertar en el sitio que corresponde, antes de la primera revista. Ojo, que la lista podría estar vacía o podría contener sólo revistas.

*/

int main(int argc, char const *argv[])
{
    ptr_str_union_item lista = malloc(sizeof(struct str_union_item));
    (*lista).tipo='l';
    strcpy(lista->item.libro.titulo,"HOla mundo book");
    strcpy(lista->item.libro.autor,"Joaquin Ballesteros");
    lista->item.libro.paginas=100;
    lista->item.libro.precio=25.5;

    lista->siguiente= malloc(sizeof(struct str_union_item));
    lista->siguiente->tipo='l';
    strcpy(lista->siguiente->item.libro.titulo,"Hi there budy");
    strcpy(lista->siguiente->item.libro.autor,"Carlos Bustamante");
    lista->siguiente->item.libro.paginas=50;
    lista->siguiente->item.libro.precio=15.5;

    lista->siguiente->siguiente= malloc(sizeof(struct str_union_item));
    lista->siguiente->siguiente->tipo='r';
    strcpy(lista->siguiente->siguiente->item.revista.titulo,"Marca gol");
    lista->siguiente->siguiente->item.revista.mes=1;
    lista->siguiente->siguiente->item.revista.precio=3.5;
    lista->siguiente->siguiente->siguiente=NULL;

    //----
    ptr_str_union_item nuevo_elemento = malloc(sizeof(struct str_union_item));
    nuevo_elemento->tipo='l';
    strcpy(nuevo_elemento->item.libro.titulo,"Book nuevo");
    strcpy(nuevo_elemento->item.libro.autor,"Joaquin Cabagho");
    nuevo_elemento->item.libro.paginas=11;
    nuevo_elemento->item.libro.precio=12.5;
    nuevo_elemento->siguiente=NULL;

    // Insertar el nuevo elemento al comienzo de la lista.

    nuevo_elemento->siguiente=lista;
    lista = nuevo_elemento;

    //Insertar el nuevo elemento al final de la lista.

    // ptr_str_union_item ptr;
    // if(lista == NULL){
    //     lista = nuevo_elemento;
    //     nuevo_elemento->siguiente = NULL;
    // } else {
    //     ptr = lista;
    //     while(ptr->siguiente!=NULL){
    //         ptr=ptr->siguiente;
    //     }
    //     ptr->siguiente=nuevo_elemento;
    //     nuevo_elemento->siguiente=NULL;
    // }

    //Insertamos nuevo elemento en una lista ordenada con libros al principio y revistas al final.
    // Suponemos que la lista esta correctamente ordenada de manera previa.
    // Insertamos los nuevos objetos al final de su zona correspondiente.

    ptr_str_union_item ptr_libros,ptr_revistas,ptr;
    if(lista == NULL){
        lista = nuevo_elemento;
        lista->siguiente = NULL;
    } else {
        if(nuevo_elemento->tipo == 'l'){
            if(lista->tipo=='r'){
                nuevo_elemento->siguiente = lista;
                lista = nuevo_elemento;
            } else {
                ptr = lista;
                while(lista->siguiente!=NULL && lista->siguiente->tipo=='l'){
                    ptr = ptr->siguiente;
                }
                ptr->siguiente=nuevo_elemento;
                nuevo_elemento->siguiente=NULL; //Podriamos suponer que al añadirse se inicializa siguiente a NULL con lo que no haria falta.
            }
        } else{
            ptr = lista;
             while(lista->siguiente!=NULL && lista->siguiente->tipo=='l'){
                    ptr = ptr->siguiente;
                }
                ptr->siguiente=nuevo_elemento;
                nuevo_elemento->siguiente=NULL; //Podriamos suponer que al añadirse se inicializa siguiente a NULL con lo que no haria falta.
        }
    }
    
    
    return 0;
}
