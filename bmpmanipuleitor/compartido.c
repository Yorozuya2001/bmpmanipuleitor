#include "compartido.h"
#include "estructuras.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones_viegas.h"
#include "funciones_rosales.h"
#include "funciones_valiente.h"



int validarParametros(int* argc,const char* filtro,const char* pathImagen)
{
    // argv [0] = nombre del archivo .exe -->  bmpmanipuleitor.exe
   // argv [1] = filtro                  -->  --negativo
   // argv [2] = nombre de la imagne     -->  359.bmp
    const char extension[]=".bmp";


    if (*argc <3){
        printf("Cantidad de parametros ingresados invalida\n");
        printf("Uso:\n");
        printf("bmpmanipuleitor.exe --filtro imagen.bmp\n");
        return -1;
    }

    const char listado_Funciones[5][100]= {"--negativo,--escala-de-grises,--espejar-horizontal",
                                 "--espejar-vertical,--aumentar-contraste,--reducir-contraste",
                                 "--tonalidad-azul,--tonalidad-verde,--tonalidad-roja",
                                 "--recortar,--achicar,--rotar-derecha",
                                 "--rotar-izquierda,--concatenar-horizontal,--concatenar-vertical"
                                 };

    ///Validar ingreso de filtro
    for(int i=0;i<=4;i++){
            if(strstr(filtro,listado_Funciones[i])==NULL){
                printf("Filtro no reconocido: %s\n",filtro);
                return FALLA;
            }
          }

      ///Validar extension de la imagen
      if(strstr(extension,pathImagen)==NULL){
          printf("Archivo ingresado invalido. Debe ser una imagen BMP");
          return FALLA;

      }

     return TODO_OK;

}

int validar_cabecera(FILE* archBMP,int* inicioDatos)
{
   int tamanioExtra = *inicioDatos - 54;
   unsigned char *datosExtra;

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
            return FALLA;
        }
    }

    return TODO_OK;
}

int validar_profundidad(FILE* archBMP,int* tamPunto)
{
   if (*tamPunto != 24)
    {
        printf("El BMP debe ser de 24 bits.\n");
        fclose(archBMP);
        return FALLA;
    }

    return TODO_OK;


}


FILE* abrirArchivo(char* nombreArchivo)
{
    FILE* archBMP = fopen(nombreArchivo, "rb");
    struct imagen regArch;

    if (archBMP == NULL){
        printf("No se pudo abrir el archivo %s\n",nombreArchivo);
    }


     /* LEER CABECERA BMP */

    // Obtengo el tipo de archivo
    regArch.letra1 = fgetc(archBMP); ///Fgetc lee caracteres individualmente y devuelve un int como valor ASCII del caracter
    regArch.letra2 = fgetc(archBMP);

    if (regArch.letra1 != 'B' || regArch.letra2 != 'M')
    {
        printf("El archivo no es un BMP valido.\n");
        fclose(archBMP);
    }

    return archBMP;

}

int obtener_TamArchivo(FILE* archBMP,struct imagen* reg)
{

  int tamArchivo;

  fseek(archBMP, 2, SEEK_SET);
  fread(&reg->tamanio_archivo, 4, 1, archBMP);
  tamArchivo=reg->tamanio_archivo;

  return tamArchivo;


}


int obtener_InicioDatos(FILE* archBMP,struct imagen* reg)
{

  int inicioDatos;

  fseek(archBMP, 10, SEEK_SET);
  fread(&reg->inicio_datos_imagen, 4, 1, archBMP);
  inicioDatos=reg->inicio_datos_imagen;

  return inicioDatos;


}

int obtener_TamCabecera(FILE* archBMP,struct imagen* reg)
{

  int tamCabecera;

  fseek(archBMP, 14, SEEK_SET);
  fread(&reg->tamanio_cabecera, 4, 1, archBMP);
  tamCabecera=reg->tamanio_cabecera;

  return tamCabecera;


}

int obtener_Ancho(FILE* archBMP,struct imagen* reg)
{
   int anchoImagen;


  fseek(archBMP, 18, SEEK_SET);
  fread(&reg->ancho, 4, 1, archBMP);
  anchoImagen=reg->ancho;

  return anchoImagen;


}

int obtener_Alto(FILE* archBMP,struct imagen* reg)
{
    int altoImagen;

    fseek(archBMP, 22, SEEK_SET);
    fread(&reg->alto, 4, 1, archBMP);
    altoImagen=reg->alto;

    return altoImagen;
}

int obtener_TamPixeles(FILE* archBMP,struct imagen* reg)
{
   int tamPixeles;

  fseek(archBMP, 28, SEEK_SET);
  fread(&reg->tamanio_punto, 2, 1, archBMP);
  tamPixeles=reg->tamanio_punto;

  return tamPixeles;

}

int obtener_TamImagen(FILE* archBMP, struct imagen* reg)
{
  int tamImagen;

  fseek(archBMP, 34, SEEK_SET);
  fread(&reg->tamanio_imagen, 4, 1, archBMP);
  tamImagen=reg->tamanio_imagen;

  return tamImagen;

}

/*Funciones de Procesamiento*/

int cargarImagen_Matriz(FILE* archBMP,unsigned char*** matriz,int* inicioDatos,int* ancho,int* alto)
{
    fseek(archBMP,*inicioDatos, SEEK_SET);

    int padding = (4 - (*ancho * 3) % 4) % 4;
    int i,j;

      /* LEER LOS PIXELES */
    // Se guardan las las filas desde abajo hacia arriba.
    // Fila 0 = parte superior

    for (i = *alto - 1; i >= 0; i--)
    {
        for (j = 0; j < *ancho; j++){
            matriz[i][j][0] = fgetc(archBMP); /* B */
            matriz[i][j][1] = fgetc(archBMP); /* G */
            matriz[i][j][2] = fgetc(archBMP); /* R */
          }

        /* Ignorar padding */
        for (j = 0; j < padding; j++){
            fgetc(archBMP);
        }
    }

    return TODO_OK;

}


///Menu de opciones que ejecuta las funcionalidades en base al filtro ingresado
int aplicarFiltro(unsigned char*** matriz,const char* filtro,int* ancho, int* alto,int* padding)
{

    int porcentaje;
    int opcion;

    ///Funcionalidades que reciben porcentaje como argumento
    char filtrosxPorcent[7][30]={
                               "--aumentar-contraste",
                               "--reducir-contraste",
                               "--tonalidad-azul",
                               "--tonalidad-verde",
                               "--tonalidad-roja",
                               "--recortar",
                               "--achicar"
                               };

    for(int i=0;i<=6;i++){
      if(strstr(filtro,filtrosxPorcent[i])!=NULL){
         sscanf(filtro,"%s=%d",filtro,&porcentaje);
       }

    }

    if (strcmp(filtro, "--negativo") == 0){
        negativo(matriz,*ancho,*alto);
    }
     else if (strcmp(filtro, "--escala-de-grises") == 0){
        escalaDeGrises(matriz,*ancho,*alto);
    }
     else if (strcmp(filtro, "--espejar-horizontal") == 0){
        espejarHorizontal(matriz,*ancho,*alto);
    }
    else if (strcmp(filtro, "--espejar-vertical") == 0){
        espejarVertical(matriz,*ancho,*alto);
    }

    ///Probamos funcionalidades nuevas propias(Rosales)
    else if (strcmp(filtro, "--tonalidad-azul") == 0){
        tonalidadAzul(matriz,*ancho,*alto,&porcentaje);
    }

    else if (strcmp(filtro, "--tonalidad-verde") == 0){
        tonalidadVerde(matriz,*ancho,*alto,&porcentaje);
    }

    else if (strcmp(filtro, "--recortar") == 0){
        recortarImagen(ancho,alto,padding,&porcentaje);
    }

    else if (strcmp(filtro, "--achicar") == 0){
        unsigned char*** mat=achicarImagen(matriz,ancho,alto,&porcentaje);
    }

    ///Acá agregan la llamada al resto de las funciones

    return TODO_OK;

}

int generar_ArchSalida(char* nombreSalida,FILE* archBMP,FILE* archSalida,unsigned char*** matriz,int* padding,struct imagen* reg)
{

    int tamImagen=obtener_TamImagen(archBMP,reg);
    int tamArchivo=obtener_TamArchivo(archBMP,reg);
    int tamCabecera=obtener_TamCabecera(archBMP,reg);

    archSalida = fopen(nombreSalida, "wb");

    if (archSalida == NULL)
    {
        printf("No se pudo crear %s\n", nombreSalida);
        liberarMatriz(matriz,reg->ancho,reg->alto);
        return 1;
    }

    *padding = (4 - (reg->ancho * 3) % 4) % 4;

    tamImagen = (reg->ancho * 3 + *padding) * reg->alto;
    reg->tamanio_archivo = reg->inicio_datos_imagen + reg->tamanio_imagen;

     /*  ESCRIBIR CABECERA BMP */
    fputc(reg->letra1, archSalida);
    fputc(reg->letra2, archSalida);

    fwrite(tamArchivo, 4, 1, archSalida);
    //fwrite(reg.reservado1, 2, 1, archSalida);
    //fwrite(reg.reservado2, 2, 1, archSalida);
    fwrite(reg->inicio_datos_imagen, 4, 1, archSalida);
    fwrite(&tamCabecera, 4, 1, archSalida);
    fwrite(reg->ancho, 4, 1, archSalida);
    fwrite(reg->alto, 4, 1, archSalida);
    fwrite(reg->nro_planos, 2, 1, archSalida);
    fwrite(reg->tamanio_punto, 2, 1, archSalida);
    fwrite(reg->compresion, 4, 1, archSalida);
    fwrite(reg->tamanio_imagen, 4, 1, archSalida);
    fwrite(reg->resolucion_horizontal, 4, 1, archSalida);
    fwrite(reg->resolucion_vertical, 4, 1, archSalida);
    fwrite(reg->tamanio_tabla_color, 4, 1, archSalida);
    fwrite(reg->contador_colores_importantes, 4, 1, archSalida);


    /*
    if (tamanioExtra > 0){
        fwrite(datosExtra, 1, tamanioExtra, archSalida);
    }*/



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

