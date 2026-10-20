#include "funciones_rosales.h"
#include "funciones_viegas.h"
#include <stdlib.h>

void tonalidadAzul(unsigned char ***matriz, int ancho, int alto,int* porcent)
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

            incremento = matriz[i][j][0] + *porcent * matriz[i][j][0];

            matriz[i][j][0] = incremento;
        }
    }
}

void tonalidadVerde(unsigned char ***matriz,int ancho,int alto,int* porcent)
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

            incremento = matriz[i][j][1] + *porcent * matriz[i][j][1];

            matriz[i][j][1] = incremento;
        }
    }

}

void recortarImagen(int* ancho,int* alto,int* padding,int* porcent)
{

    *ancho = *ancho * (*porcent);
    *alto = *alto * (*porcent);

    *padding = (4 - (*ancho * 3) % 4) % 4;
}

///Deberá reescribir todos los pixeles, para que se ubiquen dentro de un marco determinado
  ///Para ello, deberiamos "redimensionar" la matriz donde guardamos los datos

unsigned char *** achicarImagen(unsigned char ***matriz,int* ancho, int* alto,int* porcent)
{

   int anchoOrig = *ancho;
   int altoOrig  = *alto;
   int anchoRed = anchoOrig * (*porcent);
   int altoRed  = altoOrig  * (*porcent);

    unsigned char ***nueva_matriz = reservarMatriz(anchoRed,altoRed);

    float pasoX = (float)anchoOrig / (float)anchoRed;
    float pasoY = (float)altoOrig  / (float)altoRed;

    for (int i = 0; i < altoRed; i++) {
        for (int j = 0; j < anchoRed; j++) {
            int io = (int)(i * pasoY);
            int jo = (int)(j * pasoX);
            nueva_matriz[i][j][0] = matriz[io][jo][0];
            nueva_matriz[i][j][1] = matriz[io][jo][1];
            nueva_matriz[i][j][2] = matriz[io][jo][2];
        }
    }

     liberarMatriz(matriz,&anchoOrig,&altoOrig);

    *ancho = anchoRed;
    *alto  = altoRed;

    return nueva_matriz;
}












