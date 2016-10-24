#include <dos.h>
#include "mi_io.h"

BYTE _read(){
    BYTE resultado;
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    int86(0x16,&inregs,&outregs);
    resultado = outregs.h.al;
    if(resultado == 0)
        resultado = outregs.h.ah;
    return resultado;
}

BYTE _kbhit(){
    union REGS inregs, outregs;

    inregs.h.ah = 0x01;
    int86(0x16,&inregs,&outregs);
    return (outregs.x.flags>>6)&0x01;
}

BYTE _wherex(){
    union REGS inregs, outregs;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;
    int86(0x10,&inregs,&outregs);
    return outregs.h.dl;
}

BYTE _wherey(){
    union REGS inregs, outregs;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;
    int86(0x10,&inregs,&outregs);
    return outregs.h.dh;
}

void _gotoxy(BYTE x,BYTE y){
    union REGS inregs, outregs;

    inregs.h.ah = 0x02;
    inregs.h.dh = y;
    inregs.h.dl = x;
    inregs.h.bh = 0x00;
    int86(0x10,&inregs,&outregs);
    return;
}


void _setcursortype(int type){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    if(type == 0){
        /*Modo invisible*/
        inregs.h.ch = inregs.h.ch | 0x40;
        inregs.h.cl = 0x00;
    }else if(type == 1){
        /*Modo delgado*/
        inregs.h.ch = 0x02;
        inregs.h.cl = 0x02;
    }else if(type == 2){
        /*Modo grueso*/
        inregs.h.ch = 0x01;
        inregs.h.cl = 0x05;
    }
    if(type > -1 && type < 3)
        int86(0x10,&inregs,&outregs);
    return;
}

void _setvideomode(BYTE modo){
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    inregs.h.al = modo;
    int86(0x10,&inregs,&outregs);
    return;
}

BYTE _getvideomode(){
    BYTE resultado;
    union REGS inregs,outregs;
    int al,ah;
    inregs.h.ah = 0x0F;
    int86(0x10,&inregs,&outregs);
    al = outregs.h.al;
    ah = outregs.h.ah;
    if(al==0 || al==1 || al==2 || al==3 || al==7)
        resultado = ah;
    else
        resultado = al;
    return resultado;
}

void _clrscr(BYTE color){
    union REGS inregs, outregs;

    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(0,0);
    return;
}

void _clreol(BYTE color){
    union REGS inregs, outregs;
    BYTE x = _wherex();
    BYTE y = _wherey();
    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.bh = color;
    inregs.h.ch = y;
    inregs.h.cl = x;
    inregs.h.dh = y;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    return;
}

void _scrollup(BYTE color){
    union REGS inregs, outregs;

    inregs.h.ah = 0x06;
    inregs.h.al = 1;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()-1);
    return;
}

void _scrollupdesp(int desp,BYTE color){
    union REGS inregs, outregs;

    inregs.h.ah = 0x06;
    inregs.h.al = desp;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()-desp);
    return;
}

void _scrolldown(BYTE color){
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

void _scrolldowndesp(int desp,BYTE color){
    union REGS inregs, outregs;

    inregs.h.ah = 0x07;
    inregs.h.al = desp;
    inregs.h.bh = color;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 24;
    inregs.h.dl = 79;
    int86(0x10,&inregs,&outregs);
    _gotoxy(_wherex(),_wherey()+desp);
    return;
}

void _cputchar(BYTE car_ascii,BYTE color,BYTE num_rep){
    union REGS inregs, outregs;

    inregs.h.ah = 0x09;
    inregs.h.al = car_ascii;
    inregs.h.bl = color;
    inregs.h.bh = 0x00;
    inregs.x.cx = num_rep;
    int86(0x10,&inregs,&outregs);
    return;
}

void _getche(BYTE color){
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    int86(0x16,&inregs,&outregs);
    if(outregs.h.al != 0)
        _cputchar(outregs.h.al,color,1);
    return;
}

void _cputs(char *s,BYTE color){
    int i = 0;
    while (s[i] != '\0'){
        _cputchar(s[i],color,1);
        _gotoxy(_wherex()+1,_wherey());
        i++;
    }
    return;
}




