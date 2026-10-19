#include "funciones_bustillos.h"
#include "estructuras.h"
#include "funciones_viegas.h"
#include <stdlib.h>

void tonalidadRoja(unsigned char ***matriz, int ancho, int alto)
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

            incremento = matriz[i][j][2] + INCREMETO_ROJO * matriz[i][j][2];
            if (incremento > 255)
            {
                incremento = 255;
            }

            matriz[i][j][2] = incremento;
        }
    }
}



unsigned char ***concatenarHorizontal( unsigned char ***img1, int *ancho1, int *alto1, unsigned char ***img2, int ancho2, int alto2)
{
    int anchoNuevaImg = *ancho1 + ancho2;
    int altoNuevaImg = (*alto1 > alto2) ? *alto1 : alto2;
    int i, j, k;

    unsigned char ***salida = reservarMatriz(anchoNuevaImg, altoNuevaImg);

    if (salida == NULL)
        return NULL;

    // Rellenar con Rosa
    for (i = 0; i < altoNuevaImg; i++)
        for (j = 0; j < anchoNuevaImg; j++)
        {
            salida[i][j][0] = 255;
            salida[i][j][1] = 0;
            salida[i][j][2] = 255;
        }

    // Copio primera imagen
    for (i = 0; i < *alto1; i++)
        for (j = 0; j < *ancho1; j++)
            for (k = 0; k < 3; k++)
                salida[i][j][k] = img1[i][j][k];

    //Copio la segunda, donde termina el ancho de la primera
    for (i = 0; i < alto2; i++)
        for (j = 0; j < ancho2; j++)
            for (k = 0; k < 3; k++)
                salida[i][j + *ancho1][k] = img2[i][j][k];

    int anchoOriginal = *ancho1;
    int altoOriginal = *alto1;

    liberarMatriz(img1, &anchoOriginal, &altoOriginal);

    *ancho1 = anchoNuevaImg;
    *alto1 = altoNuevaImg;

    return salida;
}



unsigned char ***concatenarVertical(
    unsigned char ***img1, int *ancho1, int *alto1,
    unsigned char ***img2, int ancho2, int alto2)
{
    int anchoNuevaImg = (*ancho1 > ancho2) ? *ancho1 : ancho2;
    int altoNuevaImg = *alto1 + alto2;
    int i, j, k;

    unsigned char ***salida = reservarMatriz(anchoNuevaImg, altoNuevaImg);

    if (salida == NULL)
        return NULL;

    // Rellenar con Rosa
    for (i = 0; i < altoNuevaImg; i++)
        for (j = 0; j < anchoNuevaImg; j++)
        {
            salida[i][j][0] = 255;
            salida[i][j][1] = 0;
            salida[i][j][2] = 255;
        }

    // Copio primera imagen
    for (i = 0; i < *alto1; i++)
        for (j = 0; j < *ancho1; j++)
            for (k = 0; k < 3; k++)
                salida[i][j][k] = img1[i][j][k];

    // Copio segunda donde termina el alto de la primera
    for (i = 0; i < alto2; i++)
        for (j = 0; j < ancho2; j++)
            for (k = 0; k < 3; k++)
                salida[i + *alto1][j][k] = img2[i][j][k];

    int anchoOriginal = *ancho1;
    int altoOriginal = *alto1;

    liberarMatriz(img1, &anchoOriginal, &altoOriginal);

    *ancho1 = anchoNuevaImg;
    *alto1 = altoNuevaImg;

    return salida;
}

void comodin(unsigned char ***matriz, int ancho, int alto)
{
    int i, j, k;
    int brillo;

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            for (k = 0; k < 3; k++)
            {
                brillo = matriz[i][j][k] * INCREMETO_BRILLO;

                if (brillo > 255)
                    brillo = 255;

                matriz[i][j][k] = brillo;
            }
        }
    }
}
