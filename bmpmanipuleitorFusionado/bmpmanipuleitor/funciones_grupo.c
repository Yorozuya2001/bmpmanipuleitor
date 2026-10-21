
/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Bustillos
    Nombre: Juan Ignacio
    DNI: 46876304
    Entrega: Sí
    -----------------
    Apellido:Rosales
    Nombre: Gustavo Mauricio
    DNI: 43665940
    Entrega:Sí
    -----------------
    Apellido: Valiente
    Nombre: Axel Ariel
    DNI: 43202499
    Entrega: Sí
    -----------------
	Apellido: Viegas
    Nombre: Chloe Jacqueline Micol
    DNI: 35361882
    Entrega: Sí
    -----------------
*/
#include "funciones_grupo.h"




int main(int argc, char* argv[])
{
    /*-------------------------------------------------------------- */
    /* Variables*/

    FILE *archBMP;
    FILE *archSalida;
     Imagen regArch;
    //Imagen regSalida;
    unsigned char ***matriz;
    int inicioDatos,ancho,alto,tamPunto;
    //unsigned char ***matRed;
    char nombreSalida[500];
    char* p_nombreSalida=nombreSalida;
    int padding;
    //unsigned char *datosExtra;
    //int tamanioExtra;
    
    
    //-----------------------------------------------------------------------------------
    // Validacion de parametros

    if (validarParametros(&argc, argv[1], argv[2]) != TODO_OK){
        return 1;
    }
    ///Apertura de Archivo
    archBMP=abrirArchivo(argv[2],"rb");
    if (archBMP == NULL)
        return 1;
    
    // Obtengo el tamnio del archivo
    obtenerTamArchivo(archBMP, &regArch);

    // Obtengo el primer campo reservado
    obtenerPrimerReservado(archBMP, &regArch);
    
    // Obtengo el segundo campo reservado
    obtenerSegundoReservado(archBMP, &regArch);

    // Obtengo inicio de datos de la imagen
    inicioDatos = obtenerInicioDatos(archBMP, &regArch);
    
    // Obtengo tamanio de la cabecera
    obtenerTamCabecera(archBMP, &regArch);

    // Obtengo ancho
    ancho = obtenerAncho(archBMP, &regArch);
    
    // Obtengo alto
    alto = obtenerAlto(archBMP, &regArch);
    
    // Obtengo nro de planos
    obtenerNroPlanos(archBMP, &regArch);
    
    // Obtengo tamanio de cada punto
    tamPunto = obtenerTamPixeles(archBMP, &regArch);
    
    // Obtengo compresion
    obtenerCompresion(archBMP, &regArch);
    
    // Obtengo tamanio de la imagen
    obtenerTamImagen(archBMP, &regArch);
    
    // Obtengo resolucion horizontal
    obtenerResolHorizontal(archBMP, &regArch);
    
    // Obtengo resolucion vertical
    obtenerResolVertical(archBMP, &regArch);

    //Obtengo tamanio de la tabla de color
    obtenerTamTablaColor(archBMP, &regArch);

    // Obtengo contaodr de colores importantes
    obtenerContColorImportantes(archBMP, &regArch);
    regArch.letra1 = 'B';
    regArch.letra2 = 'M';
    
    
    //-----------------------------------------------------------------------------------
    // Bytes adicionales entre el final de la cabecera y el comienzo d elos pixeles
    validarCabecera(archBMP,&inicioDatos);

    //-----------------------------------------------------------------------------------
    // Validacion BMP 24 BITS
    validarProfundidad(archBMP,&tamPunto);
   
    //-----------------------------------------------------------------------------------
    // Reservo memoria para la matriz que va a almacenar la imagen 
    matriz = reservarMatriz(regArch.ancho, regArch.alto);
    
    if(!matriz){
        printf("No se pudo reservar memoria.\n");
        fclose(archBMP);
        return 1;
    }
  
    //-----------------------------------------------------------------------------------
    // Leer los pixeles y cargar
    cargarImagenMatriz(archBMP,matriz,&inicioDatos,&ancho,&alto);

    //-----------------------------------------------------------------------------------
    // Aplicar filtro
    matriz = aplicarFiltro(matriz,argv[1],&ancho,&alto,&padding);
    regArch.ancho = ancho;
    regArch.alto  = alto;


    //-----------------------------------------------------------------------------------
    // Crear nombre del archivo de salida
    p_nombreSalida=crearNombreSalida(nombreSalida, argv[1] + 2, argv[2]);
    archSalida = fopen(p_nombreSalida, "wb");
    if (archSalida == NULL)
        return 1;


    //-----------------------------------------------------------------------------------
    // Crear archivo de salida
    generarArchSalida(nombreSalida,archBMP,archSalida,matriz,&padding,&regArch);
    fclose(archBMP);
    //free(datosExtra);
    liberarMatriz(matriz, &regArch.ancho, &regArch.alto);
    fclose(archSalida);
    printf("Archivo generado correctamente: %s\n", nombreSalida);
    return 0;
}