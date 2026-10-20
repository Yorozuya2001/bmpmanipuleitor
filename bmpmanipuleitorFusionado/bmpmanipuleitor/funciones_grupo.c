
/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Bustillos
    Nombre: Juan Ignacio
    DNI: 46876304
    Entrega: Sí
    -----------------
    Apellido:Rosales
    Nombre: Gustavo Mauricio
    DNI: 43665940
    Entrega:Sí
    -----------------
    Apellido: Valiente
    Nombre: Axel Ariel
    DNI: 43202499
    Entrega: Sí
    -----------------
	Apellido: Viegas
    Nombre: Chloe Jacqueline Micol
    DNI: 35361882
    Entrega: Sí
    -----------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include <string.h>
#include "funciones_viegas.h"
#include "funciones_rosales.h"
#include "compartido.h"



int main(int argc, char* argv[])
{
   // argv [0] = nombre del archivo .exe -->  bmpmanipuleitor.exe
   // argv [1] = filtro                  -->  --negativo
   // argv [2] = nombre de la imagne     -->  359.bmp


    FILE *archBMP;
    FILE *archSalida;

    struct imagen regArch;
    //struct imagen regSalida;

    unsigned char ***matriz;
    int inicioDatos,ancho,alto,tamPunto;

    //unsigned char ***matRed;
    char nombreSalida[500];
    char* p_nombreSalida=nombreSalida;
    int padding;
    //unsigned char *datosExtra;
    //int tamanioExtra;

    /* VALIDAR ARGUMENTOS */
    validarParametros(&argc,argv[1],argv[2]);

    ///Apertura de Archivo
    archBMP=abrirArchivo(argv[2],"rb");


    ///Obtencion de datos/propiedades del archivo: alto, ancho,tamanio,etc
    ancho=obtener_Ancho(archBMP,&regArch);
    alto=obtener_Alto(archBMP,&regArch);
    tamPunto=obtener_TamPixeles(archBMP,&regArch);
    inicioDatos=obtener_InicioDatos(archBMP,&regArch);





    //-----------------------------------------------------------------------------------//
    // bytes adicionales entre el final de la cabecera y el comienzo de los pixeles

    ///El encabezado del archivo tiene 54 bytes
    validar_cabecera(archBMP,&inicioDatos);
     /* VALIDAR BMP 24 BITS */
    validar_profundidad(archBMP,&tamPunto);

   /* Reservo memoria para la matriz que va a almacenar la imagen */
    matriz = reservarMatriz(regArch.ancho, regArch.alto);
    //matriz2= reservarMatriz(regArch.ancho,regArch.alto);

    ///Cargar imagen en matriz
    cargarImagen_Matriz(archBMP,matriz,&inicioDatos,&ancho,&alto);

    fclose(archBMP);

    ///Menu de opciones
    aplicarFiltro(matriz,argv[1],&ancho,&alto,&padding);

    ///Apertura del archivo de salida




    /*  CREAR NOMBRE DEL ARCHIVO DE SALIDA */
    p_nombreSalida=crearNombreSalida(nombreSalida, argv[1] + 2, argv[2]);

    archSalida=abrirArchivo(p_nombreSalida,"wb");


    /* CREAR ARCHIVO DE SALIDA */
    generar_ArchSalida(nombreSalida,archBMP,archSalida,matriz,&padding,&regArch);

    //free(datosExtra);
    liberarMatriz(matriz, &regArch.ancho, &regArch.alto);

    fclose(archSalida);
    printf("Archivo generado correctamente: %s\n", nombreSalida);

    return 0;
}
