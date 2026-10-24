#include "funciones_rosales.h"
#include "compartido.h"

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

            incremento = matriz[i][j][0] + ((float)*(porcent) / 100) * matriz[i][j][0];

            if (incremento > 255)
            {
                incremento = 255;
            }

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

            incremento = matriz[i][j][1] + ((float)*(porcent) / 100) * matriz[i][j][1];

            if (incremento > 255)
            {
                incremento = 255;
            }

            matriz[i][j][1] = incremento;
        }
    }

}

unsigned char ***recortarImagen(unsigned char ***matriz,int* ancho,int* alto,int* padding,int* porcent)
{
    int anchoOrig = *ancho;
    int altoOrig = *alto;
    int anchoNuevo = anchoOrig * (*porcent) / 100;
    int altoNuevo = altoOrig * (*porcent) / 100;
    int i, j;

    if (anchoNuevo < 1)
        anchoNuevo = 1;
    if (altoNuevo < 1)
        altoNuevo = 1;

    unsigned char ***nueva_matriz = reservarMatriz(anchoNuevo, altoNuevo);

    for (i = 0; i < altoNuevo; i++)
    {
        for (j = 0; j < anchoNuevo; j++)
        {
            nueva_matriz[i][j][0] = matriz[i][j][0];
            nueva_matriz[i][j][1] = matriz[i][j][1];
            nueva_matriz[i][j][2] = matriz[i][j][2];
        }
    }

    liberarMatriz(matriz, &anchoOrig, &altoOrig);

    *ancho = anchoNuevo;
    *alto = altoNuevo;
    *padding = (4 - (anchoNuevo * 3) % 4) % 4;

    return nueva_matriz;
}

///Deberá reescribir todos los pixeles, para que se ubiquen dentro de un marco determinado
  ///Para ello, deberiamos "redimensionar" la matriz donde guardamos los datos

unsigned char *** achicarImagen(unsigned char ***matriz,int* ancho, int* alto,int* porcent)
{

   int anchoOrig = *ancho;
   int altoOrig  = *alto;
   int anchoRed = anchoOrig * (*porcent) / 100;
   int altoRed  = altoOrig  * (*porcent) / 100;

    if (anchoRed < 1)
        anchoRed = 1;
    if (altoRed < 1)
        altoRed = 1;

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












