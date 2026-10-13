#include "funciones_rosales.h"
#include <stdlib.h>

void tonalidadAzul(unsigned char ***matriz, int ancho, int alto)
{
   int i, j;
   int incremento;

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            /*
                matriz[i][j][0] = B
                matriz[i][j][1] = G
                matriz[i][j][2] = R
            */

            incremento = matriz[i][j][0] + INTENSIDAD_AZUL * matriz[i][j][0];

            matriz[i][j][0] = incremento;
        }
    }
}

void tonalidadVerde(unsigned char ***matriz,int ancho,int alto)
{
  int i, j;
   int incremento;

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            /*
                matriz[i][j][0] = B
                matriz[i][j][1] = G
                matriz[i][j][2] = R
            */

            incremento = matriz[i][j][1] + INTENSIDAD_VERDE * matriz[i][j][1];

            matriz[i][j][1] = incremento;
        }
    }

}

void recortarImagen(int* ancho,int* alto,int* padding)
{

    *ancho = *ancho * RECORTE;
    *alto = *alto * RECORTE;

    *padding = (4 - (*ancho * 3) % 4) % 4;
}

///Deberá reescribir todos los pixeles, para que se ubiquen dentro de un marco determinado
  ///Para ello, deberiamos "redimensionar" la matriz donde guardamos los datos

unsigned char *** achicarImagen(unsigned char ***matriz,int* ancho, int* alto)
{

   *ancho = *ancho * REDUCCION;
   *alto = *alto * REDUCCION;

   ///Hacemos un realloc de la matriz
    int i, j;

    unsigned char ***nueva_matriz = realloc(matriz, *alto * sizeof(unsigned char **));

    if (nueva_matriz == NULL)
        return NULL;

    matriz = nueva_matriz;

    for (i = 0; i < *alto; i++)
    {
        unsigned char **fila= realloc(matriz[i],*ancho * sizeof(unsigned char *));

        if (fila == NULL)
            return NULL;

        matriz[i]=fila;

        for (j = 0; j < *ancho; j++)
        {
            unsigned char *elem= realloc(matriz[i][j],3 * sizeof(unsigned char));

            if (elem == NULL)
                return NULL;

            matriz[i][j]=elem;
        }
     }
    return matriz;

}










