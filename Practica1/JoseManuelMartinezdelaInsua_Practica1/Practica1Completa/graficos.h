/*
ASIGNATURA : " PERIFERICOS Y DISPOSITIVOS DE INTERFAZ HUMANA ".
AUTOR : Jose Manuel Mart�nez de la Insua.
*/

#include "mi_io.h"

/*
############################## GRAFICOS ################################
A PARTIR DE ESTE PUNTO SE DEFINEN LAS VARIABLES Y LOS MODULOS NECESARIOS
PARA EL DISE�O Y CREACION DE INTERFAZ GRAFICA POR DEFECTO .
*/


/*
Constantes est�ticas que definen la alineaci�n
del texto en cualquier men� de opciones. La variable
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
pasado por par�metro.
f : (FRAME) Rect�ngulo contenedor.
color: define el color de fondo y el color de caracter, siendo
los 4 primeros bits los correspondientes al fondo de pantalla y los 4 �ltimos
al color de los caracteres.
*/
void frame_box(FRAME f,const BYTE color);


/*
Crea un recuadro en la pantalla (relleno) del color
pasado por par�metro.
f : FRAME Rect�ngulo contenedor.
color : define el color de fondo y el color de caracter, siendo
los 4 primeros bits los correspondientes al fondo de pantalla y los 4 �ltimos
al color de los caracteres.
*/
void empty_box(FRAME f,const BYTE color);


/*
Crea un recuadro con una cadena de caracteres en su interior,
alineada seg�n se indique por par�metro.
f : FRAME Rect�ngulo contenedor del cuadro de texto.
color:  usa los primeros 4 bits para el color de fondo y los siguientes 4 bits
para el color de la cadena de caracteres.
alignx y aligny definen la alineaci�n horizontal y vertical respectivamente.
*/
void text_box(FRAME f,const char *str,const BYTE color,const int alignx,const int aligny);

/*
Crea un men� de opciones por defecto cuyo per�metro queda delimitado por 'f' (FRAME).
fcolor : Representa el color del 'frame_box()'.
ocolor : Representa el color del contenedor de la opci�n.
opts : Array de cadenas de caracteres con las opciones del menu.
selected : Entero con la opci�n seleccionada.
tam : Longitud del vector opts.

Por defecto, cada opci�n ocupar� el ancho completo del 'frame_box()' y el alto de una l�nea.
*/
void display_default_menu(FRAME f,const BYTE fcolor,const BYTE ocolor,const char **opts,const int tam,int selected);



/*
Crea un men� informativo por defecto cuyo per�metro queda delimitado por 'f' (FRAME).
title : T�tulo del men�.
fcolor : Representa el color del 'frame_box()'.
ocolor : Representa el color del contenedor de la opci�n.
opts : Array de cadenas de caracteres con la informaci�n del men�.
tam : Longitud del vector opts.

Por defecto, cada opci�n ocupar� el ancho completo del 'frame_box()' y el alto de una l�nea.
*/

void display_default_info_menu(const char* title ,FRAME f,const BYTE fcolor,const BYTE ocolor,const char **opts,const int tam);


