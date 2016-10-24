#define BYTE unsigned char

/*Leer un caracter por pantalla e imprimir su ID*/
BYTE _read();

/*Detectar un caracter por teclado*/
BYTE _kbhit();

/*Obtiene las posiciones x e y del cursor */
BYTE _wherex();
BYTE _wherey();

/*Coloca el cursor en la coordenada (x,y) en el plano (X) (-Y) */
void _gotoxy(BYTE x,BYTE y);

/*Fijar el aspecto del cursor */
void _setcursortype(int type);

/* Selecciona el modo de video deseado */
void _setvideomode(BYTE modo);

/*Fija el modo de video deseado */
BYTE _getvideomode();

/*Borra la pantalla*/
void _clrscr(BYTE color);

/*Borra una linea desde la posicion actual el cursor*/
void _clreol(BYTE color);

/*Scroll  hacia arriba*/
void _scrollup(BYTE color);
void _scrollupdesp(int desp,BYTE color);

/*Scroll  hacia abajo*/
void _scrolldown(BYTE color);
void _scrolldowndesp(int desp,BYTE color);

/*Escribe un caracter de un color en la posicion del cursor un numero determinado de veces*/
void _cputchar(BYTE car_ascii,BYTE color,BYTE num_rep);

/*Obtiene un caracter del teclado y lo muestra en pantalla*/
void _getche(BYTE color);

/*Imprime una cadena de caracteres por pantalla*/
void _cputs(char *s,BYTE color);


