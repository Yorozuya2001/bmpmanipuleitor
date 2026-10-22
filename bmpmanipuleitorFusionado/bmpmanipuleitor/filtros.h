#ifndef FILTROS_H_INCLUDED
#define FILTROS_H_INCLUDED

#define EXTENSION_BMP ".bmp"

#define CANTIDAD_FILTROS 14
#define CANTIDAD_FILTROS_PORCENTAJE 6

/* Filtros sin par�metro extra (o nombre exacto en argv) */
#define FILTRO_NEGATIVO "--negativo"
#define FILTRO_ESCALA_DE_GRISES "--escala-de-grises"
#define FILTRO_ESPEJAR_HORIZONTAL "--espejar-horizontal"
#define FILTRO_ESPEJAR_VERTICAL "--espejar-vertical"
#define FILTRO_ROTAR_DERECHA "--rotar-derecha"
#define FILTRO_ROTAR_IZQUIERDA "--rotar-izquierda"
#define FILTRO_CONCATENAR_HORIZONTAL "--concatenar-horizontal"
#define FILTRO_CONCATENAR_VERTICAL "--concatenar-vertical"
#define FILTRO_COMODIN "--comodin"

/* Filtros que pueden venir como --nombre=porcentaje */
#define FILTRO_AUMENTAR_CONTRASTE "--aumentar-contraste"
#define FILTRO_REDUCIR_CONTRASTE "--reducir-contraste"
#define FILTRO_TONALIDAD_AZUL "--tonalidad-azul"
#define FILTRO_TONALIDAD_VERDE "--tonalidad-verde"
#define FILTRO_TONALIDAD_ROJA "--tonalidad-roja"
#define FILTRO_RECORTAR "--recortar"
#define FILTRO_ACHICAR "--achicar"

#endif /* FILTROS_H_INCLUDED */
