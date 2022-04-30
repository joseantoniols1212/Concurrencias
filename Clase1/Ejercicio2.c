#include <stdio.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    float a,b;

    printf("Introduce los dos floats a multiplicar separados por espacio: \n");
    if(scanf("%f %f", &a, &b)==2){
        printf("Resultado: %.3f", a*b);
    } else {
        perror("Se esperaban dos flota separados por un espacio.");
    }
    return 0;
}
