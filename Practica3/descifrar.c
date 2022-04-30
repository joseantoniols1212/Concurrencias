#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned DELTA = 0x9e3779b9;

void decrypt(unsigned * v, unsigned * k){
    unsigned sum = 0xC6EF3720;

    for(int i = 0; i < 32; i++){
        v[1] -= ((v[0] << 4) + k[2])^(v[0]+sum)^((v[0]>>5)+k[3]);
        v[0] -= ((v[1] << 4) + k[0])^(v[1]+sum)^((v[1]>>5)+k[1]);
        sum -= DELTA;
    }
}

int main(int argc, char const *argv[])
{
    unsigned k[4]={128, 129, 130, 131};
    FILE *file_write, *file_read;

    if(argc!=3){
        perror("Error en el numero de argumentos\n");
        exit(-1);
    }

    if((file_read=fopen(argv[1], "rb")) == NULL){
        perror("Error archivo a encriptar no se ha podido abrir\n");
        exit(-1);
    }

    if((file_write=fopen(argv[2], "wb")) == NULL){
        perror("Error archivo a escribir no se ha podido abrir\n");
        exit(-1);
    }
    printf("Los archivos se han cargado correctamente.\n");

    unsigned tam_real,tam_file;
    if ((fread(&tam_real, sizeof(unsigned), 1, file_read)==1)){

        if(tam_real % 8 != 0){
            tam_file = tam_real - (tam_real%8) + 8;
        } else {
            tam_file = tam_real;
        }

        unsigned *buffer = malloc(tam_file);
        fread(buffer, tam_file,1,file_read);

        for(int i = 0; i < tam_file/sizeof(unsigned); i+=2){
            decrypt(&buffer[i], k);
        }

        fwrite(buffer, sizeof(char), tam_real, file_write);

    }

    fclose(file_read);
    fclose(file_write);
    
    return 0;
}
