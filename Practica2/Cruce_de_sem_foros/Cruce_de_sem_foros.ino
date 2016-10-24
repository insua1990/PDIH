
// Declaración de los pines

const int pulsador = 9;   // Pin 9 has an interruptor conected on most arduino board. De nombre pulsador
const int conmutador = 2; // Pin 2 has an interruptor conected on most arduino board. De nombre conmutador
const int rojo1 = 3;    // Pin 3 has an led red conected on most arduino board. De nombre rojo1
const int rojo2 = 6;    // Pin 6 has an led red conected on most arduino board. De nombre rojo2
const int verde1 = 5;   // Pin 5 has an led green conected on most arduino board. De nombre verde1 
const int verde2 = 8;   // Pin 8 has an led green conected on most arduino board. De nombre verde2 
const int ambar1 = 4;   // Pin 4 has an led orange conected on most arduino board. De nombre ambar1
const int ambar2 = 7;   // Pin 7 has an led orange conected on most arduino board. De nombre ambar2

// Variable que controla el modo actual del software.
int modo = 0;               // Controlar 0-Automatico 1-Manual
int pulmodo = 0;        // modo manual: cambio de semaforos
int buttonState = 0;        // estado del boton conmutador
int pulbuttonState = 0;   // estado del boton pulsador
int cambio=0;       // Bandera para controlar si se ha pulsado el conmutador 
              //(Esto hace que al pulsar y soltar el estado no me cambie de 1 a 0)
int pulcambio=0;      // Bandera para controlar si se ha pulsado el pulsador
              //(Esto hace que al pulsar y soltar el estado no me cambie de 1 a 0)

// Inicialización de los pines usados en el software.
void setup() {
  pinMode(rojo1, OUTPUT);   //Inicializo pin rojo1 a salida
  pinMode(rojo2, OUTPUT);   //Inicializo pin rojo2 a salida
  pinMode(verde1, OUTPUT);    //Inicializo pin verde1 a salida
  pinMode(verde2, OUTPUT);    //Inicializo pin verde2 a salida
  pinMode(ambar1, OUTPUT);    //Inicializo pin ambar1 a salida
  pinMode(ambar2, OUTPUT);    //Inicializo pin ambar2 a salida
  pinMode(conmutador, INPUT); //Inicializo pin conmutador a entrada
  pinMode(pulsador, INPUT);   //Inicializo pin pulsador a entrada
  Serial.begin(9600);     // Abrimos el puerto serie, establecemos una velocidad de datos a 9600 bps
}

//Todo lo del bucle se ejecutará sucesivamente de forma infinita
void loop() {
  estado();
    if(modo==0)     // Comprobación de que el modo sea Automático
      temporizador(); // Llamamos a la función temorizador que equivaldria a modo Automático
    else        // Sino accedemos al modo Manual
      manual();     // Llamamos a la función manual
    
}
   

// función para el comportamiento por defecto de los semáforos.
// Mientras el pulsador no esté activo se ejecutará este método.
void temporizador(){
    estado();           //Llamamos a función estado
    
    digitalWrite(rojo1, HIGH);    //encender el led rojo1
    digitalWrite(verde2, HIGH);   //encender el led verde2
    
    estado();           //Llamamos a función estado
    
    delay(3000);            //Espera de 3 segundos
  
    estado();           //Llamamos a función estado
    
    digitalWrite(verde2, LOW);    //apagar el led verde2
    digitalWrite(ambar2, HIGH);   //encender el led ambar1
  
    estado();           //Llamamos a función estado
    
    delay(500);           //Espera de medio segundos
  
    estado();           //Llamamos a función estado
    
    digitalWrite(rojo1, LOW);   //apagar el led rojo1
    digitalWrite(verde1, HIGH);   //encender el led verde1
    digitalWrite(ambar2, LOW);    //apagar el led rojo2
    digitalWrite(rojo2, HIGH);    //encender el led rojo2
    
    estado();           //Llamamos a función estado
    
    delay(3000);          //Espera de 3 segundos
    
    estado();           //Llamamos a función estado
    
    digitalWrite(verde1, LOW);    //apagar el led verde1
    digitalWrite(ambar1, HIGH);   //encender el led ambar1
    
    estado();           //Llamamos a función estado
    
    delay(500);           //Espera de medio segundos
  
    estado();           //Llamamos a función estado
    
    digitalWrite(ambar1, LOW);    //apagar el led ambar1
    digitalWrite(rojo2, LOW);   //apagar el led rojo2
    digitalWrite(rojo1, HIGH);    //encender el led rojo1
    digitalWrite(verde2, 1);    //encender el led verde2
    
    estado();           //Llamamos a función estado
    
    delay(3000);          //Espera de 3 segundos
    
    estado();           //Llamamos a función estado
   
}

// modo manual del semáforo.
void manual(){
    
    pulbuttonState = digitalRead(pulsador);     //Variable que almacena el estador actual del pulsador
    if (pulbuttonState == HIGH && pulcambio == 0) { //Comprobación de que el pulsador esta activo y la bandera del pulsador esta inactiva 
      pulcambio=1;                  //La bandera del pulsador pasa a activa 
       Serial.println("primero");
     digitalWrite(rojo1, HIGH);   //encender el led rojo1
     digitalWrite(verde2, HIGH);  //encender el led verde2

      delay(3000);            //Espera de 3 segundos

      digitalWrite(verde2, LOW);  //apagar el led verde2
      digitalWrite(ambar2, HIGH); //encender el led ambar2

      delay(500);         //Espera de medio segundos

      digitalWrite(rojo1, LOW);   //apagar el led rojo1
      digitalWrite(verde1, HIGH); //encender el led rojo1
      digitalWrite(ambar2, LOW);  //apagar el led ambar2
      digitalWrite(rojo2, HIGH);  //encender el led rojo2
    

    } else if(pulbuttonState == HIGH && pulcambio==1){ //Comprobación de que el pulsador esta activo y la bandera del pulsador esta activa 
      pulcambio=0;                     //La bandera del pulsador pasa a inactiva
    
     // delay(3000);            //Espera de 3 segundos
      Serial.println("segundo");
      digitalWrite(verde1, LOW);  //apagar el led verde1
      digitalWrite(ambar1, HIGH); //encender el led ambar1
    
      delay(500);         //Espera de medio segundos

      digitalWrite(ambar1, LOW);  //apagar el led ambar1
      digitalWrite(rojo2, LOW);   //apagar el led rojo2
      digitalWrite(rojo1, HIGH);  //encender el led rojo1
      digitalWrite(verde2, 1);      //encender el led verde2
    }
}

//Función que devuelve el modo al pulsar el boton derecho( 0 = Automatico; 1 = Manual )
void estado(){
      buttonState = digitalRead(conmutador);    //Variable que almacena el estador actual del conmutador
      
      if (buttonState == HIGH && cambio == 0) {   //Comprobación de que el conmutador esta activo y la bandera del conmutador esta inactiva 
        modo++;                   //Aumentamos el modo
        cambio=1;                 //La bandera del conmutador pasa a activa
        modo=modo%2;                //Limitamos el modulo a que tome valores entre 0 y 1
        Serial.print("modo: ");           //Imprimimos por el serial un string 
        Serial.println(modo);           //Imprimimos por el serial el modo en el que nos encontramos
        apagar();                 //Llamamos a la funcion apagar 

      } else if(buttonState == LOW && cambio==1){ //Comprobación de que el conmutador esta inactivo y la bandera del conmutador esta activa 
        cambio=0;                 //La bandera del conmutador pasa a inactiva
        
      }
  
}

//Función para apagar todos los leds
void apagar(){
  digitalWrite(verde1, LOW);  //apagar el led verde1
  digitalWrite(verde2, LOW);  //apagar el led verde2
  digitalWrite(ambar1, LOW);  //apagar el led ambar1
  digitalWrite(ambar2, LOW);  //apagar el led ambar2
  digitalWrite(rojo2, LOW);   //apagar el led rojo2
  digitalWrite(rojo1, LOW);   //apagar el led rojo1
}

