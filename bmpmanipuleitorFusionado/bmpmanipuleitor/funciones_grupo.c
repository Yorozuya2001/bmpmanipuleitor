
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

    FILE *archBMP = NULL;

    FILE *archBMP2 = NULL;

    FILE *archSalida = NULL;

    Imagen regArch;

    Imagen regArch2;

    int codigo = TODO_OK;

    //Imagen regSalida;

    unsigned char ***matriz = NULL;

    unsigned char ***matriz2 = NULL;

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

    codigo = validarParametros(&cantidadDeArgumentos, filtro, pathImagen1, &esConcatenar);

    if (codigo != TODO_OK)
    {
        return salirConError(codigo);
    }

    //-----------------------------------------------------------------------------------
    //Apertura de Archivo1
    codigo = abrirArchivo(pathImagen1, "rb", &archBMP);

    if (codigo != TODO_OK)
    {
        return salirConError(codigo);
    }

    matriz = NULL;
    codigo = leerBMP(pathImagen1, &regArch, &inicioDatosImg1, &anchoImg1, &altoImg1,
                     &tamPuntoImg1, archBMP, &matriz);

    if (codigo != TODO_OK)
    {
        if (matriz != NULL)
        {
            liberarMatriz(matriz, &anchoImg1, &altoImg1);
        }
        return salirConError(codigo);
    }
    
    //-----------------------------------------------------------------------------------
    // Comprobacion de esConcatenar y apertura de archivo2

    if (esConcatenar)
    {
        codigo = abrirArchivo(pathImagen2, "rb", &archBMP2);

        if (codigo != TODO_OK)
        {
            liberarMatriz(matriz, &anchoImg1, &altoImg1);
            fclose(archBMP);
            return salirConError(codigo);
        }

        matriz2 = NULL;
        codigo = leerBMP(pathImagen2, &regArch2, &inicioDatosImg2, &anchoImg2, &altoImg2,
                         &tamPuntoImg2, archBMP2, &matriz2);

        if (codigo != TODO_OK)
        {
            if (matriz2 != NULL)
            {
                liberarMatriz(matriz2, &anchoImg2, &altoImg2);
            }
            liberarMatriz(matriz, &anchoImg1, &altoImg1);
            fclose(archBMP);
            return salirConError(codigo);
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
    {
        liberarMatriz(matriz, &regArch.ancho, &regArch.alto);
        fclose(archBMP);
        if (archBMP2 != NULL)
        {
            fclose(archBMP2);
        }
        return salirConError(ERROR_ABRIR_ARCHIVO);
    }


    //-----------------------------------------------------------------------------------
    // Crear archivo de salida
    codigo = generarArchSalida(nombreSalida,archBMP,archSalida,matriz,&padding,&regArch);

    if (codigo != TODO_OK)
    {
        fclose(archSalida);
        liberarMatriz(matriz, &regArch.ancho, &regArch.alto);
        fclose(archBMP);
        if (archBMP2 != NULL)
        {
            fclose(archBMP2);
        }
        return salirConError(codigo);
    }

    fclose(archBMP);

    //free(datosExtra);
    if (archBMP2 != NULL)
    {
        fclose(archBMP2);
    }

    liberarMatriz(matriz, &regArch.ancho, &regArch.alto);
    fclose(archSalida);
    printf("Archivo generado correctamente: %s\n", nombreSalida);
    return TODO_OK;
}
