/*
ASIGNATURA : " PERIFERICOS Y DISPOSITIVOS DE INTERFAZ HUMANA ".
AUTOR : Jose Manuel Martínez de la Insua.
*/

#include <dos.h>
#include "mi_io.h"

BYTE _read(void){
    BYTE result;
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16,&inregs,&outregs);
    result = outregs.h.al;
    result = (outregs.h.al == 0) ? outregs.h.ah : outregs.h.al;
    return result;
}

BYTE _kbhit(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    int86(0x16,&inregs,&outregs);
    return (outregs.x.flags>>6)&0x01;
}

BYTE _wherex(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;
    int86(0x10,&inregs,&outregs);
    return outregs.h.dl;
}

BYTE _wherey(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;
    int86(0x10,&inregs,&outregs);
    return outregs.h.dh;
}

void _gotoxy(const BYTE x,const BYTE y){
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    inregs.h.dh = y;
    inregs.h.dl = x;
    inregs.h.bh = 0x00;
    int86(0x10,&inregs,&outregs);
    return;
}

void _setcursortype(const int type){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(type){
        case 0:inregs.h.ch = inregs.h.ch | 0x20;break;
        case 1:inregs.h.ch = 0x06;inregs.h.cl = 0x07;break;
        case 2:inregs.h.ch = 0x00;inregs.h.cl = 0x07;break;
    }
    if(type > -1 && type < 3)int86(0x10,&inregs,&outregs);
    return;
}

void _setvideomode(const int mode){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = mode;
    int86(0x10,&inregs,&outregs);
    return;
}

BYTE _getvideowidth(void){
    union REGS inregs,outregs;
    inregs.h.ah = 0x0F;
    int86(0x10,&inregs,&outregs);
    return outregs.h.ah;
}

BYTE _getvideomode(void){
    union REGS inregs,outregs;
    inregs.h.ah = 0x0F;
    int86(0x10,&inregs,&outregs);
    return outregs.h.al;
}

void _clrscr(const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 480;
    inregs.h.dl = 640;
    int86(0x10,&inregs,&outregs);
    _gotoxy(0,0);
    return;
}

void _clrscr2(const BYTE color){
    _scrolldowndist(320,color);
    _gotoxy(0,0);
    return;
}

void _clreol(const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = 0x00;
    inregs.h.bh = color;
    inregs.h.ch = _wherey();
    inregs.h.cl = _wherex();
    inregs.h.dh = _wherey();
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    return;
}

void _scrollup(const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = 0x01;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()-1);
    return;
}

void _scrollupdist(const int dist,const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;
    inregs.h.al = dist;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()-dist);
    return;
}

void _scrolldown(const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x07;
    inregs.h.al = 1;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()+1);
    return;
}

void _scrolldowndist(const int dist,const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x07;
    inregs.h.al = dist;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()+dist);
    return;
}

void _cputchar(const BYTE char_ascii,const BYTE color,const BYTE num_rep){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = char_ascii;
    inregs.h.bl = color;
    inregs.h.bh = 0x00;
    inregs.x.cx = num_rep;
    int86(0x10,&inregs,&outregs);
    return;
}

void _getche(const BYTE color){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16,&inregs,&outregs);
    if(outregs.h.al != 0)
        _cputchar(outregs.h.al,color,1);
    return;
}

void _cputs(const char *str,const BYTE color){
    int i = 0;
    while (str[i] != '\0'){
        _cputchar(str[i],color,1);
        _gotoxy(_wherex()+1,_wherey());
        i++;
    }
    return;
}

BYTE _getstatuskeyboardbyte1(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    int86(0x16,&inregs,&outregs);
    return outregs.h.al;
}

BYTE _getstatuskeyboardbyte2(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    int86(0x16,&inregs,&outregs);
    return outregs.h.ah;
}

int _isactivebit(BYTE B,const int pos){
		return (((B>>pos) & 0x01) == 0x01);
}

void _waitforesc(void){
    while(_read()!=27);
    return;
}

void _waitforenter(void){
    while(_read()!=13);
    return;
}

BYTE _getkeyboardrate(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.al = 0x06;
    int86(0x16,&inregs,&outregs);
    return outregs.h.bl;
}

BYTE _getkeyboarddelay(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.al = 0x06;
    int86(0x16,&inregs,&outregs);
    return outregs.h.bh;
}

void _setdefaultrateanddelay(void){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.al = 0x00;
    int86(0x16,&inregs,&outregs);
    return;
}

void _setkeyboardrate(const BYTE rate){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.al = 0x05;
    inregs.h.bl = rate;
    int86(0x16,&inregs,&outregs);
    return;
}

void _setkeyboarddelay(const BYTE delay){
    union REGS inregs, outregs;
    inregs.h.ah = 0x03;
    inregs.h.al = 0x05;
    inregs.h.bh = delay;
    int86(0x16,&inregs,&outregs);
    return;
}
