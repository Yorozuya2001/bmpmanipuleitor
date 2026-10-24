
// #include "funciones_viegas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GRUPO "MATRICERO"


char* crearNombreSalida(char *salida, char *filtro, char *entrada)
{
    char *nombre;

    /*
        Buscar la última aparición de '/' o '\'
        para quedarnos solamente con el nombre del archivo.
    */

    nombre = strrchr(entrada, '\\');

    if (nombre == NULL)
        nombre = strrchr(entrada, '/');

    if (nombre == NULL)
        nombre = entrada;
    else
        nombre++;

    sprintf(salida, "%s_%s_%s", GRUPO, filtro, nombre);

    return salida;
}


void negativo(unsigned char ***matriz, int ancho, int alto)
{
    int i, j, k;

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            for (k = 0; k < 3; k++)
            {
                matriz[i][j][k] = 255 - matriz[i][j][k];
            }
        }
    }
}


void escalaDeGrises(unsigned char ***matriz, int ancho, int alto)
{
    int i, j;
    int promedio;

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            /*
                matriz[i][j][0] = B
                matriz[i][j][1] = G
                matriz[i][j][2] = R
            */

            promedio = (matriz[i][j][0] + matriz[i][j][1] + matriz[i][j][2]) / 3;

            matriz[i][j][0] = promedio;
            matriz[i][j][1] = promedio;
            matriz[i][j][2] = promedio;
        }
    }
}

void espejarHorizontal(unsigned char ***matriz, int ancho, int alto)
{
    int i, j, k;
    unsigned char aux;

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho / 2; j++)
        {
            for (k = 0; k < 3; k++)
            {
                aux = matriz[i][j][k];
                matriz[i][j][k] = matriz[i][ancho - 1 - j][k];
                matriz[i][ancho - 1 - j][k] = aux;
            }
        }
    }
}

void espejarVertical(unsigned char ***matriz, int ancho, int alto)
{
    int i, j, k;
    unsigned char aux;

    for (i = 0; i < alto / 2; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            for (k = 0; k < 3; k++)
            {
                aux = matriz[i][j][k];
                matriz[i][j][k] = matriz[alto - 1 - i][j][k];
                matriz[alto - 1 - i][j][k] = aux;
            }
        }
    }
}
