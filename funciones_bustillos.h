#ifndef FUNCIONES_BUSTILLOS_H_INCLUDED
#define FUNCIONES_BUSTILLOS_H_INCLUDED
#define INCREMETO_ROJO 0.15
#define INCREMETO_BRILLO 1.5

void tonalidadRoja(unsigned char ***matriz, int ancho, int alto);
unsigned char ***concatenarHorizontal(unsigned char ***img1, int *ancho1, int *alto1, unsigned char ***img2, int ancho2, int alto2);
unsigned char ***concatenarVertical(unsigned char ***img1, int *ancho1, int *alto1, unsigned char ***img2, int ancho2, int alto2);
void comodin(unsigned char ***matriz, int ancho, int alto);

#endif // FUNCIONES_BUSTILLOS_H_INCLUDED
