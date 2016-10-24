/*
ASIGNATURA : " PERIFERICOS Y DISPOSITIVOS DE INTERFAZ HUMANA ".
AUTOR : Jose Manuel Martínez de la Insua.
PRACTICA 1 : " Programación de interrupciones para periféricos de entrada/salida en MS-DOS ".
*/

#include <dos.h>
#include "graficos.h"
#include <stdio.h>

/*
Constantes estáticas que definen los colores utilizados en el programa.
*/
const static BYTE DEFAULT = 0x0F;
const static BYTE BLACK_BLUE = 0x01;
const static BYTE BLACK_RED = 0x04;
const static BYTE RED_YELLOW = 0x4E;
const static BYTE CYAN_BLUE = 0x31;
const static BYTE CYAN_RED = 0x34;
const static BYTE BLUE_WHITE = 0x1F;

/*
Vectores constantes que almacenan las cadenas de caracteres utilizadas por el programa.
*/
const char* options[6] = {"1. Estado del teclado.","2. Modificar velocidad de respuesta del teclado.","3. Informe de modo de video.","4. Modificar modo de video.","5. Modificar aspecto del cursor.","6. Salir."};
const char* keyboardkeys[8] ={"Shift Dcho : ", "Shift Izq : ", "Control : ", "Alt : ", "Bloq Desp. : ","Bloq Num. : ", "Bloq May. : ","Insertar : " };
const char* videomodes[16] ={"0h: Texto 40x25 (16 grises)","1h: Texto 40x25 (16 colores)","2h: Texto 80x25 (16 colores)","3h: Texto 80x25 (16 colores)","4h: Grafico 320x200 (4 colores)","5h: Grafico 320x200 (4 grises)","6h: Grafico 640x200 (2 colores)","7h: Texto 80x25 (monocromo)","Dh: Grafico 320x200 (16 colores)","Eh: Grafico 640x200 (16 colores)","Fh: Grafico 640x350 (monocromo)","10h: Grafico 640x350 (16 colores)","11h: Grafico 640x480 (2 colores)","12h: Grafico 640x480 (16 colores)","13h: Grafico 320x200 (256 colores)","Menu Principal"};
const char* cursortypes[4] = {"1. Cursor invisible","2. Cursor fino","3. Cursor grueso","4. Menu Principal"};
const char* keyboardtest[4] ={"1. Cambiar retardo y factor de rep.","2. Probar configuracion","3. Cargar por defecto","4. Menu Principal"};
const char* keyboardratedelay[2] = {"Valor de retardo (0=0.25, 1=0.5, 2=0.75, 3=1) : ","Valor de repeticion (0=30 cps hasta 31=2 cps) : "};
const char* videoinfo[3] = {"Modo : H'","Columnas : ","Filas : "};





/*################################################################################################################
############################   INTERFAZ GRAFICA PROPIA DEL PROGRAMA    #############################################
################################################################################################################*/





/*
Crea el menú para representar el estado de las teclas (CTRL,ALT...) del teclado.
Primero lanza el menú informativo por defecto definido en "graficos.h"
y después asigna a cada opción el valor ON si está la tecla en el buffer, OFF
en caso contrario.
 */
void display_keyboard_state_menu(void);


/*
Crea el menu para representar el modo de vídeo en el cual nos encontramos (0h-13h).
El menú consta de 15 opciones : opciones 0-13 para los modos de vídeo y la última
opción para salir.
El menú lanzado es el menú de opciones por defecto definido en "graficos.h"
*/
void display_video_state_menu(void);


/*
Crea el menu para seleccionar el factor de repeticion y el retardo del teclado.
La interfaz no permitirá abandonar el menú mientras no se introduzcan números
válidos para cada opción.
*/
void display_rate_delay_menu(void);


/*
Restaura valores por defecto.
Modo de vídeo : 0x03h
Cursor : Fino (modo texto)
Valores definidos por defecto para retardo y factor de repetición.
*/
void restore_defaults(void);


/*
Muestra el menú principal del programa.
El método de funcionamiento es el siguiente:
1 - Dibuja el rectángulo contenedor.
2 - Dibuja dentro 6 "textbox"(graficos.h) con las opciones.
3 - Dibuja la opción seleccionada de color rojo para el fondo y amarillo para los caracteres.

selected : (const int) Opción seleccionada (0 por defecto).
*/
void display_main_menu(const int selected);




/*################################################################################################################
########################################  INTERFAZ DE USUARIO  ###################################################
################################################################################################################*/




/*
Método para recorrer el menú de opciones por defecto(graficos.h).
La idea de ésta función es poder recorrer cualquier menú de opciones por defecto,
(de los definidos en graficos.h) con las teclas 'UP_ARROW', 'DOWN_ARROW' y 'ENTER'.
Ésta herramienta se encarga, además, de re-dibujar el menú después de cambiar de opción,
así como de lanzar la función correspondiente al menú tras pulsar la telca ENTER.
Para ello, se pasa por parámetro:
f: FRAME del menú (estructura definida en graficos.h).
bg: (BYTE) Color de fondo del menú (4 bits más a la izq para fondo y 4 más a la drcha para caracteres).
fg: (BYTE) Color de caracter del menú. Igual que 'bg'.
opts: (char**) Array con las opciones del menú. (La última opción debe ser la salida del menú).
tam: (int) Tamaño del vector 'opts'.
fptr: (*) Puntero a función de tipo void que acepta por parámetro un entero. Se trata de la función
     correspondiente al menú de opciones. Por ejemplo, en el menú de selección de modo de vídeo, ésta
     función llamará a 'void _setvideomode(const int mode)' al pulsar la tecla ENTER.
selected: (int) Opción seleccionada.
clrscr: (int) 1 Si desea limpar la pantalla, 0 en caso  contrario. Indica si el menú por el cual nos desplazamos
       aparece superpuesto sobre otro (u otros) menú(s), o si por el contrario aparece solo en pantalla.
*/
void move(FRAME f,BYTE bg,BYTE fg,char **opts,const int tam,void (*fptr)(int),const int selected,const int clrscr);


/*
Gestiona el menú principal del programa.
Se encarga de lanzar la función correspondiente a la opción
seleccionada en el menú principal ('display_main_menu()').
*/
void manage_main_menu(const int opt);


/*
Gestiona el menú de configuración de teclado.
Se encarga de lanzar la función correspondiente a la opción
seleccionada en el menú de configuración de teclado ('display_keyboard_state_menu()').
*/
void manage_keyboard_menu(const int opt);


/*
Se encarga de lanzar una pantalla para probar la configuración de teclado y vídeo, así
como el tipo de cursor. Como máximo permitirá escribir 200 caracteres.
Lee cualquier caracter introducido por teclado. Las teclas especiales no están configuradas,
es decir, al pulsar una tecla especial (a excepción de las 4 flechas , ESC y ENTER) se imprimirá
por pantalla el caracter correspondiente al BIOS SCAN CODE devuelto por la función _read() definida en
graficos.h .
*/
void launch_test(void);




/*################################################################################################################
#############################################  MENU PRINCIPAL  ###################################################
################################################################################################################*/




int main(){
    int exit = 0,option = 0,key = 0;
    display_main_menu(exit);
    while(exit!=5){
        key = _read();
        switch(key){
			case 72:option--;if(option<0)option=5;break;
			case 80:option++;if(option>5)option=0;break;
            case 13:exit = option;if(exit!=5)manage_main_menu(option);break;
            case 27:exit = 5;break;
        }
        display_main_menu(option);
    }
    _clrscr(DEFAULT);
	return(0);
}




/*################################################################################################################
###################################   FUNCIONES IMPLEMENTADAS   ##################################################
################################################################################################################*/




void move(FRAME f,BYTE bg,BYTE fg,char *opts[],const int tam,void (*fptr)(int),const int selected,const int clrscr){
    int exit = 0,option = selected,key = 0;
    if(clrscr==1)_clrscr(DEFAULT);
    display_default_menu(f,bg,fg,(char**)opts,tam,option);
    while(exit!=tam-1){
        key = _read();
        switch(key){
            case 27:exit = tam-1;break;
            case 72:option--;if(option<0)option=tam-1;break;
            case 80:option++;if(option>tam-1)option=0; break;
			case 13:exit = option;if(exit!=tam-1)(option>=8) ? fptr(option+5) : fptr(option);break;
        }
        if(clrscr==1)_clrscr(DEFAULT);
        display_default_menu(f,bg,fg,(char**)opts,tam,option);
    }
    return;
}

void restore_defaults(void){
    _setvideomode(3);
    _setcursortype(1);
    _setdefaultrateanddelay();
    return;
}

void launch_test(void){
    int i,j,cont=0,key;
    _clrscr(DEFAULT);
    _cputs((char*)"Escribe : ",DEFAULT);
    i = _wherex();
    j = _wherey();
    while(cont<200){
        key = _read();
        if(key == 27 || key == 13) cont = 200;
        else if(key == 8){
            if(!(i==10 && j==0)){
                if(i == 0){
                    i = 79;
                    j = _wherey() -1;
                }else{
                    i = _wherex()-1;
                    j = _wherey();
                }
                _gotoxy(i,j);_cputchar(255,DEFAULT,1);
            }
        }else if(key == 77 || key == 75 || key == 72 || key == 80){
        }else{
            _cputchar(key,DEFAULT,1);_gotoxy(i+1,j);
            i++;
            if(i>79){ i=0;j++;}
            cont++;
        }
    }
    _clrscr(DEFAULT);
    return;
}



/*Gestores de menú*/

void manage_main_menu(const int opt){
		switch(opt){
            case 0:display_keyboard_state_menu();_waitforesc();break;
            case 1:move(init(14,5,55,10),BLACK_RED,DEFAULT,(char**)keyboardtest,4,manage_keyboard_menu,0,1);break;
            case 2:display_video_state_menu();_waitforesc();break;
            case 3:move(init(5,2,50,19),BLACK_RED,DEFAULT,videomodes,16,_setvideomode,0,1);break;
			case 4:move(init(20,11,50,16),BLACK_RED,DEFAULT,(char**)cursortypes,4,_setcursortype,0,0);break;
    }
    return;
}

void manage_keyboard_menu(const int opt){
    switch(opt){
        case 0:display_rate_delay_menu();break;
        case 1:launch_test();break;
        case 2:restore_defaults();break;
    }
    return;
}


/*Gráficos*/


void display_main_menu(const int selected){
        int i;
		FRAME f = init(9,0,70,24);
		FRAME f1 = init(f.x0+1,f.y0+1,f.x1-1,f.y1-1);
		FRAME sel = init(f.x0+5,3*(selected+1),f.x1-5,(3*(selected+1))+2);
		_clrscr(DEFAULT);empty_box(f1,DEFAULT);frame_box(f,BLACK_BLUE);
		for(i=0;i<6;i++)
			text_box(init(f.x0+5,3*(i+1),f.x1-5,(3*(i+1))+2),(char*)options[i],DEFAULT,CENTER,CENTER);
		text_box(sel,(char*)options[selected],RED_YELLOW,CENTER,CENTER);
		return;
}

void display_keyboard_state_menu(void){
    int i;
    FRAME f = init(40,6,63,20);
    display_default_info_menu((char*)"#TECLADO#",f,CYAN_BLUE,CYAN_BLUE,(char**)keyboardkeys,8);
    for(i = 0;i<8;i++){
		_gotoxy(57,8+i+1);
        (_isactivebit(_getstatuskeyboardbyte1(),i)) ? _cputs((char*)"ON",CYAN_BLUE) : _cputs((char*)"OFF",CYAN_BLUE);
    }
    _gotoxy(f.x0+2,f.y1-1);_cputs((char*)"ESC -> SALIR.",CYAN_RED);
    return;
}

void display_video_state_menu(void){
    FRAME f = init(40,6,63,15);
    char str[4],str1[4];
    display_default_info_menu((char*)"#VIDEO#",f,CYAN_BLUE,CYAN_BLUE,(char**)videoinfo,3);
    _gotoxy(f.x0+13,f.y0+3);
    switch(_getvideomode()){
        case 0x0D:sprintf(str,"%c",'D');_cputs(str,CYAN_BLUE);break;
        case 0x0E:sprintf(str,"%c",'E');_cputs(str,CYAN_BLUE);break;
        case 0x0F:sprintf(str,"%c",'F');_cputs(str,CYAN_BLUE);break;
        case 0x10:sprintf(str,"%i",10);_cputs(str,CYAN_BLUE);break;
        case 0x11:sprintf(str,"%i",11);_cputs(str,CYAN_BLUE);break;
        case 0x12:sprintf(str,"%i",12);_cputs(str,CYAN_BLUE);break;
        case 0x13:sprintf(str,"%i",13);_cputs(str,CYAN_BLUE);break;
        default: _cputchar(_getvideomode()+48,CYAN_BLUE,1);break;
    }

    switch(_getvideomode()){
        case 0x00:sprintf(str,"%i",25);sprintf(str1,"%i",40);break;
        case 0x01:sprintf(str,"%i",25);sprintf(str1,"%i",40);break;
        case 0x02:sprintf(str,"%i",25);sprintf(str1,"%i",80);break;
        case 0x03:sprintf(str,"%i",25);sprintf(str1,"%i",80);break;
        case 0x04:sprintf(str,"%i",200);sprintf(str1,"%i",320);break;
        case 0x05:sprintf(str,"%i",200);sprintf(str1,"%i",320);break;
        case 0x06:sprintf(str,"%i",200);sprintf(str1,"%i",640);break;
        case 0x07:sprintf(str,"%i",25);sprintf(str1,"%i",80);break;
        case 0x0D:sprintf(str,"%i",200);sprintf(str1,"%i",320);break;
        case 0x0E:sprintf(str,"%i",200);sprintf(str1,"%i",640);break;
        case 0x0F:sprintf(str,"%i",350);sprintf(str1,"%i",640);break;
        case 0x10:sprintf(str,"%i",350);sprintf(str1,"%i",640);break;
        case 0x11:sprintf(str,"%i",480);sprintf(str1,"%i",640);break;
        case 0x12:sprintf(str,"%i",480);sprintf(str1,"%i",640);break;
        case 0x13:sprintf(str,"%i",200);sprintf(str1,"%i",320);break;
    }
    _gotoxy(f.x0+15,f.y0+4);
    _cputs(str1,CYAN_BLUE);
    _gotoxy(f.x0+13,f.y0+5);
    _cputs(str,CYAN_BLUE);


    _gotoxy(f.x0+2,f.y1-1);
    _cputs((char*)"ESC -> SALIR.",CYAN_RED);
    return;
}

void display_rate_delay_menu(void){
    int rate=-1,delay,key=-1;
    FRAME f = init(17,8,71,11);
    empty_box(f,DEFAULT);frame_box(f,BLACK_RED);
    _gotoxy(f.x0+2,f.y0+1);_cputs(keyboardratedelay[0],DEFAULT);
    _gotoxy(f.x0+2,f.y0+2);_cputs(keyboardratedelay[1],DEFAULT);
    while(!(key==13 && rate >-1 && rate <4)){
        _gotoxy(f.x1-4,f.y0+1);
        key = _read();
        if(key!=13){
            rate = key - 48;
            _cputchar(key,DEFAULT,1);
        }
    }
    key=-1;
    delay=-1;
    while(!(key==13 && delay >-1 && delay <32)){
        _gotoxy(f.x1-4,f.y0+2);
        key = _read();
        if(key!=13){
            delay = (key-48);
            _cputchar(key,DEFAULT,1);_gotoxy(f.x1-3,f.y0+2);
			key = _read() ;
            if(key!=13){
                delay = (delay*10) + (key-48);
                _cputchar(key,DEFAULT,1);
            }
        }
    }
    _setkeyboarddelay(delay);
    _setkeyboardrate(rate);
    return;
}

