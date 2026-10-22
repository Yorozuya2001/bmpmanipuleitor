
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
#include "funciones_grupo.h"




int main(int argc, char* argv[])
{
    
    //-------------------------------------------------------------- 
    // Variables

    FILE *archBMP;

    FILE *archBMP2;

    FILE *archSalida;

    Imagen regArch;

    Imagen regArch2;

    //Imagen regSalida;

    unsigned char ***matriz;

    unsigned char ***matriz2;

    int inicioDatosImg1,anchoImg1,altoImg1,tamPuntoImg1;

    int inicioDatosImg2,anchoImg2,altoImg2,tamPuntoImg2;

    //unsigned char ***matRed;
    char nombreSalida[500];
    char* p_nombreSalida=nombreSalida;
    int padding;
    //unsigned char *datosExtra;
    //int tamanioExtra;


    //Variables para argumentos
    int cantidadDeArgumentos = argc;
    char* filtro = argv[1];
    char* pathImagen1 = argv[2];
    char* pathImagen2 = argv[3];


    //-----------------------------------------------------------------------------------
    // Validacion de parametros

    int esConcatenar = 0;

    if (validarParametros(&cantidadDeArgumentos, filtro, pathImagen1, &esConcatenar) != TODO_OK){
        return FALLA;
    }

    //-----------------------------------------------------------------------------------
    //Apertura de Archivo1
    archBMP=abrirArchivo(pathImagen1,"rb");

    if (archBMP == NULL) {
        printf("No pudo abrir el archivo\n");
        return FALLA;
    }

    matriz = leerBMP(pathImagen1,&regArch,&inicioDatosImg1,&anchoImg1,&altoImg1,&tamPuntoImg1,archBMP);

    if(!matriz){
        printf("No se genero la matriz correctamente\n");
        return 0;
    }
    
    //-----------------------------------------------------------------------------------
    // Comprobacion de esConcatenar y apertura de archivo2

    if (esConcatenar)
    {
        archBMP2=abrirArchivo(pathImagen2,"rb");

        if (archBMP2 == NULL) {
            printf("No pudo abrir el archivo\n");
            return 0;
        }

        matriz2 = leerBMP(pathImagen2,&regArch2,&inicioDatosImg2,&anchoImg2,&altoImg2,&tamPuntoImg2,archBMP2);

        if (matriz2 == NULL)
        {
            liberarMatriz(matriz2, &regArch2.ancho, &regArch2.alto);
            return 0;
        }
    }


    //-----------------------------------------------------------------------------------
    // Aplicar filtro
    matriz = aplicarFiltro(matriz,filtro,&anchoImg1,&altoImg1,&padding, matriz2, &anchoImg2, &altoImg2);
    regArch.ancho = anchoImg1;
    regArch.alto  = altoImg1;


    //-----------------------------------------------------------------------------------
    // Crear nombre del archivo de salida
    p_nombreSalida=crearNombreSalida(nombreSalida, filtro + 2, pathImagen1);
    archSalida = fopen(p_nombreSalida, "wb");
    if (archSalida == NULL)
        return 1;


    //-----------------------------------------------------------------------------------
    // Crear archivo de salida
    generarArchSalida(nombreSalida,archBMP,archSalida,matriz,&padding,&regArch);
    fclose(archBMP);
    //free(datosExtra);
    liberarMatriz(matriz, &regArch.ancho, &regArch.alto);
    fclose(archSalida);
    printf("Archivo generado correctamente: %s\n", nombreSalida);
    return 0;
}
