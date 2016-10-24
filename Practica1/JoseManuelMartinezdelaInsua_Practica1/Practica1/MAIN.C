#include <stdio.h>
#include "mi_io.h"

const static BYTE COLOR_DEFECTO = 0x0F;
const static BYTE COLOR_SPAIN = 0x64;
const static BYTE COLOR_NEGRO_AZUL = 0x01;
const static BYTE COLOR_AZUL_NEGRO = 0x10;

void _nl(){
    _gotoxy(0,_wherey()+1);
}

void _next(){
    _cputs("Pulsa una tecla para continuar...",COLOR_DEFECTO);
    _nl();
    _read();
}

int main(){
    _clrscr(COLOR_DEFECTO);
    _gotoxy(0,0);
    _cputs("Prueba de kbhit() y read(). Pulsa una tecla:",COLOR_DEFECTO);
    _nl();
    printf("Codigo de la tecla pulsada: %i \n",_read());
    _next();
    _cputs("Prueba de gotoxy(). Voy a escribir en la coordenada (30,10).",COLOR_DEFECTO);
    _nl();
    _next();
    _gotoxy(30,10);
    printf("Prueba de wherex/y().La cordenada de la letra 'P' de 'Prueba' esta en la coordenada: (%i,%i)\n",_wherex(),_wherey());
    _next();
    _cputs("Prueba de setcursortype() << modo grueso >>",COLOR_DEFECTO);
    _nl();
    _next();
    _setcursortype(2);
    _cputs("Prueba de clrscr(). ",COLOR_DEFECTO);
    _nl();
    _next();
    _clrscr(COLOR_DEFECTO);
    _cputs("Prueba de clreol(). Voy a borrar la primera linea...",COLOR_DEFECTO);
    _nl();
    _cputs("(Salvo las tres primeras letras!!).",COLOR_DEFECTO);
    _nl();
    _next();
    _gotoxy(3,0);
    _clreol(COLOR_DEFECTO);
    _gotoxy(0,4);
    _next();
    _cputs("Prueba de scroll(). Subimos dos lineas...",COLOR_DEFECTO);
    _nl();
    _next();
    _scrollupdesp(2,COLOR_DEFECTO);
    _next();
    _cputs("Y ahora bajamos tres.",COLOR_DEFECTO);
    _nl();
    _next();
    _scrolldowndesp(3,COLOR_DEFECTO);
    _next();
    _clrscr(COLOR_DEFECTO);
    _cputs("Prueba de getche(). Introduce un caracter para",COLOR_DEFECTO);
    _nl();
    _cputs("mostrarlo en la esquina inferior drch de la pantalla.",COLOR_DEFECTO);
    _gotoxy(79,24);
    _getche(COLOR_DEFECTO);
    _gotoxy(0,20);
    _cputs("FG : Rojo ",COLOR_DEFECTO);
    _nl();
    _cputs("BG : Amarillo ",COLOR_DEFECTO);
    _nl();
    _cputs("Autor : Jose Manuel Martinez de la Insua.",COLOR_SPAIN);
    _nl();
    _read();
    _clrscr(COLOR_DEFECTO);
	return(0);
}

