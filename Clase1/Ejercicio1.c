#include <stdio.h>

int main(int argc, char const *argv[])
{
    char cadena[11] = "Hola mundo";
    int a = 65;
    float b = 65.0;
    printf("Esto es una cadena %s,  un entero  %-5c y un float %.2f  \n", cadena, a ,b);
    return 0;
}
