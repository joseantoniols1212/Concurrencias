#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char cadena[15] = "123456789012345";
    char copia[50];

    strcpy(copia, cadena);
    printf("%s \n", copia);

    printf("%i", strlen(copia));

    if(strcmp(cadena,"123456789012345")==0){
        printf("Las cadenas son iguales");
    } else {
       printf("Las cadenas NO son iguales"); 
    }
    return 0;
}
