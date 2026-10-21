#ifndef FUNCIONES_ROSALES_H_INCLUDED
#define FUNCIONES_ROSALES_H_INCLUDED

#define INTENSIDAD_AZUL 0.5
#define INTENSIDAD_VERDE 0.05
#define INTENSIDAD_ROJA 0.15
#define RECORTE 0.30
#define REDUCCION 0.10

void tonalidadAzul(unsigned char ***matriz, int ancho, int alto,int* porcent);
void tonalidadVerde(unsigned char ***matriz,int ancho,int alto,int* porcent);
unsigned char ***recortarImagen(unsigned char ***matriz,int* ancho,int* alto,int* padding,int* porcent);
unsigned char *** achicarImagen(unsigned char ***matriz,int* ancho, int* alto,int* porcent);












#endif // FUNCIONES_ROSALES_H_INCLUDED
