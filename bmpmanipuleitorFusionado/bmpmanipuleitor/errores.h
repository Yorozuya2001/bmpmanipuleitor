#ifndef ERRORES_H_INCLUDED
#define ERRORES_H_INCLUDED


#define TODO_OK                 0
#define SIN_MEMORIA            -1
#define ARGUMENTO_INVALIDO     -2
#define ERROR_EXTENSION        -3   /* path sin .bmp (antes ERROR_ARCHIVO en validarParametros) */
#define ARCHIVO_NO_BMP         -4   /* abierto pero no empieza con 'B' 'M' */
#define FILTRO_NO_RECONOCIDO   -5
#define PORCENTAJE_INVALIDO    -6   /* opcional: 0..100 */
#define PROFUNDIDAD_INVALIDA   -7
#define ERROR_ABRIR_ARCHIVO    -8   /* fopen falló */
#define CABECERA_INVALIDA      -9   /* cabecera BMP inconsistente */
#define ERROR_LECTURA_ARCHIVO -10   /* fread / lectura incompleta */
#define ERROR_CARGA_IMAGEN    -11


void mostrarError(int codigo);

int salirConError(int codigo);

#endif /* ERRORES_H_INCLUDED */
