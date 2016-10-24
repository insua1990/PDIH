/*
ASIGNATURA : " PERIFERICOS Y DISPOSITIVOS DE INTERFAZ HUMANA ".
AUTOR : Jose Manuel Martínez de la Insua.
*/

#include "graficos.h"

FRAME init(int xa,int ya,int xb,int yb){
    FRAME f;
    f.x0 = xa;f.x1 = xb;f.y0 = ya;f.y1 = yb;
    return f;
}

void frame_box(FRAME f,const BYTE color){
    int b=f.x1-f.x0,h=f.y1-f.y0,i;
    for(i=1;i<h;i++){
        _gotoxy(f.x0,f.y0+i);
        _cputchar(221,color,1);
        _gotoxy(f.x1,f.y0+i);
        _cputchar(222,color,1);
    }
    _gotoxy(f.x0,f.y0);
    _cputchar(220,color,b+1);
    _gotoxy(f.x0,f.y1);
    _cputchar(223,color,b+1);
    return;
}

void empty_box(FRAME f,const BYTE color){
    int i;
    for(i=f.y0;i<=f.y1;i++){
        _gotoxy(f.x0,i);
        _cputchar(255,color,f.x1-f.x0+1);
    }
    return;
}

void text_box(FRAME f,const char *str,const BYTE color,const int alignx,const int aligny){
    int i=0,X,Y;
    while (str[i] != '\0') i++;
    empty_box(f,color);

    if(aligny == TOP) Y = f.y0;
    else if(aligny == CENTER) Y = (f.y1+f.y0)/2;
    else Y = f.y1;

    if(alignx == LEFT)X = f.x0+2;
    else if(alignx == CENTER)X = 39-(i/2);
    else X = f.x1-2-i;

    _gotoxy(X,Y);
    _cputs(str,color);
    return;
}

void display_default_menu(FRAME f,const BYTE fcolor,const BYTE ocolor,const char **opts,const int tam,int selected){
    int i;
    empty_box(init(f.x0+1,f.y0+1,f.x1-1,f.y1-1),fcolor);frame_box(f,fcolor);
    for(i = 0;i<tam;i++)
        text_box(init(f.x0+2,f.y0+i+1,f.x1-2,f.y0+i+1),(char*)opts[i],ocolor,LEFT,CENTER);
    text_box(init(f.x0+2,f.y0+selected+1,f.x1-2,f.y0+selected+1),opts[selected],0x1F,LEFT,CENTER);
    return;
}

void display_default_info_menu(const char* title ,FRAME f,const BYTE fcolor,const BYTE ocolor,const char **opts,const int tam){
    int i;
    empty_box(init(f.x0-1,f.y0,f.x1+1,f.y1),fcolor);frame_box(f,fcolor);
    _gotoxy(f.x0+2,f.y0+1);
    _cputs(title,ocolor);
    for(i = 0;i<tam;i++)
        text_box(init(f.x0+2,f.y0+i+3,f.x1-2,f.y0+i+3),(char*)opts[i],ocolor,LEFT,CENTER);;
    return;
}


