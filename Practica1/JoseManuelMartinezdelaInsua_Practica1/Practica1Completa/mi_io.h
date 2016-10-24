/*
ASIGNATURA : " PERIFERICOS Y DISPOSITIVOS DE INTERFAZ HUMANA ".
AUTOR : Jose Manuel Mart�nez de la Insua.
*/

#define BYTE unsigned char

/*
Lee un caracter por pantalla y devuelve su ID.
CODIGO ASCII para caracteres.
BSC para no caracteres.
*/
BYTE _read(void);


/*
Detecta la pulsaci�n de una tecla por teclado.
Retorna 0 si hay tecla en buffer, 1 en caso contrario.
*/
BYTE _kbhit(void);


/*
Obtiene las posiciones 'x' e 'y' del cursor respectivamente.
Devuelve una coordenada en el plano (X) (-Y) para el modo de v�deo 0x03h.
*/
BYTE _wherex(void);
BYTE _wherey(void);


/*
Obtiene los BYTEs de estado 1 y 2 del teclado, respectivamente.
*/
BYTE _getstatuskeyboardbyte1(void);
BYTE _getstatuskeyboardbyte2(void);


/*
Coloca el cursor en la coordenada (x,y) en el plano (X) (-Y)
para el modo 0x03h de v�deo siendo : {min(x,y) = (0,0), max(x,y) = (79,24)}.
*/
void _gotoxy(const BYTE x,const BYTE y);


/*
Fija el aspecto del cursor.
type: (const int)  puede ser:
0 - Cursor invisible.
1 - Cursor fino (por defecto).
2- Cursor grueso.
*/
void _setcursortype(const int type);


/* Fija el modo de v�deo.
mode: (const int)  puede oscilar entre:
0 y 19. A excepci�n de : 8,9,10,11 y 12.
*/
void _setvideomode(const int mode);


/*
Obtiene el modo de v�deo deseado.
Retona un valor (BYTE) que oscila entre 0x00h - 0x07h y 0x0Dh - 0x13h.
 */
BYTE _getvideomode(void);


/*
Obtiene el ancho (n�mero de columnas) de la pantalla. (S�lo para modo texto.)
*/
BYTE _getvideowidth(void);


/*
Borra la pantalla,y la pinta del color pasado por par�metro.
color: (BYTE) color para la pantalla.
*/
void _clrscr(const BYTE color);

/*
Crea el efecto de borrado de pantalla, pero realmente hace scroll
el tama�o de las filas totales.
color: (BYTE) color para la pantalla.
*/
void _clrscr2(const BYTE color);


/*
Borra una l�nea desde la posici�n actual el cursor,
del color pasado por par�metro.
*/
void _clreol(const BYTE color);


/*
Scroll  hacia arriba. La segunda funci�n se usa para
scroll de m�s de una una unidad de distancia.
*/
void _scrollup(const BYTE color);
void _scrollupdist(const int dist,const BYTE color);


/*Scroll  hacia abajo. La segunda funci�n se usa para
scroll de m�s de una una unidad de distancia.
*/
void _scrolldown(const BYTE color);
void _scrolldowndist(const int dist,const BYTE color);


/*
Escribe un caracter de un color, en la posici�n del cursor,
un n�mero determinado de veces.
char_ascii : (BYTE) C�digo ascii del caracter.
color : (BYTE) Color para el fondo y caracteres.
num_rep : (BYTE) N�mero de repeticiones del caracter.
*/
void _cputchar(const BYTE char_ascii,const BYTE color,const BYTE num_rep);


/*
Lee un caracter del teclado y lo muestra en pantalla
en la posici�n actual del cursor y del color pasado
por par�metro.
color : (BYTE) Color para el fondo y caracteres.
*/
void _getche(const BYTE color);


/*
Imprime una cadena de caracteres por pantalla.
str : (char*) Cadena para mostrar por pantalla.
color : (BYTE) Color para el caracter y el fondo de pantalla.
*/
void _cputs(const char *str,const BYTE color);


/*
Indica si un bit est� activo o no, para el BYTE dado por par�metro.
B : (BYTE)
pos : oscila entre 0-7, siendo 0 el bit m�s a la derecha.

Retorna:0 true ,1 false.
*/
int _isactivebit(BYTE B,const int pos);


/*
Espera hasta que se pulse ESC.
*/
void _waitforesc(void);


/*
Espera hasta que se pulse ENTER.
*/
void _waitforenter(void);


/*
Retorna el factor de repetici�n actual del teclado.
0 = 0.25 hasta 3 = 1.0
*/
BYTE _getkeyboardrate(void);


/*
Retorna el retardo actual del teclado.
0 = 31.0 cps hasta 31 = 2.0 cps
*/
BYTE _getkeyboarddelay(void);


/*
Restaura los valores por defecto para el retardo
y factor de repetici�n del teclado.
*/
void _setdefaultrateanddelay(void);


/*
Fija el factor de repetici�n del teclado.
0 = 0.25 hasta 3 = 1.0
*/
void _setkeyboardrate(const BYTE rate);


/*
Fija el valor para el retardo de teclado.
0 = 31.0 cps hasta 31 = 2.0 cps
*/
void _setkeyboarddelay(const BYTE delay);
