<<<<<<< HEAD:bmpmanipuleitor/funciones_viegas.h
#ifndef FUNCIONES_VIEGAS_H_INCLUDED
#define FUNCIONES_VIEGAS_H_INCLUDED


void negativo(unsigned char ***matriz, int ancho, int alto);
void escalaDeGrises(unsigned char ***matriz, int ancho, int alto);
void espejarHorizontal(unsigned char ***matriz, int ancho, int alto);
void espejarVertical(unsigned char ***matriz, int ancho, int alto);
unsigned char ***reservarMatriz(int ancho, int alto);
void liberarMatriz(unsigned char ***matriz, int ancho, int alto);
void crearNombreSalida(char *salida, char *filtro, char *entrada);



#endif // FUNCIONES_VIEGAS_H_INCLUDED
=======
#ifndef FUNCIONES_VIEGAS_H_INCLUDED
#define FUNCIONES_VIEGAS_H_INCLUDED

void negativo(unsigned char ***matriz, int ancho, int alto);
void escalaDeGrises(unsigned char ***matriz, int ancho, int alto);
void espejarHorizontal(unsigned char ***matriz, int ancho, int alto);
void espejarVertical(unsigned char ***matriz, int ancho, int alto);
void liberarMatriz(unsigned char ***matriz, int ancho, int alto);
void crearNombreSalida(char *salida, char *filtro, char *entrada);
unsigned char ***reservarMatriz(int ancho, int alto);

#endif // FUNCIONES_VIEGAS_H_INCLUDED
>>>>>>> 476c77a4f7ef7dfa4066cd29d5cbe6b9e024b738:funciones_viegas.h
