#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
#include "estructuras.h"

#define TODO_OK                 0
#define SIN_MEMORIA            -1
#define ARGUMENTO_INVALIDO     -2
#define ERROR_EXTENSION        -3
#define ARCHIVO_NO_BMP         -4
#define FILTRO_NO_RECONOCIDO   -5
#define PORCENTAJE_INVALIDO    -6
#define PROFUNDIDAD_INVALIDA   -7
#define ERROR_ABRIR_ARCHIVO    -8
#define CABECERA_INVALIDA      -9
#define ERROR_LECTURA_ARCHIVO -10
#define ERROR_CARGA_IMAGEN    -11

#define EXTENSION_BMP ".bmp"

/* Filtros sin parametro extra (o nombre exacto en argv) */
#define FILTRO_NEGATIVO "--negativo"
#define FILTRO_ESCALA_DE_GRISES "--escala-de-grises"
#define FILTRO_ESPEJAR_HORIZONTAL "--espejar-horizontal"
#define FILTRO_ESPEJAR_VERTICAL "--espejar-vertical"
#define FILTRO_ROTAR_DERECHA "--rotar-derecha"
#define FILTRO_ROTAR_IZQUIERDA "--rotar-izquierda"
#define FILTRO_CONCATENAR_HORIZONTAL "--concatenar-horizontal"
#define FILTRO_CONCATENAR_VERTICAL "--concatenar-vertical"
#define FILTRO_COMODIN "--comodin"

/* Filtros que pueden venir como --nombre=porcentaje */
#define FILTRO_AUMENTAR_CONTRASTE "--aumentar-contraste"
#define FILTRO_REDUCIR_CONTRASTE "--reducir-contraste"
#define FILTRO_TONALIDAD_AZUL "--tonalidad-azul"
#define FILTRO_TONALIDAD_VERDE "--tonalidad-verde"
#define FILTRO_TONALIDAD_ROJA "--tonalidad-roja"
#define FILTRO_RECORTAR "--recortar"
#define FILTRO_ACHICAR "--achicar"

void mostrarError(int codigo);
int salirConError(int codigo);

///Definimos estos valores
//#define 1 --negativo

// Funciones para reservar memoria y liberar matrices
void liberarMatriz(unsigned char ***matriz, int* ancho, int* alto);
unsigned char ***reservarMatriz(int ancho, int alto);


///Funcion de validacion de Parametros
int validarParametros(int* argc,const char* filtro,const char* pathImagen, int *esConcatenar);


///Funciones extras que se invocan desde la solucion
int abrirArchivo(char *nombreArchivo, const char *modoApertura, FILE **archivo);

///Funciones especificas para obtencion de datos del archivo
int obtenerTamArchivo(FILE* archBMP, Imagen* reg);
int obtenerInicioDatos(FILE* archBMP, Imagen* reg);
int obtenerTamCabecera(FILE* archBMP, Imagen* reg);
int obtenerAncho(FILE* archBMP, Imagen* reg);
int obtenerAlto(FILE* archBMP, Imagen* reg);
int obtenerTamPixeles(FILE* archBMP, Imagen* reg);
int obtenerTamImagen(FILE* archBMP, Imagen* reg);
int obtenerNroPlanos(FILE* archBMP, Imagen* reg);
int obtenerCompresion(FILE* archBMP, Imagen* reg);
int obtenerResolHorizontal(FILE* archBMP, Imagen* reg);
int obtenerResolVertical(FILE* archBMP, Imagen* reg);
int obtenerTamTablaColor(FILE* archBMP, Imagen* reg);
int obtenerContColorImportantes(FILE* archBMP, Imagen* reg);
int obtenerPrimerReservado(FILE* archBMP, Imagen* reg);
int obtenerSegundoReservado(FILE* archBMP, Imagen* reg);







///Funciones de validacion sobre estructura del archivo
int validarCabecera(FILE* archBMP,int* inicioDatos);
int validarProfundidad(FILE* archBMP,int* tamPunto);

///Funciones de procesamiento de imagenes
int cargarImagenMatriz(FILE* archBMP,unsigned char*** matriz,int* inicioDatos,int* ancho,int* alto);///Carga pixeles de la imagen en matriz dinamica
unsigned char*** aplicarFiltro(unsigned char*** matriz,const char* filtro,int* ancho, int* alto,int* padding,unsigned char*** matriz2,int* anchoImg2, int* altoImg2);
int generarArchSalida(char* nombreSalida,FILE* archBMP,FILE* archSalida,unsigned char*** matriz,int* padding,Imagen* reg);

//Funcion para leer archivos BMP (devuelve codigo; la matriz se escribe en *matriz)
int leerBMP(const char *nombreArch, Imagen *regArch, int *inicioDatos, int *ancho, int *alto,
            int *tamPunto, FILE *archBMP, unsigned char ****matriz);





#endif // COMPARTIDO_H_INCLUDED
