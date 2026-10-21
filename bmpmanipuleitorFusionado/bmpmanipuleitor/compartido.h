#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
#include "filtros.h"
#include "estructuras.h"

#define TODO_OK 0
#define FALLA -2

///Definimos estos valores
//#define 1 --negativo


///Funcion de validacion de Parametros
int validarParametros(int* argc,const char* filtro,const char* pathImagen);


///Funciones extras que se invocan desde la solucion
FILE* abrirArchivo(char* nombreArchivo,const char* modoApertura);

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
unsigned char*** aplicarFiltro(unsigned char*** matriz,const char* filtro,int* ancho, int* alto,int* padding);
int generarArchSalida(char* nombreSalida,FILE* archBMP,FILE* archSalida,unsigned char*** matriz,int* padding,Imagen* reg);







#endif // COMPARTIDO_H_INCLUDED
