#include <stdio.h>
#include <string.h>

struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

int main(int argc, char const *argv[])
{
    struct str_Libro libro;

    strcpy(libro.autor, "Ursula K.Le Guin");
    strcpy(libro.titulo, "La mano izquierda de la oscuridad");
    libro.precio = 17.2;
    printf("Titulo: %s  \n Autor: %s \n Precio: %f euros", libro.titulo, libro.autor, libro.precio);
    return 0;
}
