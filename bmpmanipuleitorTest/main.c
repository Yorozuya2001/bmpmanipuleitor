
/*--------------------------------------------------------------------------------------------------------
Se solicita realizar un programa en lenguaje C llamado bmpmanipuleitor, que a partir de un archivo BMP de 24
bits de profundidad genere otro archivo BMP con las modificaciones solicitadas como argumentos a main.

Por ejemplo:
bmpmanipuleitor.exe ₋₋negativo imagenOriginal.bmp

Debe generar un archivo llamado GRUPO_negativo_imagenOriginal.bmp que contenga la misma imagen,
pero con los colores invertidos.
De modo que si el grupo INVISIBLE quisiera aplicar este mismo filtro a una imagen llamada unlam.bmp,
la imagen resultante debería llamarse INVISIBLE_negativo_unlam.bmp

Funcionalidades:
₋₋escala-de-grises      // deberá promediar los valores de cada color RGB y transformarlo a gris
₋₋espejar-horizontal    // deberá invertir horizontalmente la imagen
₋₋espejar-vertical      // deberá invertir la imagen verticalmente
₋₋aumentar-contraste=10 // aumenta el contraste en un 10%
₋₋reducir-contraste=20  //reduce el contraste en un 20%
₋₋tonalidad-azul=50     // aumenta en un 50% la intensidad del color azul
₋₋tonalidad-verde=5     // aumenta en un 5% la intensidad del color verde
₋₋tonalidad-roja=15     // aumenta en un 15% la intensidad del color rojo
₋₋rotar-derecha         // gira la imagen 90 grados a la derecha (sentido horario)
₋₋rotar-izquierda       // gira la imagen 90 grados a la izquierda (sentido antihorario)

₋₋recortar=30           // reduce el tamaño de la imagen al 30%, sin cambiar sus proporciones,
                           solamente descarta lo que exceda ese tamaño.
                           Por ejemplo: una imagen de 1000px x 500px, deberá mantener todos los píxeles que estén
                           entre 0 y 299 en el eje X y entre 0 y 149 el eje Y.

₋₋achicar=10             // reduce la imagen al 10%.
                            Por ejemplo: una imagen de 1000px x 500px, deberá reescribir todos los píxeles
                            para que se ubiquen entre 0 y 99 en el eje X y entre 0 y 49 el eje Y, formando
                            la misma imagen inicial (con peor calidad, claro).

₋₋concatenar-horizontal  // recibirá como argumento dos imágenes, y creará una nueva con el contenido de ambas,
                            una al lado de la otra. En caso de tener distinto alto, la más pequeña se rellenará
                            con algún color a gusto (que no sea ni blanco ni negro, dejando de lado el debate
                            de que sean o no un color) hasta completar el alto.

₋₋concatenar-vertical    // recibirá como argumento dos imágenes, y creará una nueva con el contenido de ambas,
                            una arriba de la otra, en caso de tener distinto ancho, la más pequeña se rellenará con
                            algún color a gusto (que no sea ni blanco ni negro, dejando de lado el debate de que sean
                            o no un color) hasta completar el ancho de la otra

₋₋comodin                 // una funcionalidad nueva, decidida por el grupo (no se puede repetir con alguna de las
                            solicitadas previamente en el TP)
---------------------------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include "funciones_grupo.h"


int main(int argc,char* argv[])
{
   return solucion(argc, argv);
}
