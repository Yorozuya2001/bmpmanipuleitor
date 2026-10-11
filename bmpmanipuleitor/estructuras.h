#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED
// Estructura sugerida, su uso es opcional.
//typedef struct
//{
//    unsigned char pixel[3];
//}t_pixel;

//typedef struct
//{
 //   unsigned int tamArchivo;
 //   unsigned int tamEncabezado;
 //   unsigned int ancho;
 //   unsigned int alto;
 //   unsigned short profundidad;
//}t_metadata;

struct imagen
{
    char letra1;
    char letra2;
    int tamanio_archivo;
    short int reservado1;
    short int reservado2;
    int inicio_datos_imagen;
    int tamanio_cabecera;
    int ancho;
    int alto;
    short int nro_planos;
    short int tamanio_punto;
    int compresion;
    int tamanio_imagen;
    int resolucion_horizontal;
    int resolucion_vertical;
    int tamanio_tabla_color;
    int contador_colores_importantes;
};



#endif // ESTRUCTURAS_H_INCLUDED
