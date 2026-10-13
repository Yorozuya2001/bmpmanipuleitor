#ifndef FUNCIONES_ROSALES_H_INCLUDED
#define FUNCIONES_ROSALES_H_INCLUDED

#define INTENSIDAD_AZUL 0.5
#define INTENSIDAD_VERDE 0.05
#define RECORTE 0.30
#define REDUCCION 0.80

void tonalidadAzul(unsigned char ***matriz, int ancho, int alto);
void tonalidadVerde(unsigned char ***matriz,int ancho,int alto);
void recortarImagen(int* ancho,int* alto,int* padding);
unsigned char *** achicarImagen(unsigned char ***matriz,int* ancho, int* alto);






#endif // FUNCIONES_ROSALES_H_INCLUDED
