#include "funciones_valiente.h"
#include "funciones_viegas.h"

void modificarContraste(unsigned char ***matriz, int ancho, int alto,int porcentaje)
{
    int i,j,k;
    int valor;
    int nuevoValor;

    for( i = 0; i < alto; i++)
    {
        for(j = 0; j < ancho; j++)
        {
            for(k = 0; k < 3; k++)
            {
                valor = matriz[i][j][k];

                /* Formula para cada color */
                nuevoValor = ((valor - 128) * (100 + porcentaje)) / 100 + 128;

                if(nuevoValor > 255)
                {
                    nuevoValor = 255;
                }

                if(nuevoValor < 0)
                {
                    nuevoValor = 0;
                }

                matriz[i][j][k] = nuevoValor;
            }
        }
    }

};


unsigned char***rotarDerecha(unsigned char ***matriz,int ancho,int alto)
{
    int nuevoAlto = ancho;
    int nuevoAncho = alto;
    int i,j,k;

    unsigned char*** nuevo = reservarMatriz(nuevoAncho,nuevoAlto);

    /* Aquí se debe de manejar el error */
    if(!nuevo)
    {
        return NULL;
    }

    for(i = 0; i < alto; i++)
    {
        for(j= 0; j < ancho; j++)
        {
            for(k=0; k<3; k++)
            {
                nuevo[j][alto-1-i][k] = matriz[i][j][k];
            }
        }
    }

    return nuevo;
};

unsigned char ***rotarIzquierda(unsigned char ***matriz, int ancho, int alto)
{
    int nuevoAlto = ancho;
    int nuevoAncho = alto;
    int i, j, k;

    unsigned char ***nuevo = reservarMatriz(nuevoAncho, nuevoAlto);

    /* Aquí se debe de manejar el error */
    if(!nuevo)
    {
        return NULL;
    }

    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            for (k = 0; k < 3; k++)
            {
                nuevo[ancho-1-j][i][k] = matriz[i][j][k];
            }
        }
    }

    return nuevo;
}
