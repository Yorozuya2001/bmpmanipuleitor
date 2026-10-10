/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
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
int solucion(int argc, char* argv[])
{
    //#include "funciones_grupo.h"



int solucion(int argc, char* argv[])
{
   // argv [0] = nombre del archivo .exe -->  bmpmanipuleitor.exe
   // argv [1] = filtro                  -->  --negativo
   // argv [2] = nombre de la imagne     -->  359.bmp
   

    FILE *archBMP;
    FILE *archSalida;

    struct imagen regArch;
    struct imagen regSalida;

    unsigned char ***matriz;
    char nombreSalida[500];
    int padding;
    int i, j;
    unsigned char *datosExtra;
    int tamanioExtra;

    /* VALIDAR ARGUMENTOS */
    if (argc != 3)
    {
        printf("Uso:\n");
        printf("bmpmanipuleitor.exe --filtro imagen.bmp\n");
        return 1;
    }

    /* VALIDAR FILTRO */
    if (strcmp(argv[1], "--negativo") != 0 &&  strcmp(argv[1], "--escala-de-grises") != 0 &&
        strcmp(argv[1], "--espejar-horizontal") != 0 &&  strcmp(argv[1], "--espejar-vertical") != 0)
    {
        printf("Filtro no reconocido: %s\n", argv[1]);
        return 1;
    }

    /* ABRIR BMP */
    archBMP = fopen(argv[2], "rb");

    if (archBMP == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", argv[2]);
        return 1;
    }


     /* LEER CABECERA BMP */

    // Obtengo el tipo de archivo
    regArch.letra1 = fgetc(archBMP);
    regArch.letra2 = fgetc(archBMP);

    if (regArch.letra1 != 'B' || regArch.letra2 != 'M')
    {
        printf("El archivo no es un BMP valido.\n");
        fclose(archBMP);
        return 1;
    }

    // Obtengo el tamanio del archivo
    fseek(archBMP, 2, SEEK_SET);
    fread(&regArch.tamanio_archivo, 4, 1, archBMP);

    // Obtengo el primer campo reservado
    fseek(archBMP, 6, SEEK_SET);
    fread(&regArch.reservado1, 2, 1, archBMP);

    // Obtengo el segundo campo reservado
    fseek(archBMP, 8, SEEK_SET);
    fread(&regArch.reservado2, 2, 1, archBMP);

    // Obtengo inicio datos de la imagen
    fseek(archBMP, 10, SEEK_SET);
    fread(&regArch.inicio_datos_imagen, 4, 1, archBMP);

    // Obtengo tamanio de la cabecera
    fseek(archBMP, 14, SEEK_SET);
    fread(&regArch.tamanio_cabecera, 4, 1, archBMP);

    // Obtengo ancho
    fseek(archBMP, 18, SEEK_SET);
    fread(&regArch.ancho, 4, 1, archBMP);

    // Obtengo alto
    fseek(archBMP, 22, SEEK_SET);
    fread(&regArch.alto, 4, 1, archBMP);

    // Obtengo nro de planos
    fseek(archBMP, 26, SEEK_SET);
    fread(&regArch.nro_planos, 2, 1, archBMP);

    // Obtengo tamanio de cada punto
    fseek(archBMP, 28, SEEK_SET);
    fread(&regArch.tamanio_punto, 2, 1, archBMP);

    // Obtengo compresion
    fseek(archBMP, 30, SEEK_SET);
    fread(&regArch.compresion, 4, 1, archBMP);

    // Obtengo tamanio de la imagen
    fseek(archBMP, 34, SEEK_SET);
    fread(&regArch.tamanio_imagen, 4, 1, archBMP);

    // Obtengo resolucion horizontal
    fseek(archBMP, 38, SEEK_SET);
    fread(&regArch.resolucion_horizontal, 4, 1, archBMP);

    // Obtengo resolucion vertical
    fseek(archBMP, 42, SEEK_SET);
    fread(&regArch.resolucion_vertical, 4, 1, archBMP);

    // Obtengo tamanio de la tabla de color
    fseek(archBMP, 46, SEEK_SET);
    fread(&regArch.tamanio_tabla_color, 4, 1, archBMP);

    // Obtengo contador de colores importantes
    fseek(archBMP, 50, SEEK_SET);
    fread(&regArch.contador_colores_importantes, 4, 1, archBMP);


    //-----------------------------------------------------------------------------------//
    // bytes adicionales entre el final de la cabecera y el comienzo de los pixeles

    tamanioExtra = regArch.inicio_datos_imagen - 54;

    if (tamanioExtra < 0)
    {
        printf("Cabecera BMP invalida.\n");
        fclose(archBMP);
        return 1;
    }

    datosExtra = NULL;

    if (tamanioExtra > 0)
    {
        datosExtra = malloc(tamanioExtra);

        if (datosExtra == NULL)
        {
            printf("No se pudo reservar memoria para la cabecera.\n");
            fclose(archBMP);
            return 1;
        }

        fseek(archBMP, 54, SEEK_SET);

        if (fread(datosExtra, 1, tamanioExtra, archBMP) != tamanioExtra)
        {
            printf("Error al leer los datos adicionales.\n");
            free(datosExtra);
            fclose(archBMP);
            return 1;
        }
    }

    //-----------------------------------------------------------------------------------//


     /* VALIDAR BMP 24 BITS */
    if (regArch.tamanio_punto != 24)
    {
        printf("El BMP debe ser de 24 bits.\n");
        fclose(archBMP);
        return 1;
    }

    /* VALIDAR QUE NO ESTE COMPRIMIDA */
    if (regArch.compresion != 0)
    {
        printf("El BMP debe estar sin compresion.\n");
        fclose(archBMP);
        return 1;
    }

     /* Reservo memoria para la matriz que va a almacenar la imagen */
    matriz = reservarMatriz(regArch.ancho, regArch.alto);

    if (matriz == NULL)
    {
        printf("No se pudo reservar memoria.\n");
        fclose(archBMP);
        return 1;
    }

    // Me ubico al comienzo de la imagen, luego de los 54 bytes de la cabecera
    fseek(archBMP, regArch.inicio_datos_imagen, SEEK_SET);

    // Cada fila debe ocupar un múltiplo de 4 bytes. Se completan los bytes faltantes
    padding = (4 - (regArch.ancho * 3) % 4) % 4;

      /* LEER LOS PIXELES */
    // Se guardan las las filas desde abajo hacia arriba.
    // Fila 0 = parte superior

    for (i = regArch.alto - 1; i >= 0; i--)
    {
        for (j = 0; j < regArch.ancho; j++)
        {
            matriz[i][j][0] = fgetc(archBMP); /* B */
            matriz[i][j][1] = fgetc(archBMP); /* G */
            matriz[i][j][2] = fgetc(archBMP); /* R */
        }

        /* Ignorar padding */
        for (j = 0; j < padding; j++)
        {
            fgetc(archBMP);
        }
    }

    fclose(archBMP);

    /* APLICAR FILTRO */

    if (strcmp(argv[1], "--negativo") == 0)
    {
        negativo(matriz, regArch.ancho, regArch.alto);
    }
    else if (strcmp(argv[1], "--escala-de-grises") == 0)
    {
        escalaDeGrises(matriz, regArch.ancho, regArch.alto);
    }
    else if (strcmp(argv[1], "--espejar-horizontal") == 0)
    {
        espejarHorizontal(matriz, regArch.ancho, regArch.alto);
    }
    else if (strcmp(argv[1], "--espejar-vertical") == 0)
    {
        espejarVertical(matriz, regArch.ancho, regArch.alto);
    }


    /*  CREAR NOMBRE DEL ARCHIVO DE SALIDA */
    crearNombreSalida(nombreSalida, argv[1] + 2, argv[2]);


    /* CREAR ARCHIVO DE SALIDA */
    archSalida = fopen(nombreSalida, "wb");

    if (archSalida == NULL)
    {
        printf("No se pudo crear %s\n", nombreSalida);
        liberarMatriz(matriz, regArch.ancho, regArch.alto);
        return 1;
    }

    // recalcular tamaño
    regArch.tamanio_imagen = (regArch.ancho * 3 + padding) * regArch.alto;
    regArch.tamanio_archivo = regArch.inicio_datos_imagen + regArch.tamanio_imagen;

     /*  ESCRIBIR CABECERA BMP */
    fputc(regArch.letra1, archSalida);
    fputc(regArch.letra2, archSalida);

    fwrite(&regArch.tamanio_archivo, 4, 1, archSalida);
    fwrite(&regArch.reservado1, 2, 1, archSalida);
    fwrite(&regArch.reservado2, 2, 1, archSalida);
    fwrite(&regArch.inicio_datos_imagen, 4, 1, archSalida);
    fwrite(&regArch.tamanio_cabecera, 4, 1, archSalida);
    fwrite(&regArch.ancho, 4, 1, archSalida);
    fwrite(&regArch.alto, 4, 1, archSalida);
    fwrite(&regArch.nro_planos, 2, 1, archSalida);
    fwrite(&regArch.tamanio_punto, 2, 1, archSalida);
    fwrite(&regArch.compresion, 4, 1, archSalida);
    fwrite(&regArch.tamanio_imagen, 4, 1, archSalida);
    fwrite(&regArch.resolucion_horizontal, 4, 1, archSalida);
    fwrite(&regArch.resolucion_vertical, 4, 1, archSalida);
    fwrite(&regArch.tamanio_tabla_color, 4, 1, archSalida);
    fwrite(&regArch.contador_colores_importantes, 4, 1, archSalida);

    if (tamanioExtra > 0)
    {
        fwrite(datosExtra, 1, tamanioExtra, archSalida);
    }

    /*  LA NUEVA IMAGEN CON EL FILTRO APLICADO (ESCRIBIR PIXELES) */
    for (i = regArch.alto - 1; i >= 0; i--)
    {
        for (j = 0; j < regArch.ancho; j++)
        {
            fputc(matriz[i][j][0], archSalida); // B
            fputc(matriz[i][j][1], archSalida); // G
            fputc(matriz[i][j][2], archSalida); // R
        }

        /* Padding */
        for (j = 0; j < padding; j++)
        {
            fputc(0, archSalida);
        }
    }

    free(datosExtra);
    liberarMatriz(matriz, regArch.ancho, regArch.alto);

    fclose(archSalida);
    printf("Archivo generado correctamente: %s\n", nombreSalida);

    return 0;
}
