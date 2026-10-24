#include <stdlib.h>
#include <stdio.h>

#include "funciones_bustillos.h"
#include "estructuras.h"
#include "funciones_viegas.h"


void tonalidadRoja(unsigned char ***matriz, int ancho, int alto, int *porcent)
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

            incremento = matriz[i][j][2] + *porcent * matriz[i][j][2];

            if (incremento > 255)
            {
                incremento = 255;
            }

            matriz[i][j][2] = (unsigned char)incremento;
        }
    }
}

void comodin(unsigned char ***matriz, int ancho, int alto)
{
    int i,j;
    int incremento_rojo,incremento_azul,incremento_verde;

    for(i=0;i<alto;i++){
        for(j=0;j<ancho;j++) {

            /*
                matriz[i][j][0] = B
                matriz[i][j][1] = G
                matriz[i][j][2] = R
            */

            // Modifico cada componente para obtener el tono sepia
            incremento_azul = (matriz[i][j][0] * COMODIN_INCREMENTO_AZUL_AZUL) + (matriz[i][j][1] * COMODIN_INCREMENTO_AZUL_VERDE) + (matriz[i][j][2] * COMODIN_INCREMENTO_AZUL_ROJO);
            incremento_verde = (matriz[i][j][0] * COMODIN_INCREMENTO_VERDE_AZUL) + (matriz[i][j][1] * COMODIN_INCREMENTO_VERDE_VERDE) + (matriz[i][j][2] * COMODIN_INCREMENTO_VERDE_ROJO);
            incremento_rojo = (matriz[i][j][0] * COMODIN_INCREMENTO_ROJO_AZUL) + (matriz[i][j][1] * COMODIN_INCREMENTO_ROJO_VERDE) + (matriz[i][j][2] * COMODIN_INCREMENTO_ROJO_ROJO);

            // Verifico que no me este pasando de 255
            incremento_azul = incremento_azul > 255 ? 255 : incremento_azul;
            incremento_verde = incremento_verde > 255 ? 255 : incremento_verde;
            incremento_rojo = incremento_rojo > 255 ? 255 : incremento_rojo;

            matriz[i][j][0] = incremento_azul;
            matriz[i][j][1] = incremento_verde;
            matriz[i][j][2] = incremento_rojo;
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


