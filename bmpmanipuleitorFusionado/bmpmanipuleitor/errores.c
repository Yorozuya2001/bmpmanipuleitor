#include "errores.h"
#include <stdio.h>

void mostrarError(int codigo)
{
    if (codigo == TODO_OK)
    {
        return;
    }


    switch (codigo)
    {
        case ARGUMENTO_INVALIDO:
            printf("Error: cantidad de parametros incorrecta.\n");
            printf("Uso:\n");
            printf("  bmpmanipuleitor.exe --filtro imagen.bmp\n");
            printf("  bmpmanipuleitor.exe --concatenar-horizontal imagen1.bmp imagen2.bmp\n");
            printf("  bmpmanipuleitor.exe --concatenar-vertical imagen1.bmp imagen2.bmp\n");
            break;

        case FILTRO_NO_RECONOCIDO:
            printf("Error: filtro no reconocido.\n");
            break;

        case PORCENTAJE_INVALIDO:
            printf("Error: el porcentaje debe estar entre 0 y 100.\n");
            break;

        case ERROR_EXTENSION:
            printf("Error: el archivo debe tener extension .bmp\n");
            break;

        case ERROR_ABRIR_ARCHIVO:
            printf("Error: no se pudo abrir o crear el archivo.\n");
            break;

        case ARCHIVO_NO_BMP:
            printf("Error: el archivo no es un BMP valido (firma BM).\n");
            break;

        case CABECERA_INVALIDA:
            printf("Error: cabecera BMP invalida.\n");
            break;

        case PROFUNDIDAD_INVALIDA:
            printf("Error: el BMP debe ser de 24 bits.\n");
            break;

        case ERROR_LECTURA_ARCHIVO:
            printf("Error: no se pudieron leer los datos del archivo.\n");
            break;

        case SIN_MEMORIA:
            printf("Error: no hay memoria suficiente.\n");
            break;

        case ERROR_CARGA_IMAGEN:
            printf("Error: no se pudo cargar la imagen BMP.\n");
            break;

        default:
            printf("Error desconocido (codigo %d).\n", codigo);
            break;
            
    }
}

int salirConError(int codigo)
{
    mostrarError(codigo);
    return codigo;
}
