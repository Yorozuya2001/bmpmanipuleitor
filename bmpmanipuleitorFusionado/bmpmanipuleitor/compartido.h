#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
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
int obtener_TamArchivo(FILE* archBMP,struct imagen* reg);
int obtener_InicioDatos(FILE* archBMP,struct imagen* reg);
int obtener_TamCabecera(FILE* archBMP,struct imagen* reg);
int obtener_Ancho(FILE* archBMP,struct imagen* reg);
int obtener_Alto(FILE* archBMP,struct imagen* reg);
int obtener_TamPixeles(FILE* archBMP,struct imagen* reg);
int obtener_TamImagen(FILE* archBMP, struct imagen* reg);
int obtener_NroPlanos(FILE* archBMP,struct imagen* reg);
int obtener_Compresion(FILE* archBMP,struct imagen* reg);
int obtener_resolHorizontal(FILE* archBMP,struct imagen* reg);
int obtener_resolVertical(FILE* archBMP, struct imagen* reg);
int obtener_Tam_TablaColor(FILE* archBMP,struct imagen* reg);
int obtener_cont_color_importantes(FILE* archBMP,struct imagen* reg);
int obtener_primerReservado(FILE* archBMP,struct imagen* reg);
int obtener_segundoReservado(FILE* archBMP,struct imagen* reg);








///Funciones de validacion sobre estructura del archivo
int validar_cabecera(FILE* archBMP,int* inicioDatos);
int validar_profundidad(FILE* archBMP,int* tamPunto);

///Funciones de procesamiento de imagenes
int cargarImagen_Matriz(FILE* archBMP,unsigned char*** matriz,int* inicioDatos,int* ancho,int* alto);///Carga pixeles de la imagen en matriz dinamica
unsigned char*** aplicarFiltro(unsigned char*** matriz,const char* filtro,int* ancho, int* alto,int* padding);
int generar_ArchSalida(char* nombreSalida,FILE* archBMP,FILE* archSalida,unsigned char*** matriz,int* padding,struct imagen* reg);







#endif // COMPARTIDO_H_INCLUDED
