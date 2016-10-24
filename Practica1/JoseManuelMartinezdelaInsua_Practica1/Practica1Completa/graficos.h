/*
ASIGNATURA : " PERIFERICOS Y DISPOSITIVOS DE INTERFAZ HUMANA ".
AUTOR : Jose Manuel Martínez de la Insua.
*/

#include "mi_io.h"

/*
############################## GRAFICOS ################################
A PARTIR DE ESTE PUNTO SE DEFINEN LAS VARIABLES Y LOS MODULOS NECESARIOS
PARA EL DISEÑO Y CREACION DE INTERFAZ GRAFICA POR DEFECTO .
*/


/*
Constantes estáticas que definen la alineación
del texto en cualquier menú de opciones. La variable
'CENTER' se puede usar para ambos ejes de coordenadas (X e Y).
*/
const static int LEFT = -1;
const static int CENTER = 0;
const static int RIGHT = 1;
const static int TOP = 2;
const static int BOT = 3;


/*
Representa un rectangulo de coordenada izquierda superior (x0,y0)
y coordenada derecha inferior (x1,y1).
*/

typedef struct _Frame {
    int x0;
    int y0;
    int x1;
    int y1;
} FRAME;

/*
Inicializa y devuelve una estructura 'FRAME'.
*/
FRAME init(int xa,int ya,int xb,int yb);

/*
Crea el marco de un recuadro en la pantalla (no relleno) del color
pasado por parámetro.
f : (FRAME) Rectángulo contenedor.
color: define el color de fondo y el color de caracter, siendo
los 4 primeros bits los correspondientes al fondo de pantalla y los 4 últimos
al color de los caracteres.
*/
void frame_box(FRAME f,const BYTE color);


/*
Crea un recuadro en la pantalla (relleno) del color
pasado por parámetro.
f : FRAME Rectángulo contenedor.
color : define el color de fondo y el color de caracter, siendo
los 4 primeros bits los correspondientes al fondo de pantalla y los 4 últimos
al color de los caracteres.
*/
void empty_box(FRAME f,const BYTE color);


/*
Crea un recuadro con una cadena de caracteres en su interior,
alineada según se indique por parámetro.
f : FRAME Rectángulo contenedor del cuadro de texto.
color:  usa los primeros 4 bits para el color de fondo y los siguientes 4 bits
para el color de la cadena de caracteres.
alignx y aligny definen la alineación horizontal y vertical respectivamente.
*/
void text_box(FRAME f,const char *str,const BYTE color,const int alignx,const int aligny);

/*
Crea un menú de opciones por defecto cuyo perímetro queda delimitado por 'f' (FRAME).
fcolor : Representa el color del 'frame_box()'.
ocolor : Representa el color del contenedor de la opción.
opts : Array de cadenas de caracteres con las opciones del menu.
selected : Entero con la opción seleccionada.
tam : Longitud del vector opts.

Por defecto, cada opción ocupará el ancho completo del 'frame_box()' y el alto de una línea.
*/
void display_default_menu(FRAME f,const BYTE fcolor,const BYTE ocolor,const char **opts,const int tam,int selected);



/*
Crea un menú informativo por defecto cuyo perímetro queda delimitado por 'f' (FRAME).
title : Título del menú.
fcolor : Representa el color del 'frame_box()'.
ocolor : Representa el color del contenedor de la opción.
opts : Array de cadenas de caracteres con la información del menú.
tam : Longitud del vector opts.

Por defecto, cada opción ocupará el ancho completo del 'frame_box()' y el alto de una línea.
*/

void display_default_info_menu(const char* title ,FRAME f,const BYTE fcolor,const BYTE ocolor,const char **opts,const int tam);


