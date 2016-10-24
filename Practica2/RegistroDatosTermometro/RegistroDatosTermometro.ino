#include <LiquidCrystal.h>
#include <EEPROM.h>

/* Definici�n del retardo por defecto y del m�ximo de lecturas permitidas para el software. */

#define DELAY 1000
#define MAXLECTURAS 100

/* Variables que controlan el registro en el cual escribe la memoria EEPROM, el contador de lecturas actual y la �ltima temperatura registrada. */

float temperaturaActual =0.00f;
int registro = 0;
int contador = 0;

/* Declaraci�n de la pantalla LCD y del sensor de temperatura (pin anal�gico). */

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int sensorTmp = A0;

/* Funci�n que recoge todos los datos de temperaturas de la memoria EEPROM y los saca por el puerto serie. 

void recogerTemperaturas(){
    int i;
    float valor = 0;
    Serial.println("REGISTRO DE TEMPERATURAS: ");
    for (i=0;i<registro;i+=sizeof(float)){
        valor = EEPROM.get(i,valor) ;
        Serial.print("Lec : ");Serial.print(i/4);Serial.print("    Temp : ");Serial.print(valor);Serial.println();
    }
    Serial.println("-------------------------------------");
}

/* Funci�n para registrar una temperatura en la memoria EEPROM(modo autom�tico) con un retardo posterior. */

void registraTemperatura(){
  if(contador<128){
    temperaturaActual = conversionTMP(analogRead(sensorTmp));
    EEPROM.put(registro,temperaturaActual);
    registro+=sizeof(float);
    contador++;
    delay(DELAY);
  }
}

/* Funci�n para registrar una temperatura en la memoria EEPROM(modo manual) con un retardo posterior. */

void registraTemperaturaManual(){
  if(contador<128){
    temperaturaActual = conversionTMP(analogRead(sensorTmp));
    EEPROM.put(registro,temperaturaActual);
    registro+=sizeof(float);
    contador++;
    delay(50);
  }
}

/* Vaciado completo de la memoria EEPROM y puesta a cero de las variables necesarias. Retardo posterior para asegurar colisiones. */

void vaciarRegistro(){
    lcd.clear();
    temperaturaActual = 0.00f;
    contador = 0;
    registro = 0;
    int i;
    for (i = 0; i < registro; i++)
      EEPROM.write(i, 0); 
    delay(50);
}

/* Funci�n de configuraci�n. Inicializaci�n de la pantalla y puerto serie*/

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    delay(50);
}

/* Funci�n "display", muestra la informaci�n en la pantalla LCD .*/

void mostrarLCD(){
    lcd.setCursor(0,0);
    lcd.print("Temp: ");lcd.print(temperaturaActual);
    lcd.setCursor(0,1);
   lcd.print("Lecturas: ");lcd.print(contador);
}

/* Funci�n "loop" . Registra temperaturas c�clicamente en intervalo de tiempo definido. Recibe informaci�n del puerto serie de Arduino y ejecuta la funci�n correspondiente en base al par�metro recibido. */

void loop() {
    if (Serial.available() > 0) {
      switch (Serial.read()){
          //W
          case 87: registraTemperaturaManual(); break;
          case 119: registraTemperaturaManual();  break;
          //R
          case 82: recogerTemperaturas(); break;
          case 114: recogerTemperaturas();  break;
          //B
          case 66: vaciarRegistro();  break;
          case 98: vaciarRegistro();  break;
      }
    }
    registraTemperatura();
    mostrarLCD();
}

/* Funci�n que convierte el valor recibido por el sensor de temperatura en grados celsius. */

float conversionTMP(float valorSensor){ return ((valorSensor/1024.0)*5.0-0.5)*100;  }
