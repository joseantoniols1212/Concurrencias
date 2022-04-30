#include <stdio.h>
#include <stdlib.h>
#include "cifrado.h"

void crearEsquemaDeCifrado (TCifrado *cf){
  *cf = NULL;
}

void insertarBox (TCifrado * cf, struct TBox box, unsigned char *ok) {
  *ok = 1;
  if(*cf == NULL) {
    if(!box.esSBox) *ok = 0; // El primero debe ser SumaBox
    *cf = &box;
  } else {
    TCifrado iter = *cf;
    while (iter != NULL) {
      iter = iter->sig;
    }
    if(iter->esSBox == box.esSBox) *ok = 0; //En este caso no se alterna SumaBox y XorBox
    else {
      iter->sig = &box;
    }
  }
}

unsigned char aplicarBox (struct TBox box, unsigned char valor){
  if(box.esSBox){
    return valor+box.valorASumar;
  } else {
    if(box.bitACambiar){
      return valor^0x80;
    } else {
      return valor^0x01;
    }
  }
}

unsigned char aplicarEsquemaDeCifrado(TCifrado cf, unsigned char valor) {
  while(cf != NULL) {
    valor = aplicarBox(*cf, valor);
    cf = cf->sig;
  }
  return valor;
}

void escribirAFichero(char *nm, TCifrado cf) {
  FILE * f;
  if(((f=fopen(nm, "wb"))==NULL)){
    perror("No se ha podido abrir el archivo");
  }
  while(cf != NULL) {
    fwrite(&cf->esSBox, sizeof(unsigned char), 1, f);
    if(cf->esSBox){
      fwrite(&cf->valorASumar, sizeof(unsigned char), 1, f);
    } else {
      fwrite(&cf->bitACambiar, sizeof(unsigned char), 1, f);
    }
    cf = cf->sig;
  } 
  fclose(f);
}

void destruirEsquemaDeCifrado (TCifrado *cf) {
  if(*cf != NULL){
    destruirEsquemaDeCifrado(&(*cf)->sig);
    free(*cf);
  }
}


