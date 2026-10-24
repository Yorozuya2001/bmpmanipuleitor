#include "compartido.h"
#include <string.h>
#include <stdlib.h>
#include "funciones_viegas.h"
#include "funciones_rosales.h"
#include "funciones_valiente.h"
#include "funciones_bustillos.h"

static int filtroLlevaPorcentaje(const char *nombreFiltro)
{
    if (strcmp(nombreFiltro, FILTRO_AUMENTAR_CONTRASTE) == 0)
    {
        return 1;
    }
    if (strcmp(nombreFiltro, FILTRO_REDUCIR_CONTRASTE) == 0)
    {
        return 1;
    }
    if (strcmp(nombreFiltro, FILTRO_TONALIDAD_AZUL) == 0)
    {
        return 1;
    }
    if (strcmp(nombreFiltro, FILTRO_TONALIDAD_ROJA) == 0)
    {
        return 1;
    }
    if (strcmp(nombreFiltro, FILTRO_TONALIDAD_VERDE) == 0)
    {
        return 1;
    }
    if (strcmp(nombreFiltro, FILTRO_RECORTAR) == 0)
    {
        return 1;
    }
    if (strcmp(nombreFiltro, FILTRO_ACHICAR) == 0)
    {
        return 1;
    }
    return 0;
}

int validarParametros(int* argc,const char* filtro,const char* pathImagen, int *esConcatenar)
{
    // argv [0] = nombre del archivo .exe -->  bmpmanipuleitor.exe
    // argv [1] = filtro                  -->  --negativo
    // argv [2] = nombre de la imagen 1   -->  <img1>.bmp
    // argv [2] = nombre de la imagen 2   -->  <img2>.bmp

    int filtroAccedido=0;
    char nombreFiltro[50];
    int porcentaje = 0;
    int i;
    int cantidadFiltros;
    int tieneIgual;

    if ((*argc >= 2) && (strcmp(filtro, "--concatenar-horizontal") == 0 || strcmp(filtro, "--concatenar-vertical") == 0)) {
        *esConcatenar = 1;
    }

    if ((!*esConcatenar && *argc != 3) || (*esConcatenar && *argc != 4))
    {

        return ARGUMENTO_INVALIDO;
    }

    const char *listado_Funciones[] =
    {
        FILTRO_NEGATIVO,
        FILTRO_ESCALA_DE_GRISES,
        FILTRO_ESPEJAR_HORIZONTAL,
        FILTRO_ESPEJAR_VERTICAL,
        FILTRO_AUMENTAR_CONTRASTE,
        FILTRO_REDUCIR_CONTRASTE,
        FILTRO_TONALIDAD_AZUL,
        FILTRO_TONALIDAD_ROJA,
        FILTRO_TONALIDAD_VERDE,
        FILTRO_RECORTAR,
        FILTRO_ACHICAR,
        FILTRO_ROTAR_DERECHA,
        FILTRO_ROTAR_IZQUIERDA,
        FILTRO_CONCATENAR_HORIZONTAL,
        FILTRO_CONCATENAR_VERTICAL,
        FILTRO_COMODIN
    };

    tieneIgual = (strchr(filtro, '=') != NULL);

    if (tieneIgual)
    {
        if (sscanf(filtro, "%49[^=]=%d", nombreFiltro, &porcentaje) != 2)
        {
            return ARGUMENTO_INVALIDO;
        }
        if (porcentaje < 0 || porcentaje > 100)
        {
            return PORCENTAJE_INVALIDO;
        }
    }
    else
    {
        strcpy(nombreFiltro, filtro);
    }

    ///Validar ingreso de filtro
    cantidadFiltros = (int)(sizeof(listado_Funciones) / sizeof(listado_Funciones[0]));
    for(i = 0; i < cantidadFiltros; i++)
    {
        if(strcmp(nombreFiltro, listado_Funciones[i]) == 0)
        {
            filtroAccedido=1;
        }
    }

    if(filtroAccedido==0)
    {
        return FILTRO_NO_RECONOCIDO;
    }

    if (filtroLlevaPorcentaje(nombreFiltro) && !tieneIgual)
    {
        return ARGUMENTO_INVALIDO;
    }

    ///Validar extension de la imagen
    if(strstr(pathImagen,EXTENSION_BMP)==NULL)
    {
        return  ERROR_EXTENSION;

    }

    return TODO_OK;

}

int validarCabecera(FILE* archBMP,int* inicioDatos)
{
    int tamanioExtra = *inicioDatos - 54;
    unsigned char *datosExtra;

    if (tamanioExtra < 0)
    {
        fclose(archBMP);
        return CABECERA_INVALIDA;
    }

    datosExtra = NULL;

    if (tamanioExtra > 0)
    {
        datosExtra = malloc(tamanioExtra);

        if (datosExtra == NULL)
        {
            fclose(archBMP);
            return SIN_MEMORIA;
        }

        fseek(archBMP, 54, SEEK_SET);

        if (fread(datosExtra, 1, tamanioExtra, archBMP) != (size_t)tamanioExtra)
        {
            free(datosExtra);
            fclose(archBMP);
            return ERROR_LECTURA_ARCHIVO;
        }
        free(datosExtra);
    }

    return TODO_OK;
}

int validarProfundidad(FILE* archBMP,int* tamPunto)
{
    if (*tamPunto != 24)
    {
        fclose(archBMP);
        return PROFUNDIDAD_INVALIDA;
    }

    return TODO_OK;
}


int abrirArchivo(char *nombreArchivo, const char *modoApertura, FILE **archivo)
{
    int c1;
    int c2;

    *archivo = fopen(nombreArchivo, modoApertura);

    if (*archivo == NULL)
    {
        return ERROR_ABRIR_ARCHIVO;
    }

    /* LEER CABECERA BMP */

    // Obtengo el tipo de archivo
    c1 = fgetc(*archivo); ///Fgetc lee caracteres individualmente y devuelve un int como valor ASCII del caracter
    c2 = fgetc(*archivo);

    if (c1 != 'B' || c2 != 'M')
    {
        fclose(*archivo);
        *archivo = NULL;
        return ARCHIVO_NO_BMP;
    }

    rewind(*archivo);
    return TODO_OK;
}

int obtenerTamArchivo(FILE* archBMP,Imagen* reg)
{

    int tamArchivo;

    fseek(archBMP, 2, SEEK_SET);
    fread(&reg->tamanio_archivo, 4, 1, archBMP);
    tamArchivo=reg->tamanio_archivo;

    return tamArchivo;
}


int obtenerInicioDatos(FILE* archBMP,Imagen* reg)
{

    int inicioDatos;

    fseek(archBMP, 10, SEEK_SET);
    fread(&reg->inicio_datos_imagen, 4, 1, archBMP);
    inicioDatos=reg->inicio_datos_imagen;

    return inicioDatos;


}

int obtenerTamCabecera(FILE* archBMP,Imagen* reg)
{

    int tamCabecera;

    fseek(archBMP, 14, SEEK_SET);
    fread(&reg->tamanio_cabecera, 4, 1, archBMP);
    tamCabecera=reg->tamanio_cabecera;

    return tamCabecera;


}

int obtenerAncho(FILE* archBMP,Imagen* reg)
{
    int anchoImagen;


    fseek(archBMP, 18, SEEK_SET);
    fread(&reg->ancho, 4, 1, archBMP);
    anchoImagen=reg->ancho;

    return anchoImagen;


}

int obtenerNroPlanos(FILE* archBMP,Imagen* reg)
{

    int nroPlanos;


    fseek(archBMP, 26, SEEK_SET);
    fread(&reg->nro_planos, 2, 1, archBMP);
    nroPlanos=reg->nro_planos;

    return nroPlanos;
}

int obtenerCompresion(FILE* archBMP,Imagen* reg)
{

    int compresion;

    fseek(archBMP, 30, SEEK_SET);
    fread(&reg->compresion, 4, 1, archBMP);
    compresion=reg->compresion;

    return compresion;
}

int obtenerResolHorizontal(FILE* archBMP,Imagen* reg)
{

    int resolHorizontal;

    fseek(archBMP, 38, SEEK_SET);
    fread(&reg->resolucion_horizontal, 4, 1, archBMP);
    resolHorizontal=reg->resolucion_horizontal;

    return resolHorizontal;

}
int obtenerResolVertical(FILE* archBMP, Imagen* reg)
{

    int resolVertical;

    fseek(archBMP, 42, SEEK_SET);
    fread(&reg->resolucion_vertical, 4, 1, archBMP);
    resolVertical=reg->resolucion_vertical;

    return resolVertical;
}

int obtenerTamTablaColor(FILE* archBMP,Imagen* reg)
{
    int tamTabla_color;

    fseek(archBMP, 46, SEEK_SET);
    fread(&reg->tamanio_tabla_color, 4, 1, archBMP);
    tamTabla_color=reg->tamanio_tabla_color;


    return tamTabla_color;
}

int obtenerContColorImportantes(FILE* archBMP,Imagen* reg)
{
    int contador;


    fseek(archBMP, 50, SEEK_SET);
    fread(&reg->contador_colores_importantes, 4, 1, archBMP);
    contador=reg->contador_colores_importantes;

    return contador;
}


int obtenerAlto(FILE* archBMP,Imagen* reg)
{
    int altoImagen;

    fseek(archBMP, 22, SEEK_SET);
    fread(&reg->alto, 4, 1, archBMP);
    altoImagen=reg->alto;

    return altoImagen;
}

int obtenerTamPixeles(FILE* archBMP,Imagen* reg)
{
    int tamPixeles;

    fseek(archBMP, 28, SEEK_SET);
    fread(&reg->tamanio_punto, 2, 1, archBMP);
    tamPixeles=reg->tamanio_punto;

    return tamPixeles;

}

int obtenerTamImagen(FILE* archBMP, Imagen* reg)
{
    int tamImagen;

    fseek(archBMP, 34, SEEK_SET);
    fread(&reg->tamanio_imagen, 4, 1, archBMP);
    tamImagen=reg->tamanio_imagen;

    return tamImagen;

}

int obtenerPrimerReservado(FILE* archBMP,Imagen* reg)
{
    int primerCampo;


    // Obtengo el primer campo reservado
    fseek(archBMP, 6, SEEK_SET);
    fread(&reg->reservado1, 2, 1, archBMP);
    primerCampo=reg->reservado1;

    return primerCampo;
}

int obtenerSegundoReservado(FILE* archBMP,Imagen* reg)
{

    int segundoCampo;

    // Obtengo el segundo campo reservado
    fseek(archBMP, 8, SEEK_SET);
    fread(&reg->reservado2, 2, 1, archBMP);
    segundoCampo=reg->reservado2;

    return segundoCampo;


}

/*Funciones de Procesamiento*/

int cargarImagenMatriz(FILE* archBMP,unsigned char*** matriz,int* inicioDatos,int* ancho,int* alto)
{
    fseek(archBMP,*inicioDatos, SEEK_SET);

    int padding = (4 - (*ancho * 3) % 4) % 4;
    int i,j;

    /* LEER LOS PIXELES */
    // Se guardan las las filas desde abajo hacia arriba.
    // Fila 0 = parte superior

    for (i = *alto - 1; i >= 0; i--)
    {
        for (j = 0; j < *ancho; j++)
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

    return TODO_OK;

}


///Menu de opciones que ejecuta las funcionalidades en base al filtro ingresado
unsigned char*** aplicarFiltro(unsigned char*** matriz,const char* filtro,int* ancho, int* alto,int* padding,unsigned char*** matriz2,int* anchoImg2, int* altoImg2)
{

    int porcentaje;

    ///Funcionalidades que reciben porcentaje como argumento
    char filtrosxPorcent[7][30]=
    {
        FILTRO_AUMENTAR_CONTRASTE,
        FILTRO_REDUCIR_CONTRASTE,
        FILTRO_TONALIDAD_AZUL,
        FILTRO_TONALIDAD_VERDE,
        FILTRO_TONALIDAD_ROJA,
        FILTRO_RECORTAR,
        FILTRO_ACHICAR
    };
    char nombreFiltro[50];

    for(int i=0; i<=6; i++)
    {
        if(strstr(filtro,filtrosxPorcent[i])!=NULL)
        {
            sscanf(filtro, "%49[^=]=%d", nombreFiltro, &porcentaje);
        }

    }
    //printf("\n%s\n%s ----\n ",filtro,nombreFiltro);
    if (strcmp(filtro, FILTRO_NEGATIVO) == 0)
    {
        negativo(matriz,*ancho,*alto);
    }
    else if (strcmp(filtro, FILTRO_ESCALA_DE_GRISES) == 0)
    {
        escalaDeGrises(matriz,*ancho,*alto);
    }
    else if (strcmp(filtro, FILTRO_ESPEJAR_HORIZONTAL) == 0)
    {
        espejarHorizontal(matriz,*ancho,*alto);
    }
    else if (strcmp(filtro, FILTRO_ESPEJAR_VERTICAL) == 0)
    {
        espejarVertical(matriz,*ancho,*alto);
    }

    ///Probamos funcionalidades nuevas propias(Rosales)
    else if (strcmp(nombreFiltro, FILTRO_TONALIDAD_AZUL) == 0)
    {
        tonalidadAzul(matriz,*ancho,*alto,&porcentaje);
    }

    else if (strcmp(nombreFiltro, FILTRO_TONALIDAD_VERDE) == 0)
    {
        tonalidadVerde(matriz,*ancho,*alto,&porcentaje);
    }

    else if (strcmp(nombreFiltro, FILTRO_TONALIDAD_ROJA) == 0)
    {
        tonalidadRoja(matriz, *ancho, *alto, &porcentaje);
    }

    else if (strcmp(nombreFiltro, FILTRO_RECORTAR) == 0)
    {
        unsigned char*** mat;
        mat = recortarImagen(matriz, ancho, alto, padding, &porcentaje);
        return mat;
    }

    else if (strcmp(nombreFiltro, FILTRO_ACHICAR) == 0)
    {
        unsigned char*** mat;
        mat=achicarImagen(matriz,ancho,alto,&porcentaje);
        return mat;
    }

    ///AcÃ¡ agregan la llamada al resto de las funciones
    else if(strcmp(nombreFiltro,FILTRO_AUMENTAR_CONTRASTE) == 0)
    {
        modificarContraste(matriz,*ancho,*alto,porcentaje);

    }
    else if(strcmp(nombreFiltro,FILTRO_REDUCIR_CONTRASTE) == 0)
    {
        modificarContraste(matriz,*ancho,*alto,porcentaje * -1);
    }
    else if(strcmp(filtro,FILTRO_ROTAR_DERECHA)== 0)
    {
        unsigned char ***mat;
        int w = *ancho;
        int h = *alto;
        mat = rotarDerecha(matriz, w, h);
        *ancho = h;   /* nuevo ancho = alto viejo */
        *alto  = w;   /* nuevo alto = ancho viejo */
        liberarMatriz(matriz, &w, &h);   /* liberar con tamaño VIEJO */
        return mat;
    }
    else if(strcmp(filtro,FILTRO_ROTAR_IZQUIERDA) == 0)
    {
        unsigned char ***mat;
        int w = *ancho;
        int h = *alto;
        mat = rotarIzquierda(matriz, w, h);
        *ancho = h;
        *alto  = w;
        liberarMatriz(matriz, &w, &h);
        return mat;
    }
    else if (strcmp(filtro, "--comodin") == 0)
    {
        comodin(matriz,*ancho,*alto);
    }
    else if (strcmp(filtro, "--concatenar-horizontal") == 0)
    {
        //Creo una nueva matriz con las dimisiones de las 2 imagenes
        matriz = concatenarHorizontal(matriz, ancho, alto, matriz2, *anchoImg2, *altoImg2);

        // Libero la memoria que ya no uso
        liberarMatriz(matriz2, anchoImg2, altoImg2);

    }
    else if (strcmp(filtro, "--concatenar-vertical") == 0)
    {
        //Creo una nueva matriz con las dimisiones de las 2 imagenes
        matriz = concatenarVertical(matriz, ancho, alto, matriz2, *anchoImg2, *altoImg2);
        //Libero la meme que ya no uso
        liberarMatriz(matriz2, anchoImg2,altoImg2);

    }

    return matriz;

}

int generarArchSalida(char* nombreSalida,FILE* archBMP,FILE* archSalida,unsigned char*** matriz,int* padding,Imagen* reg)
{
    int tamImagen;
    int tamArchivo;
    const int tamCabecera = 40;
    const int inicioDatos = 54;

    (void)archBMP;

    if (archSalida == NULL)
    {
        archSalida = fopen(nombreSalida, "wb");
        if (archSalida == NULL)
        {
            liberarMatriz(matriz,&reg->ancho,&reg->alto);
            return ERROR_ABRIR_ARCHIVO;
        }
    }

    *padding = (4 - (reg->ancho * 3) % 4) % 4;

    tamImagen = (reg->ancho * 3 + *padding) * reg->alto;
    tamArchivo = inicioDatos + tamImagen;


    reg->letra1 = 'B';
    reg->letra2 = 'M';
    reg->tamanio_archivo = tamArchivo;
    reg->inicio_datos_imagen = inicioDatos;
    reg->tamanio_cabecera = tamCabecera;
    reg->tamanio_imagen = tamImagen;
    reg->tamanio_tabla_color = 0;
    reg->contador_colores_importantes = 0;
    reg->compresion = 0;


     //-----------------------------------------------------------------------------------
    // escribir cabecera BMP
    fputc(reg->letra1, archSalida);
    fputc(reg->letra2, archSalida);

    fwrite(&tamArchivo, 4, 1, archSalida);
    fwrite(&reg->reservado1, 2, 1, archSalida);
    fwrite(&reg->reservado2, 2, 1, archSalida);
    fwrite(&reg->inicio_datos_imagen, 4, 1, archSalida);
    fwrite((void *)&tamCabecera, 4, 1, archSalida);
    fwrite(&reg->ancho, 4, 1, archSalida);
    fwrite(&reg->alto, 4, 1, archSalida);
    fwrite(&reg->nro_planos, 2, 1, archSalida);
    fwrite(&reg->tamanio_punto, 2, 1, archSalida);
    fwrite(&reg->compresion, 4, 1, archSalida);
    fwrite(&tamImagen, 4, 1, archSalida);
    fwrite(&reg->resolucion_horizontal, 4, 1, archSalida);
    fwrite(&reg->resolucion_vertical, 4, 1, archSalida);
    fwrite(&reg->tamanio_tabla_color, 4, 1, archSalida);
    fwrite(&reg->contador_colores_importantes, 4, 1, archSalida);


    /*LA NUEVA IMAGEN CON EL FILTRO APLICADO (ESCRIBIR PIXELES)*/
    for (int i = reg->alto - 1; i >= 0; i--)
    {
        for (int j = 0; j < reg->ancho ; j++)
        {
            fputc(matriz[i][j][0], archSalida); // B
            fputc(matriz[i][j][1], archSalida); // G
            fputc(matriz[i][j][2], archSalida); // R
        }

        for (int j = 0; j < *padding; j++)
        {
            fputc(0, archSalida);
        }
    }

    return TODO_OK;
}

int leerBMP(const char *nombreArch, Imagen *regArch, int *inicioDatos, int *ancho, int *alto,
            int *tamPunto, FILE *archBMP, unsigned char ****matriz)
{
    int codigo;

    (void)nombreArch;

    *matriz = NULL;

    // Obtengo el tamnio del archivo
    obtenerTamArchivo(archBMP, regArch);

    // Obtengo el primer campo reservado
    obtenerPrimerReservado(archBMP, regArch);

    // Obtengo el segundo campo reservado
    obtenerSegundoReservado(archBMP, regArch);

    // Obtengo inicio de datos de la imagen
    *(inicioDatos) = obtenerInicioDatos(archBMP, regArch);

    // Obtengo tamanio de la cabecera
    obtenerTamCabecera(archBMP, regArch);

    // Obtengo ancho
    *(ancho) = obtenerAncho(archBMP, regArch);

    // Obtengo alto
    *(alto) = obtenerAlto(archBMP, regArch);

    // Obtengo nro de planos
    obtenerNroPlanos(archBMP, regArch);

    // Obtengo tamanio de cada punto
    *(tamPunto) = obtenerTamPixeles(archBMP, regArch);

    // Obtengo compresion
    obtenerCompresion(archBMP, regArch);

    // Obtengo tamanio de la imagen
    obtenerTamImagen(archBMP, regArch);

    // Obtengo resolucion horizontal
    obtenerResolHorizontal(archBMP, regArch);

    // Obtengo resolucion vertical
    obtenerResolVertical(archBMP, regArch);

    //Obtengo tamanio de la tabla de color
    obtenerTamTablaColor(archBMP, regArch);

    // Obtengo contaodr de colores importantes
    obtenerContColorImportantes(archBMP, regArch);

    regArch->letra1 = 'B';
    regArch->letra2 = 'M';

    // Bytes adicionales entre el final de la cabecera y el comienzo d elos pixeles
    codigo = validarCabecera(archBMP, inicioDatos);
    if (codigo != TODO_OK)
    {
        return codigo;
    }

    // Validacion BMP 24 BITS
    codigo = validarProfundidad(archBMP, tamPunto);
    if (codigo != TODO_OK)
    {
        return codigo;
    }

    *matriz = reservarMatriz(regArch->ancho, regArch->alto);

    if (*matriz == NULL)
    {
        fclose(archBMP);
        return SIN_MEMORIA;
    }

    // Leer los pixeles y cargar
    cargarImagenMatriz(archBMP, *matriz, inicioDatos, ancho, alto);

    return TODO_OK;
}

void mostrarError(int codigo)
{
    if (codigo == TODO_OK)
    {
        return;
    }

    switch (codigo)
    {
        case ARGUMENTO_INVALIDO:
            printf("Error: cantidad de parametros incorrecta.\n");
            printf("Uso:\n");
            printf("  bmpmanipuleitor.exe --filtro imagen.bmp\n");
            printf("  bmpmanipuleitor.exe --concatenar-horizontal imagen1.bmp imagen2.bmp\n");
            printf("  bmpmanipuleitor.exe --concatenar-vertical imagen1.bmp imagen2.bmp\n");
            break;

        case FILTRO_NO_RECONOCIDO:
            printf("Error: filtro no reconocido.\n");
            break;

        case PORCENTAJE_INVALIDO:
            printf("Error: el porcentaje debe estar entre 0 y 100.\n");
            break;

        case ERROR_EXTENSION:
            printf("Error: el archivo debe tener extension .bmp\n");
            break;

        case ERROR_ABRIR_ARCHIVO:
            printf("Error: no se pudo abrir o crear el archivo.\n");
            break;

        case ARCHIVO_NO_BMP:
            printf("Error: el archivo no es un BMP valido (firma BM).\n");
            break;

        case CABECERA_INVALIDA:
            printf("Error: cabecera BMP invalida.\n");
            break;

        case PROFUNDIDAD_INVALIDA:
            printf("Error: el BMP debe ser de 24 bits.\n");
            break;

        case ERROR_LECTURA_ARCHIVO:
            printf("Error: no se pudieron leer los datos del archivo.\n");
            break;

        case SIN_MEMORIA:
            printf("Error: no hay memoria suficiente.\n");
            break;

        case ERROR_CARGA_IMAGEN:
            printf("Error: no se pudo cargar la imagen BMP.\n");
            break;

        default:
            printf("Error desconocido (codigo %d).\n", codigo);
            break;
    }
}

int salirConError(int codigo)
{
    mostrarError(codigo);
    return codigo;
}
