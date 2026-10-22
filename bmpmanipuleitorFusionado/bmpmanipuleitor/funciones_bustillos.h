#ifndef FUNCIONES_BUSTILLOS_H_INCLUDED
#define FUNCIONES_BUSTILLOS_H_INCLUDED
#define INCREMETO_ROJO 0.15
#define INCREMETO_BRILLO 1.5


// Defines para la funcionalidad de comodin, tono sepia

#define COMODIN_INCREMENTO_ROJO_ROJO 0.393
#define COMODIN_INCREMENTO_ROJO_VERDE 0.769
#define COMODIN_INCREMENTO_ROJO_AZUL 0.189

#define COMODIN_INCREMENTO_VERDE_ROJO 0.349
#define COMODIN_INCREMENTO_VERDE_VERDE 0.686
#define COMODIN_INCREMENTO_VERDE_AZUL 0.168

#define COMODIN_INCREMENTO_AZUL_ROJO 0.272
#define COMODIN_INCREMENTO_AZUL_VERDE 0.534
#define COMODIN_INCREMENTO_AZUL_AZUL 0.131

void tonalidadRoja(unsigned char ***matriz, int ancho, int alto);
unsigned char ***concatenarHorizontal(unsigned char ***img1, int *ancho1, int *alto1, unsigned char ***img2, int ancho2, int alto2);
unsigned char ***concatenarVertical(unsigned char ***img1, int *ancho1, int *alto1, unsigned char ***img2, int ancho2, int alto2);
void comodin(unsigned char ***matriz, int ancho, int alto);

#endif // FUNCIONES_BUSTILLOS_H_INCLUDED
